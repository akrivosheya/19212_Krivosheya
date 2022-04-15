import java.lang.RuntimeException;
import java.util.logging.Logger;

/**
 * Class for taking a number modulo another in the top of stack. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Modulo implements Command {
	/**
	 * Takes 2 numbers from the top of stack and puts first number modulo second in stack.
	 * @throws RuntimeException If stack contains less than 2 operands.
	 * @throws RuntimeException If second operand is 0.
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context) {
		int firstOperand, secondOperand;
		if(context.size() < 2) {
			log.info(context.size() + " elements");
			throw new RuntimeException("Modulo needs 2 operands");
		}
		firstOperand = context.get();
		context.pop();
		secondOperand = context.get();
		if (secondOperand == 0) {
			log.info("secondOperand == 0");
			throw new RuntimeException("% by zero");
		}
		context.push(firstOperand);
		context.push(firstOperand % secondOperand);
		context.changePosition();
		log.info(firstOperand + " % " + secondOperand + " = " + (firstOperand % secondOperand));
	}
	static final Logger log = Logger.getLogger(Modulo.class.getName());
}