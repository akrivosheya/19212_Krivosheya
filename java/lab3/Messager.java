import java.net.*;
import java.io.*;
import java.util.concurrent.*;
import java.util.*;
import java.nio.channels.*;
import java.nio.*;

class Messager implements Runnable{
	
	Messager(int port, Map<Integer, Peer> peers, SocketChannel clientChannel, SelectionKey selectionKey,
	Request request, List<Boolean> isLoading, List<Boolean> hasPieces, int fileLength, int pieceLength) {
		this.port = port;
		this.peers = peers;
		this.clientChannel = clientChannel;
		this.selectionKey = selectionKey;
		this.request = request;
		this.isLoading = isLoading;
		this.hasPieces = hasPieces;
		this.fileLength = fileLength;
		this.pieceLength = pieceLength;
	}
	
	@Override
	public void run() {
		try{
			/*try{
				Thread.sleep(1000);
			}
			catch(InterruptedException ex){
				System.out.println("LOL");
			}*/
			int length = readInt(INT_LENGTH);
			int index = readInt(INDEX_LENGTH);
			int piece, offset, blockLength;
			byte text[];
			synchronized(peers.get(port)){
				switch(index){
					case CHOCK:
						peers.get(port).setIsChocked(true);
						break;
					case UNCHOCK:
						peers.get(port).setIsChocked(false);
						break;
					case INTERESTED:
						peers.get(port).setIsInterested(true);
						break;
					case UNINTERESTED:
						peers.get(port).setIsInterested(false);
						break;
					case HAVE:
						piece = readInt(INT_LENGTH);
			System.out.println(port + " have " + piece);
						peers.get(port).hasPieces().set(piece, true); 
						break;
					case REQUEST:
						//peers.get(port).setIsLoading(true);
						piece = readInt(INT_LENGTH);
						offset = readInt(INT_LENGTH);
						blockLength = readInt(INT_LENGTH);
			System.out.println(port + " rec " + piece + " " + offset);
						text = new byte[blockLength + 4];
						try{
							synchronized(request){
								request.setPiece(piece);
								request.setOffset(offset);
								request.setBlockLength(blockLength);
								request.setText(text);
								request.setMode(READ);
								request.notify();
								request.wait();
								text[0] = ((byte)(piece >> CHAR_BITS));
								text[1] = ((byte)(piece % CHAR_MAX));
								text[2] = ((byte)(offset >> CHAR_BITS));
								text[3] = ((byte)(offset % CHAR_MAX));
								sendMessage(blockLength + 2 * INT_LENGTH, PIECE, text);
							}
						}
						catch(InterruptedException ex){
							text = null;
							sendMessage(0, CHOCK, text);
						}
						break;
					case PIECE:
						piece = readInt(INT_LENGTH);
						offset = readInt(INT_LENGTH);
						text = new byte[length - INT_LENGTH * 2];
						readByteArr(length - INT_LENGTH * 2, text);
						try{
							synchronized(request){
								request.setPiece(piece);
								request.setOffset(offset);
								request.setBlockLength(length - INT_LENGTH * 2);
								request.setText(text);
								request.setMode(WRITE);
								request.notify();
								request.wait();
							}
						}
						catch(InterruptedException ex){
							text = null;
							sendMessage(0, CHOCK, text);
						}
						int currentPieceLength = (piece == hasPieces.size() - 1 &&
							fileLength % pieceLength != 0) ? 
							fileLength % pieceLength : pieceLength;
						if(length - INT_LENGTH * 2 + offset == currentPieceLength){
							hasPieces.set(piece, true);
							isLoading.set(piece, false);
							System.out.println("Loaded " + piece + " piece");
						}
						break;
					case CANCEL:
						piece = readInt(INT_LENGTH);
						offset = readInt(INT_LENGTH);
						blockLength = readInt(INT_LENGTH);
						//peers.get(port).setIsLoading(false);
						break;
					default:
			System.out.println(port + " undefinded " + index);
						break;
				}
			}
			peers.get(port).setIsBusy(false);
		}
		catch (IOException ex) {
			selectionKey.cancel();
			peers.remove(port);
			ex.printStackTrace();
		}
		catch (RuntimeException ex) {
			//selectionKey.cancel();
			//peers.remove(port);
			System.out.println(port + "Can't read");
			ex.printStackTrace();
			return;
		}
		peers.get(port).setIsBusy(false);
	}
	
	private int readInt(int length) throws IOException{
        ByteBuffer buf = ByteBuffer.allocateDirect(length);
		int numb = 0;
		clientChannel.read(buf);
		buf.flip();
		for(int i = 0; i < length; ++i){
			numb = numb * CHAR_BITS + buf.get();
		}
		return numb;
	}
	
	private void readByteArr(int length, byte[] text) throws IOException{
        ByteBuffer buf = ByteBuffer.allocateDirect(length);
		clientChannel.read(buf);
		buf.flip();
		buf.get(text);
	}
	
	private int toInt(String line){
		int numb = 0;
		for(int i = 0; i < line.length(); ++i){
			numb = numb * 10 + Character.digit(line.charAt(i), Character.MAX_RADIX);
		}
		return numb;
	}
	
	private void sendMessage(int length, int index, byte[] load) throws IOException{
        ByteBuffer buf = ByteBuffer.allocateDirect(length + INT_LENGTH + INDEX_LENGTH);
		buf.put((byte)(length >> CHAR_BITS));
		buf.put((byte)(length % CHAR_MAX));
		buf.put((byte)index);
		if(load != null){
			buf.put(load);
		}
		buf.flip();
		clientChannel.write(buf);
	}
	
	private int port;
	private int fileLength;
	private int pieceLength;
	private Map<Integer, Peer> peers;
	private List<Boolean> isLoading;
	private List<Boolean> hasPieces;
	private SocketChannel clientChannel;
	private Request request;
	private SelectionKey selectionKey;
	private int INT_LENGTH = 2;
	private int INDEX_LENGTH = 1;
	private int CHAR_BITS = 16;
	private int CHAR_MAX = 65536;
	private final int CHOCK = 0;
	private final int UNCHOCK = 1;
	private final int INTERESTED = 2;
	private final int UNINTERESTED = 3;
	private final int HAVE = 4;
	private final int BIT_FIELD = 5;
	private final int REQUEST = 6;
	private final int PIECE = 7;
	private final int CANCEL = 8;
	private final char READ = 'r';
	private final char WRITE = 'w';
}