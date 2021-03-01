import java.util.Scanner;
import java.util.ArrayList;

public class PlayField{
	PlayField(Scanner scan){
		field = new ArrayList<ArrayList<char> >();
		
	}
	public char getCommand(){
		char symb = field[positionX][positionY];
		changePosition();
	}
	private void changePosition(){
		positionX += changerX[way];
		positionY += changerY[way];
	}
	

	private static int MAX_WEIGHT = 25;
	private static int MAX_HEIGHT = 80;
	private ArrayList<ArrayList<char> > field;
}
