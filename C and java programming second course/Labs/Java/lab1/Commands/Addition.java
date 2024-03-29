import java.lang.RuntimeException;
import java.util.logging.*;

/**
 * Class for adding two numbers. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Addition implements Command {
	/**
	 * Takes two numbers from the stack and puts their sum in stack.
	 * @throws RuntimeException If stack contains less than 2 operands .
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context) {
		int firstOperand, secondOperand;
		if(context.size() < 2) {
			log.info(context.size() + " elements");
			throw new RuntimeException("Addition needs 2 operands");
		}
		firstOperand = context.get();
		context.pop();
		secondOperand = context.get();
		context.push(firstOperand);
		context.push(firstOperand + secondOperand);
		context.changePosition();
		log.info(firstOperand + " + " + secondOperand + " = " + (firstOperand + secondOperand));
	}
	static final Logger log = Logger.getLogger(Addition.class.getName());
}