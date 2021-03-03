import java.util.*;
import java.lang.RuntimeException;

public class Context{
	Context(Scanner scan){
		try {
			field = new Field(scan);
		} catch (RuntimeException error){
			throw error;
		}
		stack = new ArrayDeque<Integer>();
	}

	public void printlnNumb(int num){
		System.out.println(num);
	}
	
	public void printlnString(String text){
		System.out.println(text);
	}

	public char getKey(){
		return field.getKey();
	}
	
	public int get(){
		return stack.getLast();
	}
	
	public int pop(){
		return stack.removeLast();
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
	
	private Field field;
	private ArrayDeque<Integer> stack;
	private boolean isFinished = false;
}
