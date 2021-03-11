import java.lang.RuntimeException;

/**
 * Class for subtracting numbers in the top of stack. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Subtraction implements Command {
	/**
	 * Takes 2 numbers from the top of stack and puts result of subtraction in stack.
	 * @throws RuntimeException If stack contains less than 1 operand.
	 * @throws RuntimeException If second operand is 0.
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context) {
		int firstOperand, secondOperand;
		if(context.size() < 2) {
			throw new RuntimeException("Subtraction needs 2 operands");
		}
		firstOperand = context.get();
		context.pop();
		secondOperand = context.get();
		context.push(firstOperand);
		context.push(firstOperand - secondOperand);
		context.changePosition();
	}
}