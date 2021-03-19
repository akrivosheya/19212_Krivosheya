import java.util.*;
import java.lang.RuntimeException;
import java.util.logging.LogManager;
import java.util.logging.Logger;

/** Special class that is used for interpretation befunge language program.
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Context {
	/** Takes scan for creating of field.
	 * @param scan - object for reading text of program.
	 * @throws RuntimeException
	*/
	public Context(Scanner scan, ContextIO initContIO) {
		try {
			field = new Field(scan);
		} catch (RuntimeException error) {
			log.throwing("Context", "Context", error);
			throw error;
		}
		contIO = initContIO;
		log.info("Initialized contIO");
	}

	/**
	 * @return Returns command which field points to.
	*/
	public char getKey() {
		log.info("return " + field.getKey());
		return field.getKey();
	}
	
	/**
	 * @return Returns number in the top of stack. If stack is empty returns 0.
	*/
	public int get() {
		if(stack.size() == 0) {
			log.info("return " + 0);
			return 0;
		}
		log.info("return " + stack.getLast());
		return stack.getLast();
	}
	
	/**
	 * Deletes number in the top of stack. If stack is empty does nothing.
	*/
	public void pop() {
		if(stack.size() == 0) {
			log.info("Does nothing");
			return;
		}
		log.info("Removes last element");
		stack.removeLast();
	}
	
	/** Puts number in the top of stack.
	 * @param num - number that is putting in the top of stack.
	*/
	public void push(int num) {
		log.info("Pushes " + num);
		stack.addLast(num);
	}

	/**
	 * Changes flag isFinished to true.
	*/
	public void finishJob() {
		log.info("isFinished = true");
		isFinished = true;
	}

	/**
	 * @return Returns value of flag isFinished
	*/
	public boolean jobIsFinished() {
		log.info("return " + isFinished);
		return isFinished;
	}

	/**
	 * @return Returns size of stack
	*/
	public int size() {
		log.info("return " + stack.size());
		return stack.size();
	}

	/**
	 * Changes position in field in the direction defined in the field.
	*/
	public void changePosition() {
		log.info("Changes position");
		field.changePosition();
	}

	/**
	 * Changes direction of field to UP.
	*/
	public void changeWayUp() {
		log.info("way = UP");
		field.changeWayUp();
	}

	/**
	 * Changes direction of field to DOWN.
	*/
	public void changeWayDown() {
		log.info("way = DOWN");
		field.changeWayDown();
	}

	/**
	 * Changes direction of field to LEFT.
	*/
	public void changeWayLeft() {
		log.info("Way = LEFT");
		field.changeWayLeft();
	}

	/**
	 * Changes direction of field to RIGHT.
	*/
	public void changeWayRight() {
		log.info("Way = RIGHT");
		field.changeWayRight();
	}

	/**
	 * @return Returns object with interfaces for reading and writing.
	*/
	public ContextIO getIO() {
		log.info("return contIO");
		return contIO;
	}

	/**
	 * @return Returns command in the field by coordinates x and y.
	 * @param x - x coordinate.
	 * @param y - y coordinate.
	*/
	public char getKey(int x, int y) {
		log.info("return " + field.getKey(x, y) + " from " + x + ":" + y);
		return field.getKey(x, y);
	}

	/**
	 * Puts new command in the field by coordinates x and y.
	 * @param x - x coordinate.
	 * @param y - y coordinate.
	*/
	public void changeField(char value, int x, int y) {
		log.info("Puts " + value + " to " + x + ":" + y);
		field.changeField(value, x, y);
	}
	
	/**
	 * Class that contains text of program and directions.
	*/
	private Field field;
	/**
	 * Stack.
	*/
	private ArrayDeque<Integer> stack = new ArrayDeque<Integer>();
	/**
	 * flag with information of status of execution
	*/
	private boolean isFinished = false;
	/**
	 * Special object. Contains interfaces for reading and writing.
	*/
	private ContextIO contIO;
	static final Logger log = Logger.getLogger(Context.class.getName());
}