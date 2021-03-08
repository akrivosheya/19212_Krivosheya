import java.util.*;

public class Field{
	Field(Scanner scan){
		field = new ArrayList<String>();
		int row = 0, maxLength = 0;
		while(row < MAX_HEIGHT && scan.hasNextLine()){
			String line = null;
			line = scan.nextLine();
			if(line.length() >= MAX_WIDTH){
				throw new RuntimeException("File has more then " + MAX_WIDTH);
			}
			if(maxLength < line.length()){
				maxLength = line.length();
			}
			field.add(line);
			++row;
		}
		if(row >= MAX_HEIGHT && scan.hasNextLine()){
			throw new RuntimeException("File has more then " + MAX_HEIGHT);
		}
		for(int i = 0; i < field.size(); ++i){
			String line = field.get(i);
			int freeSpace = maxLength - line.length();
			for(int j = 0; j < freeSpace; ++j){
				line += " ";
			}
			field.set(i, line);
		}
	}

	public char getKey(){
		char symb = field.get(positionY).charAt(positionX);
		return symb;
	}

	public char getKey(int x, int y){
		char symb = field.get((y + MAX_HEIGHT) % MAX_HEIGHT).charAt((x + MAX_WIDTH) % MAX_WIDTH);
		return symb;
	}
	
	public void changeWayUp(){
		way = Ways.UP;
	}

	public void changeWayDown(){
		way = Ways.DOWN;
	}

	public void changeWayLeft(){
		way = Ways.LEFT;
	}

	public void changeWayRight(){
		way = Ways.RIGHT;
	}
	
	public void changePosition(){
		switch(way){
			case UP:
				positionY = (positionY + MAX_HEIGHT + 1) % MAX_HEIGHT;
				break;
			case DOWN:
				positionY = (positionY + MAX_HEIGHT - 1) % MAX_HEIGHT;
				break;
			case RIGHT:
				positionY = (positionX + MAX_WIDTH + 1) % MAX_WIDTH;
				break;
			case LEFT:
				positionY = (positionX + MAX_WIDTH - 1) % MAX_WIDTH;
				break;
		}
	}

	public void changeField(char value, int x, int y){
		int rightX = (x + MAX_WIDTH) % MAX_WIDTH;
		int rightY = (y + MAX_HEIGHT) % MAX_HEIGHT;
		String line = field.get(rightY);
		String newLine = "";
		for(int i = 0; i < rightX; ++i){
			newLine += line.charAt(i);
		}
		newLine += value;
		for(int i = rightX + 1; i < line.length(); ++i){
			newLine += line.charAt(i);
		}
		field.set(rightY, newLine);
	}
	
	private enum Ways {UP, DOWN, RIGHT, LEFT};
	private int MAX_WIDTH = 25;
	private int MAX_HEIGHT = 80;
	private Ways way = Ways.RIGHT;
	private int positionX = 0;
	private int positionY = 0;
	private ArrayList<String> field;
}
