package snakes;

import java.util.*;

public class Player{
	public Player(int headX, int headY, int code){
		head = new Segment(headX, headY, true);
		tail = head;
		segments.add(head);
		this.code = code;
	}
	
	@Override
	public String toString(){
		StringBuilder stringBuilder = new StringBuilder("");
		stringBuilder.append(code + " " + points + " " + direction + "\n");
		for(Segment segment : segments){
			stringBuilder.append(segment.getX() + " " + segment.getY() + " " + segment.isHead() + "\n");
		}
		return stringBuilder.toString();
	}
	
	public Player(int code, int points, List<DataSegment> segmentsData, Direction direction){
		this.code = code;
		this.points = points;
		this.direction = direction;
		for(DataSegment data : segmentsData){
			segments.add(new Segment(data.getX(), data.getY(), data.isHead()));
		}
		head = segments.get(0);
		tail = segments.get(segments.size() - 1);
	}
	
	public void addPoints(int points){
		this.points += points;
	}
	
	public int getPoints(){
		return points;
	}
	
	public Direction getDirection(){
		return direction;
	}
	
	public void changeDirection(Direction newDirection){
		switch(direction){
			case UP:
				if(newDirection != Direction.DOWN && alreadyMoved){
					direction = newDirection;
					alreadyMoved = false;
				}
				break;
			case DOWN:
				if(newDirection != Direction.UP && alreadyMoved){
					direction = newDirection;
					alreadyMoved = false;
				}
				break;
			case LEFT:
				if(newDirection != Direction.RIGHT && alreadyMoved){
					direction = newDirection;
					alreadyMoved = false;
				}
				break;
			case RIGHT:
				if(newDirection != Direction.LEFT && alreadyMoved){
					direction = newDirection;
					alreadyMoved = false;
				}
				break;
		}
	}
	
	public void move(int sizeX, int sizeY){
		int currentX = head.getX();
		int currentY = head.getY();
		int oldX = currentX;
		int oldY = currentY;
		switch(direction){
			case UP:
				if(currentX == 0){
					head.setX(sizeX - 1);
				}
				else{
					head.changePosition(-1, 0);
				}
				break;
			case DOWN:
				if(currentX == sizeX - 1){
					head.setX(0);
				}
				else{
					head.changePosition(1, 0);
				}
				break;
			case LEFT:
				if(currentY == 0){
					head.setY(sizeY - 1);
				}
				else{
					head.changePosition(0, -1);
				}
				break;
			case RIGHT:
				if(currentY == sizeY - 1){
					head.setY(0);
				}
				else{
					head.changePosition(0, 1);
				}
				break;
		}
		for(Segment segment : segments){
			if(!segment.isHead()){
				oldX = segment.getX();
				oldY = segment.getY();
				segment.setX(currentX);
				segment.setY(currentY);
				currentX = oldX;
				currentY = oldY;
			}
		}
		alreadyMoved = true;
	}
	
	public DataSegment getTail(){
		return new DataSegment(tail.getX(), tail.getY(), tail.isHead());
	}
	
	public DataSegment getHead(){
		return new DataSegment(head.getX(), head.getY(), head.isHead());
	}
	
	public int getCode(){
		return code;
	}
	
	public boolean containsSegment(int x, int y){
		for(Segment segment : segments){
			if(segment.getX() == x && segment.getY() == y){
				return true;
			}
		}
		return false;
	}
	
	public DataSegment getSegment(int x, int y){
		for(Segment segment : segments){
			if(segment.getX() == x && segment.getY() == y){
				return new DataSegment(x, y, segment.isHead());
			}
		}
		return null;
	}
	
	public List<DataSegment> getAllSegments(){
		List<DataSegment> dataSegments = new ArrayList<DataSegment>();
		for(Segment segment : segments){
			dataSegments.add(new DataSegment(segment.getX(), segment.getY(), segment.isHead()));
		}
		return dataSegments;
	}
	
	public void addSegment(int x, int y){
		segments.add(new Segment(x, y, false));
		tail = segments.get(segments.size() - 1);
	}
	
	public enum Direction{UP, DOWN, LEFT, RIGHT};
	
	private int code;
	private int points = 0;
	private Segment head = null;
	private Segment tail = null;
	private List<Segment> segments = new ArrayList<Segment>();
	private Direction direction = Direction.RIGHT;
	private boolean alreadyMoved = false;
}