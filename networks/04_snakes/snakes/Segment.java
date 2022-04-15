package snakes;

public class Segment{
	public Segment(int positionX, int positionY, boolean isHead){
		this.positionX = positionX;
		this.positionY = positionY;
		this.isHead = isHead;
	}
	
	public void changePosition(int changeX, int changeY){
		positionX += changeX;
		positionY += changeY;
	}
	
	public void setX(int newX){
		positionX = newX;
	}
	
	public void setY(int newY){
		positionY = newY;
	}
	
	public int getX(){
		return positionX;
	}
	
	public int getY(){
		return positionY;
	}
	
	public boolean isHead(){
		return isHead;
	}
	
	private int positionX;
	private int positionY;
	private boolean isHead;
}