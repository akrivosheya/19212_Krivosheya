import java.lang.RuntimeException;

/**
 * Class for division two numbers. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Division implements Command {
	/**
	 * Takes two numbers from the stack and put result of division in stack.
	 * @throws RuntimeException If second operand is 0.
	 * @throws RuntimeException If stack contains less than 2 operands.
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context) {
		int firstOperand, secondOperand;
		if(context.size() < 2) {
			throw new RuntimeException("Addition needs 2 operands");
		}
		firstOperand = context.get();
		context.pop();
		secondOperand = context.get();
		if (secondOperand == 0) {
			throw new RuntimeException("Division by zero");
		}
		context.push(firstOperand);
		context.push(firstOperand / secondOperand);
		context.changePosition();
	}
}