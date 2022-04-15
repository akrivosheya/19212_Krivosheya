import java.lang.RuntimeException;
import java.util.logging.Logger;

/**
 * Class for multiplicating number in the top of stack. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Multiplication implements Command {
	/**
	 * Takes 2 numbers from the top of stack and puts result of multiplication in stack.
	 * @throws RuntimeException If stack contains less than 2 operand.
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context) {
		int firstOperand, secondOperand;
		if(context.size() < 2) {
			log.info(context.size() + " elements");
			throw new RuntimeException("Multiplication needs 2 operands");
		}
		firstOperand = context.get();
		context.pop();
		secondOperand = context.get();
		context.push(firstOperand);
		context.push(firstOperand * secondOperand);
		context.changePosition();
		log.info(firstOperand + " * " + secondOperand + " = " + (firstOperand * secondOperand));
	}
	static final Logger log = Logger.getLogger(Multiplication.class.getName());
}