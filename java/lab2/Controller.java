import javafx.scene.shape.Rectangle;
import java.util.*;
import java.io.*;
import javafx.scene.paint.Color;
import javafx.scene.shape.StrokeType;
import java.lang.Math;

/** Class that connects View and Model.
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Controller{
	/** 
	 * Constructs Controller.
	*/
	public Controller(){}

	/**
	 * Reads file and creates by it List of Rectangles.
	 * Gives that List to View and special information about them to Model.
	 * @param file - name of file that contains information about rectangles.
	 * @return Returns List of Rectangles. If unsuccessfully, returns null.
	*/
	public List<Rectangle> getRectangles(String file){
			List<Rectangle> rectangles = new ArrayList<Rectangle>();
			List<Platform> platforms = new ArrayList<Platform>();
			boolean field[] = new boolean[MAX_COORDINATE * MAX_COORDINATE];
		try(Scanner scan = new Scanner(new File(file))){
			if(!(scan.hasNext() && ("Level").compareTo(scan.next()) == 0 && scan.hasNext())){
				return null;
			}
			level = scan.next();
			String platform;
			while(scan.hasNext()){
				platform = scan.next();
				switch(platform.charAt(0)){//проверить на другие конфликты
					case MOUSE:
						if(platform.length() != MOUSE_LENGTH ||
							Character.digit(platform.charAt(1), Character.MAX_RADIX) >= MAX_COORDINATE - 1 ||
							hasMouse){
							return null;
						}
						int position = Character.digit(platform.charAt(1), Character.MAX_RADIX);
						for(int i = 0; i < MOUSE_LENGTH_IN_FIELD; ++i){
							if(field[MOUSE_Y_IN_FIELD * MAX_COORDINATE + position + i]){
								return null;
							}
							field[MOUSE_Y_IN_FIELD * MAX_COORDINATE + position + i] = false;
						}
						hasMouse = true;
						platforms.add(new Mouse(position, MOUSE_Y_COORDINATE_MODEL,
							position + MOUSE_WIDTH, MOUSE_Y_COORDINATE_MODEL - MOUSE_HEIGHT));
						rectangles.add(createRectangle(MOUSE_HEIGHT * SIZE_OF_BLOCK, MOUSE_WIDTH * SIZE_OF_BLOCK, 
								(double)position * SIZE_OF_BLOCK, MOUSE_Y_COORDINATE_VIEW, Color.GOLD));
						break;
					case VERTICAL:
						if(badParam(platform)){
							return null;
						}
						int positionX = Character.digit(platform.charAt(1), Character.MAX_RADIX);
						int positionY = Character.digit(platform.charAt(2), Character.MAX_RADIX);
						int height = Character.digit(platform.charAt(3), Character.MAX_RADIX);
						for(int i = MAX_COORDINATE - 1 - positionY; i < height + MAX_COORDINATE - 1 - positionY; ++i){
							if(field[i * MAX_COORDINATE + positionX]
								|| positionY < height - 1){
								return null;
							}
							field[i * MAX_COORDINATE + positionX] = false;
						}
						platforms.add(new Barrier(positionX, positionY + 1, positionX + 1, positionY + 1 - height,
								Platform.Type.VERTICAL));
						rectangles.add(createRectangle(height * SIZE_OF_BLOCK, SIZE_OF_BLOCK, positionX * SIZE_OF_BLOCK,
								(double)(MAX_COORDINATE - 1 - positionY) * SIZE_OF_BLOCK, Color.AZURE));
						break;
					case HORIZONTAL:
						if(badParam(platform)){
							return null;
						}
						positionX = Character.digit(platform.charAt(1), Character.MAX_RADIX);
						positionY = Character.digit(platform.charAt(2), Character.MAX_RADIX);
						int width = Character.digit(platform.charAt(3), Character.MAX_RADIX);
						for(int i = positionX; i < width + positionX; ++i){
							if(field[(MAX_COORDINATE - 1 - positionY) * MAX_COORDINATE + i] ||
								positionX > MAX_COORDINATE - width){
								return null;
							}
							field[i * MAX_COORDINATE + positionX] = true;
						}
						platforms.add(new Barrier(positionX, positionY + 1, positionX + width, positionY,
							Platform.Type.HORIZONTAL));
						rectangles.add(createRectangle(SIZE_OF_BLOCK, width * SIZE_OF_BLOCK, (double)positionX * SIZE_OF_BLOCK,
								(double)(MAX_COORDINATE - 1 - positionY) * SIZE_OF_BLOCK, Color.AZURE));
						break;
				}
			}
		} catch (IOException error){
			return null;
		}
		if(!hasMouse){
			return null;
		}
		model = new Model(platforms);
		return rectangles;
	}

	/**
	 * Creates Rectangle.
	 * @param height - height of rectangles.
	 * @param width - width of rectangles.
	 * @param coordX - X coordinate of left top corner of rectangles.
	 * @param coordY - Y coordinate of rleft top corner of rectangles.
	 * @param inside - color of rectangles.
	 * @return Returns rectangle.
	*/
	private Rectangle createRectangle(double height, double width, double coordX, double coordY, 
				Color inside){
		Rectangle rectangle = new Rectangle(width, height, inside);
		rectangle.setStrokeType(StrokeType.INSIDE);
		rectangle.setStroke(Color.BLACK);
		rectangle.setStrokeWidth(2);
		rectangle.setX(coordX);
		rectangle.setY(coordY);
		return rectangle;
	}
	
	/**
	 * Checks params of platform.
	 * @param platform - params of platform.
	 * @return Returns true if it is good params. Else - false
	*/
	private boolean badParam(String platform){
		return platform.length() != BARRIER_LENGTH ||
			Character.digit(platform.charAt(1), Character.MAX_RADIX) > MAX_COORDINATE - 1 ||
			Character.digit(platform.charAt(2), Character.MAX_RADIX) > MAX_COORDINATE - 1 ||
			Character.digit(platform.charAt(3), Character.MAX_RADIX) > MAX_COORDINATE - 1;
	}

	private int getModelCoord(double viewCoord){
		int modelCoord = 0;
		while(!(modelCoord * SIZE_OF_BLOCK - viewCoord <= SIZE_OF_BLOCK / 2 && viewCoord - modelCoord * SIZE_OF_BLOCK <= SIZE_OF_BLOCK / 2) 
				&& modelCoord <= MAX_COORDINATE){
			++modelCoord;
		}
		return modelCoord;
	}

	public double getViewCoord(double viewCoord){
		return getModelCoord(viewCoord) * SIZE_OF_BLOCK;
	}

	private int getIndex(List<Platform> platforms, int oldX, int oldY){
		int index;
		for(index = 0; index < platforms.size(); ++index){
			//System.out.println(index + " " + oldX + " " + (SIZE_OF_FIELD - oldY) + " " + platforms.get(index).getLeftTopX() + " " + platforms.get(index).getLeftTopY());
			if(platforms.get(index).getLeftTopX() == oldX &&  
				platforms.get(index).getLeftTopY() == oldY){
				break;
			}
		}
		return index;
	}

	public int move(double oldX, double oldY, double newX, double newY){
		int oldModelX = getModelCoord(oldX);
		int oldModelY = MAX_COORDINATE - getModelCoord(oldY);
		int newModelX = getModelCoord(newX);
		int newModelY = MAX_COORDINATE - getModelCoord(newY);
		List<Platform> platforms = model.getPlatforms();
		int index = getIndex(platforms, oldModelX, oldModelY);
		if(index > platforms.size()){
			return IS_FINISH;
		}
		boolean canMove = true;
		if(platforms.get(index).getType() == Platform.Type.VERTICAL && oldModelY == newModelY && 
					Math.abs(oldY - SIZE_OF_BLOCK * (MAX_COORDINATE - oldModelY)) < Math.abs(oldY - newY)){
			if(oldY < newY){
				canMove = model.checkMove(index, 0, -1);
			} else {
				canMove = model.checkMove(index, 0, 1);
			}
		}
		if(platforms.get(index).getType() == Platform.Type.HORIZONTAL && oldModelX == newModelX 
					&& Math.abs(oldX - SIZE_OF_BLOCK * oldModelX) < Math.abs(oldX - newX)){
			if(oldX < newX){
				canMove = model.checkMove(index, 1, 0);
			} else {
				canMove = model.checkMove(index, -1, 0);
			}
		}
		if(!canMove){
			return CANT_MOVE;
		}
		return model.move(index, newModelX - oldModelX, newModelY - oldModelY);
	}

	private double SIZE_OF_FIELD = 600;
	/**
	 * Size of 1 block.
	*/
	private double SIZE_OF_BLOCK = 100;
	/**
	 * Height of Mouse.
	*/
	private int MOUSE_HEIGHT = 1;
	/**
	 * Width of Mouse.
	*/	
	private int MOUSE_WIDTH = 2;
	/**
	 * Y coordinate of left top corner of Mouse in Model.
	*/	
	private int MOUSE_Y_COORDINATE_MODEL = 4;
	/**
	 * Y coordinate of left top corner of Mouse in View.
	*/	
	private double MOUSE_Y_COORDINATE_VIEW = 200;
	/**
	 * Mouse's y position in field.
	*/	
	private int MOUSE_Y_IN_FIELD = 1;
	/**
	 * Length of Mouse's in field.
	*/	
	private int MOUSE_LENGTH_IN_FIELD = 2;
	/**
	 * Length of Mouse's param.
	*/	
	private int MOUSE_LENGTH = 2;
	/**
	 * Length of Barrier's param.
	*/	
	private int BARRIER_LENGTH = 4;
	/**
	 * Max count of blocks of field.
	*/	
	private int MAX_COORDINATE = 6;
	/**
	 * Character of Mouse.
	*/	
	private final char MOUSE = 'm';
	/**
	 * Character of vertical Barrier.
	*/	
	private final char VERTICAL = 'v';
	/**
	 * Character of horizontal Barrier.
	*/	
	private final char HORIZONTAL = 'h';
	/**
	 * Flag of having Mouse in Model.
	*/	
	private boolean hasMouse = false;
	/**
	 * Identifier of level.
	*/	
	private String level;
	/**
	 * Model of game.
	*/
	private Model model = null;
	private double MIN = 2;
	private int CAN_MOVE = 0;
	private int CANT_MOVE = 1;
	private int IS_FINISH = 2;	
}