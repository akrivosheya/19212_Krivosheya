package snakes;

public class DataSegment{
	public DataSegment(int x, int y, boolean isHead){
		this.x = x;
		this.y = y;
		this.isHead = isHead;
	}
	
	public int getX(){
		return x;
	}
	
	public int getY(){
		return y;
	}
	
	public boolean isHead(){
		return isHead;
	}
	
	private int x;
	private int y;
	private boolean isHead;
}