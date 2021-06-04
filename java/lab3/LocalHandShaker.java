import java.net.*;
import java.io.*;
import java.util.concurrent.*;
import java.util.*;
import java.nio.channels.*;
import java.nio.*;

public class LocalHandShaker implements Runnable{
	
	LocalHandShaker(SocketChannel clientChannel, String metaHash, String myId, 
	List<Peer> peers, int piecesCount, List<Boolean> hasPieces) {
		this.clientChannel = clientChannel;
		this.metaHash = metaHash;
		this.myId = myId;
		this.selector = selector;
		this.peers = peers;
		this.piecesCount = piecesCount;
		this.hasPieces = hasPieces;
	}
	
	@Override
	public void run() {
		Socket clientSocket = clientChannel.socket();
		try (InputStream input = clientSocket.getInputStream();
				BufferedReader reader = new BufferedReader(new InputStreamReader(input));
				OutputStream output = clientSocket.getOutputStream();
				OutputStreamWriter writer = new OutputStreamWriter(output)){
			String line;
			char mes[] = new char[MAX_BUF_SIZE];
			int length = reader.read();
			if(length != MES_LENGTH){
				return;
			}
			reader.read(mes, 0, length);
			line = new String(mes, 0, length);
			if(line.compareTo(PROTOCOL) != 0){
				return;
			}
			reader.read(mes, 0, HASH_LENGTH);
			line = new String(mes, 0, HASH_LENGTH);
			if(line.compareTo(metaHash) != 0){
				return;
			}
			reader.read(mes, 0, ID_LENGTH);
			line = new String(mes, 0, ID_LENGTH);
			if(line.compareTo(myId) == 0){
				return;
			}
			length = readInt(reader);
			int index = reader.read();
			System.out.println(length + " " + index);
			if(index != BIT_FIELD){
				return;
			}
			reader.read(mes, 0, length);
			
			Peer newPeer = new Peer(getBitField(length, new String(mes)), false, false, clientSocket);
			peers.add(newPeer);
			System.out.println(newPeer.isChocked() + " " + newPeer.isInterested());
			for(int i = 0; i < newPeer.hasPieces().size(); ++i){
				System.out.println(newPeer.hasPieces().get(i));
			}
			length = getHasPiecesLength();
			StringBuilder message = new StringBuilder("");
			message.append((char)(length >> CHAR_BITS));
			message.append((char)(length % CHAR_MAX));
			message.append((char)BIT_FIELD);
			createBitField(message, length);
			writer.write(message.toString());
			writer.flush();
		}
		catch (IOException ex) {
			ex.printStackTrace();
		}
	}
	
	private void createBitField(StringBuilder message, int length){
		for(int i = 0; i < length; ++i){
			message.append((hasPieces.get(i)) ? '1' : '0');
		}
	}
	
	private int getHasPiecesLength(){
		int length = 0;
		int falseCount = 0;
		for(int i = 0; i < hasPieces.size(); ++i){
			++falseCount;
			if(hasPieces.get(i)){
				length += falseCount;
				falseCount = 0;
			}
		}
		return length;
	}
	
	private int readInt(BufferedReader reader) throws IOException{
		int numb = 0;
		for(int i = 0; i < INT_LENGTH; ++i){
			numb = numb * CHAR_BITS + reader.read();
		}
		return numb;
	}
	
	private List<Boolean> getBitField(int length, String mes) throws IOException{
		List<Boolean> bitField = new ArrayList<Boolean>();
		int i;
		for(i = 0; i < length; ++i){
			bitField.add((mes.charAt(i) == '0') ? false : true);
		}
		for(; i < piecesCount; ++i){
			bitField.add(false);
		}
		return bitField;
	}
	
	private SocketChannel clientChannel;
	private String myId;
	private String metaHash;
	private int piecesCount;
	private int	MES_LENGTH = 19;
	private int HASH_LENGTH = 4;
	private int ID_LENGTH = 4;
	private int MAX_BUF_SIZE = 100;
	private int INT_LENGTH = 2;
	private int CHAR_BITS = 16;
	private int CHAR_MAX = 65 536;
	private int BIT_FIELD = 5;
	private String PROTOCOL = "Protocol BitTorrent";
	private Selector selector;
	private List<Peer> peers;
	private List<Boolean> hasPieces;
}