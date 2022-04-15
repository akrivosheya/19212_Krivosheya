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
		List<Platform> platforms;
		List<Rectangle> rectangles = null;
		model.loadLevel(file);
		platforms = model.getPlatforms();
		if(platforms != null){
			rectangles = new ArrayList<>();
			Color color;
			for(Platform platform : platforms){
				color = (platform.isMouse()) ? Color.GOLD : Color.AZURE;
				rectangles.add(createRectangle(platform.getHeight() * SIZE_OF_BLOCK, 
						platform.getWidth() * SIZE_OF_BLOCK, 
						platform.getLeftTopX() * SIZE_OF_BLOCK, 
						(double)(MAX_COORDINATE - platform.getLeftTopY()) * SIZE_OF_BLOCK,
						color));
			}
		}
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

	/**
	 * Transforms view coordinatess to model coordinates.
	 * @param viewCoord - view coordinate.
	 * @return Returns model coordinate.
	*/
	private int getModelCoord(double viewCoord){
		int modelCoord = 0;
		while(!(modelCoord * SIZE_OF_BLOCK - viewCoord <= SIZE_OF_BLOCK / 2 &&
				viewCoord - modelCoord * SIZE_OF_BLOCK <= SIZE_OF_BLOCK / 2) 
				&& modelCoord <= MAX_COORDINATE){
			++modelCoord;
		}
		return modelCoord;
	}

	/**
	 * Transforms view coordinates to fixed view coordintes.
	 * @param viewCoord - view coordinate.
	 * @return Returns fixed view coordinate.
	*/
	public double getViewCoord(double viewCoord){
		return getModelCoord(viewCoord) * SIZE_OF_BLOCK;
	}

	/**
	 * Takes index of platform in list of platforms of current level with given coordinates.
	 * @param platforms - list of platforms of current level.
	 * @param oldX - x coordinate of current platform in View.
	 * @param oldY - y coordinate of current platform in View.
	 * @return Returns index of current platform.
	*/
	private int getIndex(List<Platform> platforms, int oldX, int oldY){
		int index;
		for(index = 0; index < platforms.size(); ++index){
			if(platforms.get(index).getLeftTopX() == oldX &&  
				platforms.get(index).getLeftTopY() == oldY){
				break;
			}
		}
		return index;
	}

	/**
	 * Moves platform in model, if moving is possible, and doesn't do it else.
	 * @param oldX - x coordinate of current platform in View.
	 * @param oldY - y coordinate of current platform in View.
	 * @param newX - new x coordinate of current platform in View.
	 * @param newY - new y coordinate of current platform in View.
	 * @return Returns CANT_MOVE if it is impossible to move platform,
	 * MOVE_HORIZONTAL if moving is possible and platform is horizontal
	 * MOVE_VERTICAL if moving is possible and platform is vertical.
	*/
	public int move(double oldX, double oldY, double newX, double newY){
		int oldModelX = getModelCoord(oldX);
		int oldModelY = MAX_COORDINATE - getModelCoord(oldY);
		int newModelX = getModelCoord(newX);
		int newModelY = MAX_COORDINATE - getModelCoord(newY);
		List<Platform> platforms = model.getPlatforms();
		int index = getIndex(platforms, oldModelX, oldModelY);
		if(index > platforms.size()){
			return CANT_MOVE;
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
	
	/**
	 * @return Returns list of names of levels in model.
	*/
	public List<String> getLevelsNames(){
		return model.getLevelsNames();
	}

	/**
	 * Checkes if level in model is finished.
	 * @return Returns true if level is finished and false else.
	*/
	public boolean isFinished(){
		return model.isFinished();
	}

	/**
	 * @return Returns number of current level in model.
	*/
	public String getLevel(){
		return model.getLevel();
	}
	
	/**
	 * @return Returns text about levels.
	*/
	public List<String> getLevelsInfo(){
		return model.getLevelsInfo();
	}

	/**
	 * Increases count of steps in model.
	*/
	public void increaseSteps(){
		model.increaseSteps();
	}

	/**
	 * @return Returns current count of steps in model.
	*/
	public int getSteps(){
		return model.getSteps();
	}
	
	/**
	 * Increases time in model.
	*/
	public void increaseTime(){
		model.increaseTime();
	}

	/**
	 * @return Returns text of time of current level in model.
	*/
	public String getTime(){
		return model.getTime();
	}
	
	/**
	 * @param mode - flag that chooses requiring information.
	 * @return Returns list of strings of information in model.
	*/
	public List<String> getInfoText(Mode mode){
		return model.getInfoText(mode);
	}
	
	/**
	 * @return Returns best time in model or "--:--" if level is uncompleted.
	*/
	public String getBest(){
		return model.getBest();
	}
	
	/**
	 * Resets score tab in model.
	*/
	public void reset(){
		model.reset();
	}
	
	/**
	 * Checkes if player gets new record in level of model.
	 * @return Returns true if player gets new record and false else.
	*/
	public boolean isRecord(){
		return model.isRecord();
	}
	
	/**
	 * Saves new best time of level in model.
	 * @param name - name of player who  gets new record.
	*/
	public void saveResult(String name){
		StringBuilder rightName = new StringBuilder(name.replace(' ', '_'));
		if(rightName.length() > MAX_NAME_LENGTH){
			rightName.delete(MAX_NAME_LENGTH, rightName.length());
		}
		if(rightName.length() < 1){
			rightName.append("NO_NAME");
		}
		rightName.append(" ");
		model.saveResult(rightName.toString());
	}
	
	/**.
	 * @return Returns file name of current level.
	*/
	public String getCurrentLevel(){
		return model.getCurrentLevel();
	}

	/**
	 * Size of 1 block.
	*/
	private double SIZE_OF_BLOCK = 100;
	/**
	 * Max count of blocks of field.
	*/	
	private int MAX_COORDINATE = 6;
	/**
	 * Length of Barrier's param.
	*/	
	private int BARRIER_LENGTH = 4;
	/**
	 * Model of game.
	*/
	private Model model = new Model();
	/**
	 * Flag of impossible moving.
	*/
	private int CANT_MOVE = 1;	
	/**
	 * Max length of player name.
	*/
	private int MAX_NAME_LENGTH = 10;
	/**
	 * All possible modes of information: TAB - tab of scores, ABOUT - information about game,
	 * HELP - help information.
	*/
	public enum Mode{TAB, ABOUT, HELP};
}