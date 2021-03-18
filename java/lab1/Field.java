import java.util.*;

/** Special class that contains text of program and direction.
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Field{
	/**
	 * Reads program and create its text in special form.
	 * @throws RuntimeException If file of program is more than 80x25.
	 * @param scan - object for reading text of program.
	*/
	Field(Scanner scan){
		field = new ArrayList<String>();
		int row = 0;
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

	/**
	 * @return Returns command which field points to.
	*/
	public char getKey(){
		char symb = field.get(positionY).charAt(positionX);
		return symb;
	}

	/**
	 * @return Returns command in the field by coordinates x and y.
	 * @param x - x coordinate.
	 * @param y - y coordinate.
	*/
	public char getKey(int x, int y){
		char symb = field.get((field.size() - 1 - (y % field.size())) % field.size()).charAt(((x % maxLength) + maxLength) % maxLength);
		return symb;
	}
	
	/**
	 * Changes direction to UP.
	*/
	public void changeWayUp(){
		way = Ways.UP;
	}

	/**
	 * Changes directionto DOWN.
	*/
	public void changeWayDown(){
		way = Ways.DOWN;
	}

	/**
	 * Changes direction to LEFT.
	*/
	public void changeWayLeft(){
		way = Ways.LEFT;
	}

	/**
	 * Changes direction to RIGHT.
	*/
	public void changeWayRight(){
		way = Ways.RIGHT;
	}
	
	/**
	 * Changes position in the defined direction.
	*/
	public void changePosition(){
		switch(way){
			case UP:
				positionY = (positionY + field.size() - 1) % field.size();
				break;
			case DOWN:
				positionY = (positionY + field.size() + 1) % field.size();
				break;
			case RIGHT:
				positionX = (positionX + maxLength + 1) % maxLength;
				break;
			case LEFT:
				positionX = (positionX + maxLength - 1) % maxLength;
				break;
		}
	}

	/**
	 * Puts new command in the field by coordinates x and y.
	 * @param x - x coordinate.
	 * @param y - y coordinate.
	*/
	public void changeField(char value, int x, int y){
		int rightX = ((x % maxLength) + maxLength) % maxLength;
		int rightY = (field.size() - 1 - (y % field.size())) % field.size();
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
	
	/**
	 * Constants of directions.
	*/
	private enum Ways {UP, DOWN, RIGHT, LEFT};
	/** Max width of field. */
	private int MAX_WIDTH = 25;
	/** Max height of field. */
	private int MAX_HEIGHT = 80;
	/** Current direction. */
	private Ways way = Ways.RIGHT;
	/** Current x coordinate. */
	private int positionX = 0;
	/** Current y coordinate. */
	private int positionY = 0;
	/** Current length of every string in the field. */
	private int maxLength = 0;
	/** Contains text of program like array of strings. */
	private ArrayList<String> field;
}