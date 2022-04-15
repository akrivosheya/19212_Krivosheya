import java.lang.RuntimeException;
import java.util.logging.LogManager;
import java.util.logging.Logger;

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
			log.info(context.size() + " operands");
			throw new RuntimeException("Division needs 2 operands");
		}
		firstOperand = context.get();
		context.pop();
		secondOperand = context.get();
		if (secondOperand == 0) {
			log.info("secondOperand == 0");
			throw new RuntimeException("Division by zero");
		}
		context.push(firstOperand);
		context.push(firstOperand / secondOperand);
		context.changePosition();
		log.info(firstOperand + " / " + secondOperand + " = " + firstOperand / secondOperand);
	}
	static final Logger log = Logger.getLogger(Division.class.getName());
}