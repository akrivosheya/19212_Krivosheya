import java.io.*;

public class FileThread implements Runnable{
	public FileThread(String name, int pieceLength, Request request){
		this.name = name;
		this.pieceLength = pieceLength;
		this.request = request;
	}
	
	@Override
	public void run(){
		try(RandomAccessFile file = new RandomAccessFile(name, "rw")){
			synchronized(request){
				while(true){
					request.wait();
					file.seek(request.getOffset() + request.getPiece() * pieceLength);
					switch(request.getMode()){
						case READ:
							file.read(request.getText(), INFO_LENGTH, request.getBlockLength());
							break;
						case WRITE:
							file.write(request.getText());
							break;
					}
					request.notify();
				}
			}
		}
		catch(IOException ex){
			request.notify();
			ex.printStackTrace();
		}
		catch(InterruptedException ex){
			request.notify();
			ex.printStackTrace();
		}
	}
	
	private String name;
	private Request request;
	private int pieceLength;
	private final char READ = 'r';
	private final char WRITE = 'w';
	private int INFO_LENGTH = 4;
}