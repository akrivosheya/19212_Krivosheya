import java.util.ArrayList;
import java.util.List;
import java.util.*;
import java.io.*;

/** Class that controls process of game
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Model {
	/** 
	 * Constructs Model.
	*/
	public Model(){}
	
	/**
	 * Creates level from file with configurations of level.
	 * @param file - name of file that contains information about rectangles.
	*/
	public void loadLevel(String file){
		currentLevelFile = file;
		platforms = new ArrayList<Platform>();
		boolean field[] = new boolean[MAX_COORDINATE * MAX_COORDINATE];
		boolean hasMouse = false;
		try(Scanner scan = new Scanner(new File(file))){
			if(!(scan.hasNext() && ("Level").compareTo(scan.next()) == 0 && scan.hasNext())){
				platforms = null;
				return;
			}
			level = scan.next();
			String platform;
			while(scan.hasNext()){
				platform = scan.next();
				switch(platform.charAt(0)){
					case MOUSE:
						if(platform.length() != MOUSE_LENGTH ||
							Character.digit(platform.charAt(1), Character.MAX_RADIX) >= MAX_COORDINATE - 1 ||
							hasMouse){
							platforms = null;
							return;
						}
						int position = Character.digit(platform.charAt(1), Character.MAX_RADIX);
						for(int i = 0; i < MOUSE_LENGTH_IN_FIELD; ++i){
							if(field[MOUSE_Y_IN_FIELD * MAX_COORDINATE + position + i]){
								platforms = null;
								return;
							}
							field[MOUSE_Y_IN_FIELD * MAX_COORDINATE + position + i] = true;
						}
						hasMouse = true;
						platforms.add(new Platform(position, MOUSE_Y_COORDINATE_MODEL,
							position + MOUSE_WIDTH, MOUSE_Y_COORDINATE_MODEL - MOUSE_HEIGHT,
								Platform.Type.HORIZONTAL, true));
						break;
					case VERTICAL:
						if(badParam(platform)){
							platforms = null;
							return;
						}
						int positionX = Character.digit(platform.charAt(1), Character.MAX_RADIX);
						int positionY = Character.digit(platform.charAt(2), Character.MAX_RADIX);
						int height = Character.digit(platform.charAt(3), Character.MAX_RADIX);
						for(int i = MAX_COORDINATE - 1 - positionY; i < height + MAX_COORDINATE - 1 - positionY; ++i){
							if(field[i * MAX_COORDINATE + positionX]
								|| positionY < height - 1){
								platforms = null;
								return;
							}
							field[i * MAX_COORDINATE + positionX] = true;
						}
						platforms.add(new Platform(positionX, positionY + 1, positionX + 1, positionY + 1 - height,
								Platform.Type.VERTICAL, false));
						break;
					case HORIZONTAL:
						if(badParam(platform)){
							platforms = null;
							return;
						}
						positionX = Character.digit(platform.charAt(1), Character.MAX_RADIX);
						positionY = Character.digit(platform.charAt(2), Character.MAX_RADIX);
						int width = Character.digit(platform.charAt(3), Character.MAX_RADIX);
						for(int i = positionX; i < width + positionX; ++i){
							if(field[(MAX_COORDINATE - 1 - positionY) * MAX_COORDINATE + i] ||
								positionX > MAX_COORDINATE - width){
								platforms = null;
								return;
							}
							field[(MAX_COORDINATE - 1 - positionY) * MAX_COORDINATE + i] = true;
						}
						platforms.add(new Platform(positionX, positionY + 1, positionX + width, positionY,
							Platform.Type.HORIZONTAL, false));
						break;
				}
			}
		} catch (IOException error){
			platforms = null;
			return;
		}
		if(!hasMouse){
			platforms = null;
			return;
		}
		this.field = new Field(0, 6, 6, 0, platforms);
		time = 0;
		steps = 0;
		isFinished = false;
		isCompleted = checkCompleted();
		bestTime = (isCompleted) ? getBestInt() : 0;
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
			Character.digit(platform.charAt(3), Character.MAX_RADIX) > MAX_COORDINATE;
	}

	/**
	 * Checkes if moving is possible.
	 * @param index - index of current platform.
	 * @param coordX - moving in x coordinate.
	 * @param coordY - moving in y coordinate.
	 * @return true if moving is possible and false else.
	*/
	public boolean checkMove(int index, int coordX, int coordY){
		for(Platform platform : platforms){
			if(platforms.get(index) == platform){
				continue;
			}
			if(!field.checkMove(index, coordX, coordY, platforms)){
				return false;
			}
		}
		return true;
	}

	/**
	 * Changes position of current platform.
	 * @param index - index of current platform.
	 * @param coordX - moving in x coordinate.
	 * @param coordY - moving in y coordinate.
	 * @return Returns CANT_MOVE if it is impossible to move platform,
	 * MOVE_HORIZONTAL if moving is possible and platform is horizontal
	 * MOVE_VERTICAL if moving is possible and platform is vertical.
	*/
	public int move(int index, int coordX, int coordY){
		if(!checkMove(index, coordX, coordY)){
			return CANT_MOVE;
		}
		int type;
		if(platforms.get(index).getType() == Platform.Type.HORIZONTAL){
			coordY = 0;
			type = MOVE_HORIZONTAL;
		}else{
			coordX = 0;
			type = MOVE_VERTICAL;
		}
		platforms.get(index).move(coordX, coordY);
		isFinished = field.isFinish(platforms.get(index));
        return type;
	}
	
	/**
	 * @return Returns list of names of levels.
	*/
	public List<String> getLevelsNames(){
		List<String> names = new ArrayList<String>();
		String name = "level";
		for(int i = 1; i <= LEVELS; ++i){
			names.add(name + i);
		}
		return names;
	}

	/**
	 * @return Returns list of platforms in current level.
	*/
	public List<Platform> getPlatforms(){
		return platforms;
	}

	/**
	 * Checkes if current level is finished.
	 * @return Returns true if level is finished and false else.
	*/
	public boolean isFinished(){
		return isFinished;
	}

	/**
	 * @return Returns number of current level.
	*/
	public String getLevel(){
		return level;
	}

	/**
	 * Increases count of steps.
	*/
	public void increaseSteps(){
		++steps;
	}

	/**
	 * @return Returns current count of steps.
	*/
	public int getSteps(){
		return steps;
	}
	
	/**
	 * Increases time.
	*/
	public void increaseTime(){
		++time;
	}

	/**
	 * @return Returns text of time of current level.
	*/
	public String getTime(){
		StringBuilder timeValue = new StringBuilder();
		if(time / SECONDS < 10){
			timeValue.append("0");
		}
		timeValue.append(String.valueOf(time / SECONDS));
		timeValue.append(":");
		if(time % SECONDS < 10){
			timeValue.append("0");
		}
		timeValue.append(String.valueOf(time % SECONDS));
		return timeValue.toString();
	}
	
	/**
	 * @param mode - flag that chooses requiring information.
	 * @return Returns list of strings of information in model.
	*/
	public List<String> getInfoText(Controller.Mode mode){
		List<String> text = new ArrayList<String>();
		switch(mode){
			case ABOUT:
				try(Scanner scan = new Scanner(new File(aboutFile))){
					while(scan.hasNextLine()){
						text.add(scan.nextLine());
					}
				}
				catch(IOException error){
					text.clear();
					text.add(errorText);
				}
				break;
			case HELP:
				try(Scanner scan = new Scanner(new File(helpFile))){
					while(scan.hasNextLine()){
						text.add(scan.nextLine());
					}
				}
				catch(IOException error){
					text.clear();
					text.add(errorText);
				}
				break;
			case TAB:
				try(Scanner scan = new Scanner(new File(tabFile))){
					int i = 1;
					while(scan.hasNext()){
						scan.next();
						text.add(i + " - " + scan.next());
						text.add(scan.next());
						++i;
					}
				}
				catch(IOException error){
					text.clear();
					text.add(errorText);
				}
				break;
		}
		return text;
	}
	
	/**
	 * Transforms text to decimal value.
	 * @param text - text of decimal.
	 * @return Returns decimal value of text.
	*/
	private int toInt(String text){
		int numb = 0;
		for(int i = 0; i < text.length(); ++i){
			numb = numb * 10 + Character.digit(text.charAt(i), Character.MAX_RADIX);
		}
		return numb;
	}
	
	/**
	 * @return Returns best time or "--:--" if level is uncompleted.
	*/
	public String getBest(){
		int intLevel = toInt(level);
		try(Scanner scan = new Scanner(new File(tabFile))){
			for(int i = 1; i < intLevel; ++i){
				scan.next();
				scan.next();
				scan.next();
			}
			scan.next();
			scan.next();
			return scan.next();
		}
		catch(IOException error){
			return "-";
		}
	}
	
	/**
	 * @return Returns information about levels.
	*/
	public List<String> getLevelsInfo(){
		List<String> info = new ArrayList<String>();
		try(Scanner scan = new Scanner(new File(tabFile))){
			for(int i = 1; i <= LEVELS; ++i){
				info.add("Level " + i);
				if(toInt(scan.next()) == 0){
					info.add("Uncompleted");
					scan.next();
					scan.next();
				}
				else{
					info.add(scan.next() + " - " + scan.next());
				}
			}
			info.add("");
		}
		catch(IOException error){}
		return info;
	}
	
	/**
	 * Transforms text of time to count of seconds.
	 * @param time - text of time.
	 * @return Returns seconds of time.
	*/
	private int timeToInt(String time){
		boolean noMoreMinutes = false;
		int minutes = 0;
		int seconds = 0;
		for(char c : time.toCharArray()){
			if(c == ':'){
				noMoreMinutes = true;
			}
			else{
				if(noMoreMinutes){
					seconds = seconds * 10 + Character.digit(c, Character.MAX_RADIX);
				}
				else{
					minutes = minutes * 10 + Character.digit(c, Character.MAX_RADIX) * 60;
				}
			}
		}
		return minutes + seconds;
	}
	
	/**
	 * Resets score tabl.
	*/
	public void reset(){
		try(FileWriter writer = new FileWriter(tabFile)){
			for(int i = 0; i < LEVELS; ++i){
				writer.write(DEFAULT_COMPLETED);
				writer.write(DEFAULT_PLAYER);
				writer.write(DEFAULT_TIME);
			}
		}
		catch(IOException error){
			return;
		}
	}
	
	/**
	 * Checkes if level is already completed.
	 * @return Returns true if level is completed and false else.
	*/
	private boolean checkCompleted(){
		int intLevel = toInt(level);
		try(Scanner scan = new Scanner(new File(tabFile))){
			for(int i = 1; i < intLevel; ++i){
				scan.nextLine();
			}
			return (toInt(scan.next()) == 0) ? false : true;
		}
		catch(IOException error){
			return false;
		}
	}
	
	/**
	 * @return Returns best time of current level in seconds.
	*/
	private int getBestInt(){
		int intLevel = toInt(level);
		try(Scanner scan = new Scanner(new File(tabFile))){
			for(int i = 1; i < intLevel; ++i){
				scan.nextLine();
			}
			scan.next();
			scan.next();
			return timeToInt(scan.next());
		}
		catch(IOException error){
			return 0;
		}
	}
	
	/**
	 * Checkes if player gets new record in level.
	 * @return Returns true if player gets new record and false else.
	*/
	public boolean isRecord(){
		return !isCompleted || time < bestTime;
	}
	
	/**
	 * Saves new best time of level.
	 * @param name - name of player who  gets new record.
	*/
	public void saveResult(String name){
		int intLevel = toInt(level);
		StringBuilder forWriting = new StringBuilder("");
		try(Scanner scan = new Scanner(new File(tabFile))){
			for(int i = 1; i < LEVELS + 2; ++i){
				if(i == intLevel){
					forWriting.append(1 + " " + name + getTime());
					scan.next();
					scan.next();
					scan.next();
					continue;
				}
				forWriting.append(scan.nextLine() + "\n");
			}
		}
		catch(IOException error){
			return;
		}
		try(FileWriter writer = new FileWriter(tabFile)){
			writer.write(forWriting.toString());
		}
		catch(IOException error){
			return;
		}
	}
	
	/**.
	 * @return Returns file name of current level.
	*/
	public String getCurrentLevel(){
		return currentLevelFile;
	}

	/**.
	 * Field that contains all platforms of current level.
	*/
	private Field field;
	/**.
	 * List of platforms of current level.
	*/
	private List<Platform> platforms;
	/**.
	 * Count of available levels.
	*/
	private int LEVELS = 10;
	/**
	 * Signal that current dragged platform can't move.
	*/
	private int CANT_MOVE = 1;
	/**
	 * Signal that current dragged platform is horizontal.
	*/
	private int MOVE_HORIZONTAL = 2;
	/**
	 * Signal that current dragged platform is vertical.
	*/
	private int MOVE_VERTICAL = 3;
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
	 * Identifier of level.
	*/	
	private String level;
	/**
	 * Length of Mouse's param.
	*/	
	private int MOUSE_LENGTH = 2;
	/**
	 * Max count of blocks of field.
	*/	
	private int MAX_COORDINATE = 6;
	/**
	 * Length of Mouse's in field.
	*/	
	private int MOUSE_LENGTH_IN_FIELD = 2;
	/**
	 * Length of Barrier's param.
	*/	
	private int BARRIER_LENGTH = 4;
	/**
	 * Mouse's y position in field.
	*/	
	private int MOUSE_Y_IN_FIELD = 2;
	/**
	 * Y coordinate of left top corner of Mouse in Model.
	*/	
	private int MOUSE_Y_COORDINATE_MODEL = 4;
	/**
	 * Height of Mouse.
	*/
	private int MOUSE_HEIGHT = 1;
	/**
	 * Width of Mouse.
	*/	
	private int MOUSE_WIDTH = 2;
	/**
	 * Best time when level is uncompleted.
	*/	
	private String DEFAULT_TIME = "--:--\n";
	/**
	 * Name of best player when level is uncompleted.
	*/	
	private String DEFAULT_PLAYER = "_____ ";
	/**
	 * Bit of uncompleted level.
	*/	
	private String DEFAULT_COMPLETED = "0 ";
	/**
	 * Seconds in one minute.
	*/	
	private int SECONDS = 60;
	/**
	 * Flag of finishing level.
	*/	
	private boolean isFinished = false;
	/**
	 * Made steps in current level.
	*/	
	private int steps = 0;
	/**
	 * Current time in current level in seconds.
	*/	
	private int time = 0;
	/**
	 * Best time of current level in seconds.
	*/	
	private int bestTime = 0;
	/**
	 * Flag of completing current level.
	*/	
	private boolean isCompleted = false;
	/**
	 * File with information about game.
	*/	
	private String aboutFile = "about.txt";
	/**
	 * File with help information.
	*/	
	private String helpFile = "help.txt";
	/**
	 * File with scores tab.
	*/	
	private String tabFile = "tab.txt";
	/**
	 * Error text when information can't be showed.
	*/	
	private String errorText = "Can't show information";
	/**
	 * File with configuration of current level.
	*/	
	private String currentLevelFile = null;
}
