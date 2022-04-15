package snakes;

import java.util.*;
import snakes.Player;

public class Unit{
	public Unit(int code, int points, List<DataSegment> segments, Player.Direction direction){
		this.code = code;
		this.points = points;
		if(segments != null){
			this.segments = segments;
		}
		direction = direction;
	}
	
	public int getCode(){
		return code;
	}
	
	public int getPoints(){
		return points;
	}
	
	public List<DataSegment> getSegments(){
		return segments;
	}
	
	public Player.Direction getDirection(){
		return direction;
	}
	
	private int code;
	private int points;
	private List<DataSegment> segments = new ArrayList<DataSegment>();
	private Player.Direction direction;
}