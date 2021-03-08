import java.util.*;
import java.lang.RuntimeException;
import java.io.*;

public class Context{
	Context(Scanner scan){
		try {
			field = new Field(scan);
		} catch (RuntimeException error){
			throw error;
		}
		stack = new ArrayDeque<Integer>();
		Writer ow = new OutputStreamWriter(System.out);
		writer = new PrintWriter(ow, true);
		Reader ir = new InputStreamReader(System.in);
		reader = new BufferedReader(ir);
	}

	public char getKey(){
		return field.getKey();
	}
	
	public int get(){
		if(stack.size() == 0){
			return 0;
		}
		return stack.getLast();
	}
	
	public void pop(){
		if(stack.size() == 0){
			return;
		}
		stack.removeLast();
	}
	
	public void push(int num){
		stack.addLast(num);
	}

	public void finishJob(){
		isFinished = true;
	}

	public boolean jobIsFinished(){
		return isFinished;
	}

	public int size(){
		return stack.size();
	}

	public void changePosition(){
		field.changePosition();
	}

	public void changeWayUp(){
		field.changeWayUp();
	}

	public void changeWayDown(){
		field.changeWayDown();
	}

	public void changeWayLeft(){
		field.changeWayLeft();
	}

	public void changeWayRight(){
		field.changeWayRight();
	}

	public BufferedReader getReader(){
		return reader;
	}

	public PrintWriter getWriter(){
		return writer;
	}

	public char getKey(int x, int y){
		return field.getKey(x, y);
	}

	public void changeField(char value, int x, int y){
		field.changeField(value, x, y);
	}
	
	private Field field;
	private ArrayDeque<Integer> stack;
	private boolean isFinished = false;
	private PrintWriter writer;
	private BufferedReader reader;
}
