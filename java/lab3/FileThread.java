import java.io.*;
import java.util.*;

public class FileThread implements Runnable{
	public FileThread(String name, int pieceLength, Queue<Request> requests){
		this.name = name;
		this.pieceLength = pieceLength;
		this.requests = requests;
	}
	
	@Override
	public void run(){
		try(RandomAccessFile file = new RandomAccessFile(name, "rw")){
			synchronized(requests){
				while(true){
					requests.wait();
					Request request = requests.poll();
					file.seek(request.getOffset() + request.getPiece() * pieceLength);
					switch(request.getMode()){
						case READ:
							file.read(request.getText(), INFO_LENGTH, request.getBlockLength());
							break;
						case WRITE:
							file.write(request.getText());
							break;
					}
					request.setIsDone(true);
					requests.notify();
				}
			}
		}
		catch(IOException ex){
			requests.notify();
			ex.printStackTrace();
		}
		catch(InterruptedException ex){
			requests.notify();
			ex.printStackTrace();
		}
	}
	
	private String name;
	private Queue<Request> requests;
	private int pieceLength;
	private final char READ = 'r';
	private final char WRITE = 'w';
	private int INFO_LENGTH = 4;
}