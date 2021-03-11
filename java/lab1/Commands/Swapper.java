import java.lang.RuntimeException;

/**
 * Class for swappsing 2 numbers in the top of stack. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Swapper implements Command {
	/**
	 * Takes 2 snumber from the top of stack, swaps them and puts them in stack.
	 * @throws RuntimeException If stack contains less than 2 operand.
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context) {
		int firstOperand, secondOperand;
		if(context.size() < 2) {
			throw new RuntimeException("Swapper needs 2 operands");
		}
		firstOperand = context.get();
		context.pop();
		secondOperand = context.get();
		context.pop();
		context.push(firstOperand);
		context.push(secondOperand);
		context.changePosition();
	}
}