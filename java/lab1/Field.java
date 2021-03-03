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
		char symb = field.get(positionX).charAt(positionY);
		return symb;
	}
	
	public void changeWay(Ways newWay){
		way = newWay;
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
	
	public enum Ways {UP, DOWN, RIGHT, LEFT};
	private int MAX_WIDTH = 25;
	private int MAX_HEIGHT = 80;
	private Ways way = Ways.RIGHT;
	private int positionX = 0;
	private int positionY = 0;
	private ArrayList<String> field;
}
