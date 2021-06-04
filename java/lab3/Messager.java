import java.net.*;
import java.io.*;
import java.util.concurrent.*;
import java.util.*;
import java.nio.channels.*;
import java.nio.*;

class Messager implements Runnable{
	
	Messager(Peer peer, int blocks, int blockSize, String file, FileReader fileReader) {
		this.peer = peer;
		this.blocks = blocks;
		this.blockSize = blockSize;
		this.file = file;
		this.fileReader = fileReader;
	}
	
	@Override
	public void run() {
		Socket clientSocket = peer.getSocket();
		try (InputStream input = clientSocket.getInputStream();
				BufferedReader reader = new BufferedReader(new InputStreamReader(input));
				OutputStream output = clientSocket.getOutputStream();
				OutputStreamWriter writer = new OutputStreamWriter(output);
				InputStream fileInput = new FileInputStream(new File(file));
				BufferedReader fileReader = new BufferedReader(new InputStreamReader(fileInput))){
			while(true){
				if(!reader.ready()){
					continue;
				}
				int length = readInt();
				int index = reader.read();
				switch(index){
					case CHOCK:
						peer.setIsChocked(true);
						break;
					case UNCHOCK:
						peer.setIsChocked(false);
						break;
					case INTERESTED:
						peer.setIsInterested(true);
						break;
					case UNINTERESTED:
						peer.setIsInterested(false);
						break;
					case HAVE:
						int piece = readInt();
						peer.hasPieces().set(piece, true); 
						break;
					case REQUIRE:
						int piece = readInt();
						int offset = readInt();
						int blockLength = readInt();
						fileReader.reset();
						fileReader.skip(offset);
						char mes[] = new char[blockLength];
						fileReader.read(mes);
						StringBuilder message = new StringBuilder("");
						message.append((char)(blockLength >> CHAR_BITS));
						message.append((char)(blockLength % CHAR_MAX));
						message.append((char)PIECE);
						message.append(new String(mes));
						writer.write(message.toString());
						writer.flush();
						break;
					case PIECE:
						break;
					case CANCEL:
						break;
				}
			}
		}
		catch (IOException ex) {
			ex.printStackTrace();
		}
	}
	
	private int readInt(BufferedReader reader) throws IOException{
		int numb = 0;
		for(int i = 0; i < INT_LENGTH; ++i){
			numb = numb * CHAR_BITS + reader.read();
		}
		return numb;
	}
	
	private int toInt(String line){
		int numb = 0;
		for(int i = 0; i < line.length(); ++i){
			numb = numb * 10 + Character.digit(line.charAt(i), Character.MAX_RADIX);
		}
		return numb;
	}
	
	private Peer peer;
	private int blocks;
	private int blockSize;
	private String file;
	private FileReader fileReader;
	private int CHAR_BITS = 16;
	private int CHAR_MAX = 65 536;
	private final int CHOCK = 0;
	private final int UNCHOCK = 1;
	private final int INTERESTED = 2;
	private final int UNINTERESTED = 3;
	private final int HAVE = 4;
	private final int BIT_FIELD = 5;
	private final int REQUIRE = 6;
	private final int PIECE = 7;
	private final int CANCEL = 8;
}