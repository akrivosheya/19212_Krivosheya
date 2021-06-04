import java.net.*;
import java.io.*;
import java.util.*;

public class Peer{
	public Peer(List<Boolean> hasPieces, boolean isChocked, boolean isInterested, Socket socket){
		this.hasPieces = hasPieces;
		this.isChocked = isChocked;
		this.isInterested = isInterested;
		this.socket = socket;
	}
	
	public List<Boolean> hasPieces(){
		return hasPieces;
	}
	
	public boolean isChocked(){
		return isChocked;
	}
	
	public boolean isInterested(){
		return isInterested;
	}
	
	public Socket getSocke(){
		return socket;
	}
	
	public void setIsChocked(boolean flag){
		isChocked = flag;
	}
	
	public void setIsInterested(boolean flag){
		isInterested = flag;
	}

	private List<Boolean> hasPieces;
	private boolean isChocked;
	private boolean isInterested;
	private Socket socket;
}