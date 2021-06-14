import java.net.*;
import java.io.*;
import java.util.concurrent.*;
import java.util.*;
import java.nio.channels.*;
import java.nio.*;

public class Loader implements Runnable{
	Loader(List<Boolean> isLoading, int piece,
	int port, Map<Integer, Peer> peers, int pieceLength, SocketChannel channel, SelectionKey selectionKey){
		this.isLoading = isLoading;
		this.piece = piece;
		this.port = port;
		this.peers = peers;
		this.pieceLength = pieceLength;
		this.channel = channel;
		this.selectionKey = selectionKey;
	}
	
	@Override
	public void run(){
		int blocks = pieceLength / BLOCK_LENGTH + ((pieceLength % BLOCK_LENGTH == 0) ? 0 : 1);
		int length, index, blockLength = BLOCK_LENGTH, recPiece, recOffset, offset = 0;
		byte[] text = new byte[pieceLength];
		try{
			for(int i = 0; i < blocks; ++i){
				blockLength = (i == blocks - 1 && pieceLength % BLOCK_LENGTH != 0) ? 
					pieceLength % BLOCK_LENGTH : BLOCK_LENGTH;
				byte[] mes = new byte[]{(byte)(piece >> CHAR_BITS), (byte)(piece % CHAR_MAX),
					(byte)(offset >> CHAR_BITS), (byte)(offset % CHAR_MAX),
					(byte)(blockLength >> CHAR_BITS), (byte)(blockLength % CHAR_MAX)};
				sendMessage(REQUEST_LENGTH, REQUEST, mes);
				offset += BLOCK_LENGTH;
			}
		}
		catch(IOException ex){
			selectionKey.cancel();
			peers.remove(port);
			ex.printStackTrace();
			isLoading.set(piece, false);
		}
		catch(RuntimeException ex){
			selectionKey.cancel();
			peers.remove(port);
			ex.printStackTrace();
			isLoading.set(piece, false);
		}
		synchronized(peers){
			peers.get(port).setIsBusy(false);
		}
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
		channel.write(buf);
	}
	
	private void readByteArr(int length, byte[] text, int offset) throws IOException{
        ByteBuffer buf = ByteBuffer.allocateDirect(length);
		channel.read(buf);
		buf.flip();
		buf.get(text, offset, length);
	}
	
	private int readInt(int length) throws IOException{
        ByteBuffer buf = ByteBuffer.allocateDirect(length);
		channel.read(buf);
		buf.flip();
		int numb = 0;
		for(int i = 0; i < length; ++i){
			numb = numb * CHAR_BITS + buf.get();
		}
		return numb;
	}
	
	private List<Boolean> isLoading;
	private int piece;
	private int port;
	private Map<Integer, Peer> peers;
	private int pieceLength;
	private int BLOCK_LENGTH = 50;
	private SocketChannel channel;
	private SelectionKey selectionKey;
	private int CANCEL_LENGTH = 6;
	private int REQUEST_LENGTH = 6;
	private int REQUEST = 6;
	private int CANCEL = 8;
	private int CHAR_BITS = 16;
	private int CHAR_MAX = 65536;
	private int INT_LENGTH = 2;
	private int INDEX_LENGTH = 1;
	private final char WRITE = 'w';
	private final int CHOCK = 0;
	private final int PIECE = 7;
}