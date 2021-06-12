import java.net.*;
import java.io.*;
import java.util.*;

public class Peer{
	public Peer(boolean isLocal, boolean isRemote){
		this.isLocal = isLocal;
		this.isRemote = isRemote;
	}
	
	public List<Boolean> hasPieces(){
		return hasPieces;
	}
	
	public List<Boolean> knowHasPieces(){
		return knowHasPieces;
	}
	
	public boolean isChocked(){
		return isChocked;
	}
	
	public boolean isLoading(){
		return isLoading;
	}
	
	public boolean isBusy(){
		return isBusy;
	}
	
	public boolean isLocal(){
		return isLocal;
	}
	
	public boolean isRemote(){
		return isRemote;
	}
	
	public boolean isInterested(){
		return isInterested;
	}
	
	public boolean isHandShaked(){
		return isHandShaked;
	}
	
	public void setIsChocked(boolean flag){
		isChocked = flag;
	}
	
	public void setIsInterested(boolean flag){
		isInterested = flag;
	}
	
	public boolean hasRequest(){
		return hasRequest;
	}

	public void setHasPieces(List<Boolean> hasPieces){
		this.hasPieces = hasPieces;
	}
	
	public void setKnowHasPieces(List<Boolean> knowHasPieces){
		this.knowHasPieces = knowHasPieces;
	}
	
	public void setIsBusy(boolean flag){
		isBusy = flag;
	}
	
	public void setIsHandShaked(boolean flag){
		isHandShaked = flag;
	}
	
	public void setIsLoading(boolean flag){
		isLoading = flag;
	}
	
	private List<Boolean> hasPieces;
	private List<Boolean> knowHasPieces;
	private boolean isChocked = false;
	private boolean isInterested = false;
	private boolean hasRequest = false;
	private boolean isHandShaked = false;
	private boolean isBusy;
	private boolean isLocal;
	private boolean isRemote;
	private boolean isLoading = false;
}