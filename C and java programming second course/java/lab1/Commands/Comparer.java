import java.lang.RuntimeException;
import java.util.logging.*;

/**
 * Class for comparing two numbers. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Comparer implements Command {
	/**
	 * Takes two numbers from the stack and compares them.
	 * If first operand more than second puts 1 in stack. Else puts 0.
	 * @throws RuntimeException If stack contains less than 2 operands.
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context) {
		int firstOperand, secondOperand;
		if(context.size() < 2){
			log.info(context.size() + " operands");
			throw new RuntimeException("Comparer needs 2 operands");
		}
		firstOperand = context.get();
		context.pop();
		secondOperand = context.get();
		context.push(firstOperand);
		context.push((firstOperand > secondOperand) ? 1 : 0);
		context.changePosition();
		log.info(firstOperand + " > " + secondOperand + " = " + (firstOperand > secondOperand));
	}
	static final Logger log = Logger.getLogger(Comparer.class.getName());
}