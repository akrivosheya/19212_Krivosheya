import java.net.*;
import java.io.*;
import java.util.concurrent.*;
import java.util.*;
import java.nio.channels.*;
import java.nio.*;

public class TorrentClient {
	TorrentClient(List<Integer> addreses, List<Boolean> hasPieces, int port){
		this.addresses = addreses;
		this.hasPieces = hasPieces;
		isLoading = new ArrayList<Boolean>(hasPieces.size());
		for(int i = 0; i < hasPieces.size(); ++i){
			isLoading.add(false);
		}
		hasFile = true;
		for(Boolean hasPiece : hasPieces){
			if(!hasPiece){
				hasFile = false;
				break;
			}
		}
		try{
			serverChannel = ServerSocketChannel.open();
			serverChannel.configureBlocking(false);
			ServerSocket serverSocket = serverChannel.socket();
			selector = Selector.open();
			InetSocketAddress inetSocketAddress = new InetSocketAddress(port);
			serverSocket.bind(inetSocketAddress);
			serverChannel.register(selector, SelectionKey.OP_ACCEPT);
		}
		catch(IOException ex){
			serverChannel = null;
			HAS_READ_META = true;
			return;
		}
			
		try(Scanner scan = new Scanner(new File("meta.torrent"))){
			String line = scan.nextLine();
			BencodeableDictionary torrent = 
				new BencodeableDictionary(ByteBuffer.wrap(line.getBytes()));
			length = torrent.get(new BencodableByteString("length".getBytes())).hashCode();
			pieceLength = torrent.get(
				new BencodableByteString("pieceLength".getBytes())).hashCode();
			BencodableByteString benString = 
				(BencodableByteString)(torrent.get(new BencodableByteString("name".getBytes())));
			name = new String(benString.getByteString());
		}
		catch(IOException | DecodingBencodingException ex){
			HAS_READ_META = false;
		}
		threadPool = new ScheduledThreadPoolExecutor(N);
		threadPool.execute(new FileThread(name, pieceLength, requests));
		
		for(Integer anotherPort : addresses){
			try{
				SocketChannel channel = SocketChannel.open(new InetSocketAddress(anotherPort));
				peers.put(anotherPort, new Peer(false, true));
				channel.configureBlocking(false);
				channel.register(selector, SelectionKey.OP_READ | SelectionKey.OP_WRITE);
			}
			catch(IOException ex){
				System.out.println("Can't connect to " + anotherPort);
			}
		}
		selectorWork();
	}
	
	private void selectorWork(){
		while (true) {
			int count;
			try{
				count = selector.select();
			}
			catch (IOException e){
				e.printStackTrace();
				continue;
			}
			if (count == 0) {
				continue;
			}
			Iterator<SelectionKey> itor = selector.selectedKeys().iterator();
			while (itor.hasNext()) {
				SelectionKey selectionKey = itor.next();
				itor.remove();
				try {
					SocketChannel clientChannel;
					if(selectionKey.isAcceptable()){
						clientChannel = serverChannel.accept();
						int port =((InetSocketAddress)clientChannel.getRemoteAddress()).getPort();
						synchronized(peers){
							peers.put(port, new Peer(true, false));
						}
						clientChannel.configureBlocking(false);
						clientChannel.register(selector, SelectionKey.OP_READ | SelectionKey.OP_WRITE);
						continue;
					}
					clientChannel = (SocketChannel)selectionKey.channel();
					int port =((InetSocketAddress)clientChannel.getRemoteAddress()).getPort();
					Peer currentPeer;
					synchronized(peers){
						currentPeer = peers.get(port);
						if(currentPeer.isBusy()){
							continue;
						}
					}
					if(selectionKey.isReadable()){
						synchronized(currentPeer){
							currentPeer.setIsBusy(true);
							if(!currentPeer.isHandShaked() && currentPeer.isLocal()){
								int piecesCount = length / pieceLength + ((length % pieceLength == 0) ? 0 : 1);
								threadPool.execute(new LocalHandShaker(clientChannel, metaHash, myId, 
								port, peers, piecesCount, hasPieces, selectionKey));
								continue;
							}
							threadPool.execute(new Messager(port, peers, clientChannel, selectionKey, requests, isLoading, hasPieces, length, pieceLength));
						}
					}
					else if(selectionKey.isWritable()){
						synchronized(currentPeer){
							if(!currentPeer.isHandShaked() && currentPeer.isRemote()){
								int piecesCount = length / pieceLength + ((length % pieceLength == 0) ? 0 : 1);
								currentPeer.setIsBusy(true);
								threadPool.execute(new RemoteHandShaker(clientChannel, metaHash, myId, 
								port, peers, piecesCount, hasPieces, selectionKey));
							}
							else if(!hasFile && currentPeer.isHandShaked()){
								for(int i = 0; i < hasPieces.size(); ++i){
									if(hasPieces.get(i) && !currentPeer.knowHasPieces().get(i)){
										System.out.println("have " + i + " to " + port);
										byte[] text = new byte[INT_LENGTH];
										text[0] = (byte)(i >> CHAR_BITS);
										text[1] = (byte)(i % CHAR_MAX);
										sendMessage(INT_LENGTH, HAVE, text, clientChannel);
										currentPeer.knowHasPieces().set(i, true);
									}
									else if(!hasPieces.get(i) && currentPeer.hasPieces().get(i) && !isLoading.get(i)){
										int currentPieceLength = (i == hasPieces.size() - 1 &&
											length % pieceLength != 0) ? 
											length % pieceLength : pieceLength;
										isLoading.set(i, true);
										peers.get(port).isLoading().set(i, true);
										currentPeer.setIsBusy(true);
										threadPool.execute(new Loader(isLoading,
											i, port, peers, currentPieceLength, clientChannel, selectionKey));
										break;
									}
								}
							}
						}
					}
				} 
				catch (IOException e) {
					e.printStackTrace();
					selectionKey.cancel();
				}
				catch (RuntimeException e) {
					e.printStackTrace();
					selectionKey.cancel();
				}
			}
		}
	}
	
	private void sendMessage(int length, int index, byte[] load, SocketChannel clientChannel) throws IOException{
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
	
	public boolean hasServerSocket(){
		return serverChannel != null;
	}
	
	public boolean hasReadMeta(){
		return HAS_READ_META;
	}
	
	private Executor threadPool;
	private Queue<Request> requests = new ArrayDeque<Request>();
	private int N = 10;
	private ServerSocketChannel serverChannel;
	private Selector selector;
	private int length;
	private int pieceLength;
	private String name;
	private List<Integer> addresses;
	private boolean HAS_READ_META = true;
	private int BLOCK_LENGTH = 10;
	private Map<Integer, Peer> peers = new HashMap<Integer, Peer>();
	private String myId = "cod3";
	private String metaHash = "code";
	private boolean hasFile;
	private List<Boolean> hasPieces;
	private List<Boolean> isLoading;
	private int INT_LENGTH = 2;
	private int INDEX_LENGTH = 1;
	private int CHAR_BITS = 16;
	private int CHAR_MAX = 65536;
	private final int HAVE = 4;
}