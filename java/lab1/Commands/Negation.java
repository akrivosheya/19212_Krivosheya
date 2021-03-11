import java.lang.RuntimeException;

/**
 * Class for taking negative value of number in the top of stack. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Negation implements Command {
	/**
	 * Takes number from the top of stack and puts its negation value in stack.
	 * @throws RuntimeException If stack contains less than 1 operand.
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context) {
		int operand;
		if(context.size() < 1) {
			throw new RuntimeException("Stack is empty");
		}
		operand = context.get();
		operand = (operand == 0) ? 1 : 0;
		context.push(operand);
		context.changePosition();
	}
}