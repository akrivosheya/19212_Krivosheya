import java.net.*;
import java.io.*;
import java.util.concurrent.*;
import java.util.*;
import java.nio.channels.*;
import java.nio.*;

public class RemoteHandShaker implements Runnable{
	
	RemoteHandShaker(SocketChannel clientChannel, String metaHash, String myId, 
	int port, Map<Integer, Peer> peers, int piecesCount, List<Boolean> hasPieces, SelectionKey selectionKey) {
		this.clientChannel = clientChannel;
		this.metaHash = metaHash;
		this.myId = myId;
		this.selector = selector;
		this.port = port;
		this.peers = peers;
		this.piecesCount = piecesCount;
		this.hasPieces = hasPieces;
		this.selectionKey = selectionKey;
	}
	
	@Override
	public void run() {
		try{
			ByteBuffer buf = ByteBuffer.allocateDirect(1 + MES_LENGTH + HASH_LENGTH + ID_LENGTH);
			buf.put((byte) MES_LENGTH);
			for(int i = 0; i < MES_LENGTH; ++i){
				buf.put((byte)PROTOCOL.charAt(i));
			}
			for(int i = 0; i < HASH_LENGTH; ++i){
				buf.put((byte)metaHash.charAt(i));
			}
			for(int i = 0; i < ID_LENGTH; ++i){
				buf.put((byte)myId.charAt(i));
			}
			buf.flip();
			clientChannel.write(buf);
			int length = getHasPiecesLength();
			buf = ByteBuffer.allocateDirect(length + 3);
			buf.put((byte)(length >> CHAR_BITS));
			buf.put((byte)(length % CHAR_MAX));
			buf.put((byte)BIT_FIELD);
			createBitField(buf, length);
			buf.flip();
			clientChannel.write(buf);
			while(!selectionKey.isReadable()){}
			length = readInt(INT_LENGTH);
			buf = ByteBuffer.allocateDirect(1);
			clientChannel.read(buf);
			buf.flip();
			int index = buf.get();
			if(index != BIT_FIELD){
				return;
			}
			buf = ByteBuffer.allocateDirect(length);
			byte[] mes = new byte[length];
			clientChannel.read(buf);
			buf.flip();
			buf.get(mes);
			synchronized(peers.get(port)){
				peers.get(port).setHasPieces(getBitField(length, new String(mes)));
				peers.get(port).setKnowHasPieces(new ArrayList<Boolean>(hasPieces));
				List<Boolean> isLoading = new ArrayList<Boolean>(hasPieces.size());
				for(int i = 0; i < hasPieces.size(); ++i){
					isLoading.add(false);
				}
				peers.get(port).setIsLoading(isLoading);
				peers.get(port).setIsHandShaked(true);
				peers.get(port).setIsBusy(false);
			}
		}
		catch (IOException ex) {
			selectionKey.cancel();
			peers.remove(port);
			ex.printStackTrace();
		}
		catch (RuntimeException ex) {
			selectionKey.cancel();
			peers.remove(port);
			ex.printStackTrace();
		}
	}
	
	private void createBitField(ByteBuffer buf, int length){
		for(int i = 0; i < length; ++i){
			buf.put((byte)((hasPieces.get(i)) ? '1' : '0'));
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
	
	private int readInt(int length) throws IOException{
        ByteBuffer buf = ByteBuffer.allocateDirect(length);
		clientChannel.read(buf);
		buf.flip();
		int numb = 0;
		for(int i = 0; i < length; ++i){
			numb = numb * CHAR_BITS + buf.get();
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
	private int CHAR_MAX = 65536;
	private int BIT_FIELD = 5;
	private String PROTOCOL = "Protocol BitTorrent";
	private Selector selector;
	private int port;
	private Map<Integer, Peer> peers;
	private List<Boolean> hasPieces;
	private SelectionKey selectionKey;
}