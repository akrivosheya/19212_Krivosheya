package snakes;

import java.util.*;
import snakes.*;

public class Field{
	public Field(int sizeX, int sizeY){
		this.sizeX = sizeX;
		this.sizeY = sizeY;
		field = new int[sizeX * sizeY];
	}
	
	public boolean isItemCode(int code){
		if(ITEM_CODE == code || EMPTY == code){
			return true;
		}
		return false;
	}
	
	public List<Unit> getItems(){
		List<Unit> items = new ArrayList<Unit>();
		for(int i = 0; i < sizeX; ++i){
			for(int j = 0; j < sizeY; ++j){
				if(field[i + j * sizeX] == ITEM_CODE){
					List<DataSegment> segments = new ArrayList<DataSegment>();
					segments.add(new DataSegment(i, j, false));
					items.add(new Unit(ITEM_CODE, 0, segments, Player.Direction.UP));
				}
			}
		}
		return items;
	}
	
	public void clear(){
		for(int i = 0; i < sizeX * sizeY; ++i){
			field[i] = EMPTY;
		}
	}
	
	public boolean put(Unit unit){
		for(DataSegment segment : unit.getSegments()){
			if(field[segment.getX() + segment.getY() * sizeX] != EMPTY){
				return false;
			}
			field[segment.getX() + segment.getY() * sizeX] = unit.getCode();
		}
		return true;
	}
	
	public void movePlayers(Map<Integer, Player> players){
		players.forEach((Integer key, Player player) -> {
			DataSegment oldTail = player.getTail();
			player.move(sizeX, sizeY);
			DataSegment head = player.getHead();
			field[oldTail.getX() + oldTail.getY() * sizeX] = EMPTY;
			int cell = field[head.getX() + head.getY() * sizeX];
			if(cell == EMPTY){
				field[head.getX() + head.getY() * sizeX] = player.getCode();
			}else if(cell == ITEM_CODE){
				WellFed wellFed = new WellFed(player.getCode(), oldTail);
				wellFedPlayers.add(wellFed);
				field[head.getX() + head.getY() * sizeX] = player.getCode();
				--food;
			}else{
				Point point = new Point(head.getX(), head.getY());
				if(!conflictingPlayers.containsKey(point)){
					conflictingPlayers.put(point, new ArrayList<Integer>());
				}
				conflictingPlayers.get(point).add(player.getCode());
				if(!conflictingPlayers.get(point).contains(cell)){
					conflictingPlayers.get(point).add(cell);
				}
			}
		});
	}
	
	public void collectGarbage(Map<Integer, Player> players){
		conflictingPlayers.forEach((Point point, List<Integer> codes) -> {
			int i = 0;
			while(i < players.size()){
				if(players.containsKey(codes.get(i).intValue())){
					if(players.get(codes.get(i).intValue()).containsSegment(point.x, point.y)){
						++i;
					}
					else{
						codes.remove(i);
					}
				}
			}
			int points = 0;
			int killer = EMPTY;
			for(Integer code : codes){
				DataSegment segment = players.get(code.intValue()).getSegment(point.x, point.y);
				if(segment != null && segment.isHead()){
					deadPlayers.add(code);
					points += POINTS_FOR_KILLING;
				}
				else{
					killer = code.intValue();
				}
			}
			if(killer != EMPTY){
				players.get(killer).addPoints(points);
			}
		});
		conflictingPlayers.clear();
		removeDeadPlayers(players);
	}
	
	public void increasePlayers(Map<Integer, Player> players){
		for(WellFed wellFed : wellFedPlayers){
			if(field[wellFed.futureTail.getX() + wellFed.futureTail.getY() * sizeX] != EMPTY){
				deadPlayers.add(field[wellFed.futureTail.getX() + wellFed.futureTail.getY() * sizeX]);
				players.get(wellFed.player).addPoints(POINTS_FOR_KILLING);
			}
			field[wellFed.futureTail.getX() + wellFed.futureTail.getY() * sizeX] = wellFed.player;
			players.get(wellFed.player).addSegment(wellFed.futureTail.getX(), wellFed.futureTail.getY());
		}
		wellFedPlayers.clear();
		removeDeadPlayers(players);
	}
	
	public boolean putNewUnit(int code, int x[], int y[]){
		Random random = new Random();
		for(int i = 0; i < MAX_TRYING; ++i){
			int tryingX = random.nextInt(sizeX - 1);
			int tryingY = random.nextInt(sizeY - 1);
			if(isEmptyAround(code, tryingX, tryingY)){
				field[tryingX +tryingY * sizeX] = code;
				if(x != null){
					x[0] = tryingX;
				}
				if(y != null){
					y[0] = tryingY;
				}
				return true;
			}
		}
		return false;
	}
	
	public String getField(){
		StringBuilder stringField = new StringBuilder("");
		char nextSymb;
		int currentCode;
		for(int i = 0; i < sizeX; ++i){
			for(int j = 0; j < sizeY; ++j){
				currentCode = field[i + sizeX * j];
				if(currentCode == ITEM_CODE){
					stringField.append(ITEM_SYMBOL);
				}else if(currentCode == EMPTY){
					stringField.append(EMPTY_SYMBOL);
				}
				else{
					stringField.append(BODY_SYMBOL);
				}
			}
			stringField.append('\n');
		}
		return stringField.toString();
	}
	
	private boolean isEmptyAround(int code, int unitX, int unitY){
		if(field[unitX + unitY * sizeX] != EMPTY){
			return false;
		}
		if(code == ITEM_CODE){
			return true;
		}
		int lastX = unitX + RADIUS + 1;
		if(lastX >= sizeX){
			lastX -= sizeX;
		}
		int lastY = unitY + RADIUS + 1;
		if(lastY >= sizeY){
			lastY -= sizeY;
		}
		int firstX = unitX - RADIUS;
		if(firstX < 0){
			firstX += sizeX;
		}
		int firstY = unitY - RADIUS;
		if(firstY < 0){
			firstY += sizeY;
		}
		int x = firstX;
		int y = firstY;
		while(x != lastX){
			while(y != lastY){
				if(field[x + y * sizeX] != EMPTY && field[x + y * sizeX] != ITEM_CODE){
					return false;
				}
				++y;
				if(y == sizeY){
					y = 0;
				}
			}
			++x;
			y = firstY;
			if(x == sizeX){
				x = 0;
			}
		}
		return true;
	}
	
	private void removeDeadPlayers(Map<Integer, Player> players){
		for(Integer code : deadPlayers){
			int segmentIndex = 1;
			List<DataSegment> segments = players.get(code.intValue()).getAllSegments();
			for(DataSegment segment : segments){
				if(!segment.isHead()){
					field[segment.getX() + segment.getY() * sizeX] = (segmentIndex == STOMACH) ? ITEM_CODE : EMPTY;
				}
				++segmentIndex;
			}
			players.remove(code);
		}
		deadPlayers.clear();
	}
	
	public void addFood(){
		if(food < MAX_FOOD){
			putNewUnit(ITEM_CODE, null, null);
			++food;
		}
	}
	
	class WellFed{
		public WellFed(int player, DataSegment futureTail){
			this.player = player;
			this.futureTail = futureTail;
		}
		
		public int player;
		public DataSegment futureTail;
	}
	
	class Point{
		public Point(int x, int y){
			this.x = x;
			this.y = y;
		}
		public int x;
		public int y;
	}
	
	private int sizeX;
	private int sizeY;
	private int[] field;
	private int food = 0;
	private int MAX_FOOD = 3;
	private int MAX_TRYING = 10;
	private int ITEM_CODE = -1;
	private int EMPTY = 0;
	private int POINTS_FOR_KILLING = 4;
	private int STOMACH = 2;
	private List<WellFed> wellFedPlayers = new ArrayList<WellFed>();
	private List<Integer> deadPlayers = new ArrayList<Integer>();
	private Map<Point, List<Integer> > conflictingPlayers = new HashMap<Point, List<Integer> >();
	private Timer timer = new Timer();
	private long DELAY = 10000;
	private int RADIUS = 2;
	private char BODY_SYMBOL = '#';
	private char EMPTY_SYMBOL = '.';
	private char ITEM_SYMBOL = '@';
}