package snakes;

import java.util.*;
import java.util.concurrent.*;

public class Snakes{
	public Snakes(int sizeX, int sizeY){
		if(sizeX < MIN_SIZE_X || sizeY < MIN_SIZE_Y || sizeX > MAX_SIZE_X || sizeX > MAX_SIZE_Y){
			throw new RuntimeException("Bad sizes: " + "x = " + sizeX + ";y = " + sizeY);
		}
		field = new Field(sizeX, sizeY);
	}
	
	public Snakes(int sizeX, int sizeY, List<Unit> units){
		if(sizeX < MIN_SIZE_X || sizeY < MIN_SIZE_Y || sizeX > MAX_SIZE_X || sizeX > MAX_SIZE_Y){
			throw new RuntimeException("Bad sizes: " + "x = " + sizeX + ";y = " + sizeY);
		}
		field = new Field(sizeX, sizeY);
		if(units == null){
			return;
		}
		for(Unit unit : units){
			if(!field.isItemCode(unit.getCode())){
				Player player = new Player(unit.getCode(), unit.getPoints(), 
					unit.getSegments(), unit.getDirection());
				players.put(unit.getCode(), player);
			}
			if(!field.put(unit)){
				field.clear();
				players.clear();
				break;
			}
		}
	}
	
	public boolean canStart(){
		if(players.size() == 0){
			return false;
		}
		return true;
	}
	
	public void changeDirection(int playerCode, Player.Direction direction){
		if(players.containsKey(playerCode)){
			Player player = players.get(playerCode);
			player.changeDirection(direction);
		}
		else{
			System.err.println("Player " + playerCode + " does not exist");
		}
	}
	
	public boolean putNewPlayer(int code){
		int[] x = new int[1];
		int[] y = new int[1];
		if(field.putNewUnit(code, x, y)){
			Player newPlayer = new Player(x[0], y[0], code);
			players.put(code, newPlayer);
			return true;
		}
		return false;
	}
	
	public String getScene(){
		return field.getField();
	}
	
	public void reset(List<Unit> units){
		field.clear();
		if(units == null){
			return;
		}
		for(Unit unit : units){
			if(!field.isItemCode(unit.getCode())){
				Player player = new Player(unit.getCode(), unit.getPoints(), 
					unit.getSegments(), unit.getDirection());
				players.put(unit.getCode(), player);
			}
			if(!field.put(unit)){
				field.clear();
				players.clear();
				break;
			}
		}
	}
	
	public void update(){
		field.movePlayers(players);
		field.collectGarbage(players);
		field.increasePlayers(players);
		field.addFood();
	}
	
	public List<Unit> getUnits(){
		List<Unit> units = field.getItems();
		players.forEach((Integer code, Player player) -> {
			units.add(new Unit(code.intValue(), player.getPoints(), player.getAllSegments(), player.getDirection()));
		});
		return units;
	}
	
	private Field field = null;
	private Map<Integer, Player> players = new ConcurrentHashMap<Integer, Player>();
	private int MIN_SIZE_X = 5;
	private int MIN_SIZE_Y = 5;
	private int MAX_SIZE_X = 20;
	private int MAX_SIZE_Y = 20;
}