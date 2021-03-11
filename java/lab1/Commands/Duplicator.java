import java.lang.RuntimeException;

/**
 * Class for duplicating number in the top of stack. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Duplicator implements Command {
	/**
	 * Takes number from the top of stack and puts its copy in stack.
	 * @throws RuntimeException If stack contains less than 1 operand.
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context) {
		int value;
		if(context.size() < 1) {
			throw new RuntimeException("Stack is empty");
		}
		value = context.get();
		context.push(value);
		context.changePosition();
	}
}