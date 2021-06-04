import java.net.*;
import java.io.*;
import java.util.concurrent.*;
import java.util.*;
import java.nio.channels.*;
import java.nio.*;

public class TorrentClient {
	TorrentClient(List<String> addreses){
		this.addresses = addreses;
		try(Scanner scan = new Scanner(new File("meta.torrent"))){
			serverChannel = ServerSocketChannel.open();
			serverChannel.configureBlocking(false);
			ServerSocket serverSocket = serverChannel.socket();
			selector = Selector.open();
			InetSocketAddress inetSocketAddress = new InetSocketAddress(PORT);
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
		//threadPool.execute(new MainWorker(selector, serverSocket, threadPool, name, length, pieceLength));*/
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
				if(selectionKey.isAcceptable()){
					try {
						List<Boolean> hasPieces = new ArrayList<Boolean>();
						hasPieces.add(true);
						hasPieces.add(true);
						hasPieces.add(false);
						hasPieces.add(true);
						SocketChannel clientChannel = serverChannel.accept();
						int piecesCount = length / pieceLength + ((length % pieceLength == 0) ? 0 : 1);
						threadPool.execute(new LocalHandShaker(clientChannel, metaHash, myId, 
						peers, piecesCount, hasPieces));
					} 
					catch (IOException e) {
						e.printStackTrace();
						selectionKey.cancel();
					}
				}
			}
		}
	}
	
	public boolean hasServerSocket(){
		return serverChannel != null;
	}
	
	public boolean hasReadMeta(){
		return HAS_READ_META;
	}
	
	public void getFile(){
		/*int i;
		for(i = 0; i < length / pieceLength; ++i){
			Socket socket;
			try{
				socket = new Socket(peers.get(i % peers.size()), PORT);
			}
			catch(UnknownHostException ex){
				ex.printStackTrace();
				return;
			}
			catch(IOException ex){
				ex.printStackTrace();
				return;
			}
				loadThreadPool.execute(new LoadWorker(socket, name, length, pieceLength, i));
		}
		++i;
		if(length % pieceLength != 0){
			Socket socket;
			try{
				socket = new Socket(peers.get(i % peers.size()), PORT);
			}
			catch(UnknownHostException ex){
				ex.printStackTrace();
				return;
			}
			catch(IOException ex){
				ex.printStackTrace();
				return;
			}
			loadThreadPool.execute(new LoadWorker(socket, name, length % pieceLength, pieceLength, i));
		}
		//while(loadThreadPool.getActiveCount() != 0){}
		try(File file = new File(name);
		FileWriter fileWriter = new FileWriter(file)){
			file.createNewFile();
			for(i = 0; i < length / pieceLength; ++i){
				File
				Socket socket = new Socket(peers.get(i % peers.size()), PORT);
				loadThreadPool.execute();
			}
		}*/
	}
	
	private int PORT = 2048;
	private Executor threadPool;
	private Executor loadThreadPool;
	private int N = 10;
	private ServerSocketChannel serverChannel;
	private Selector selector;
	private int length;
	private int pieceLength;
	private String name;
	private List<String> addresses;
	private boolean HAS_READ_META = true;
	private int BLOCK_LENGTH = 10;
	private List<Peer> peers = new ArrayList<Peer>();
	private String myId = "cod2";
	private String metaHash = "code";
}