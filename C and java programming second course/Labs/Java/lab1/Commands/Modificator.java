import java.lang.RuntimeException;
import java.util.logging.Logger;

/**
 * Class for putting symbol in defined position of field. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Modificator implements Command {
	/**
	 * Takes 1 value and 2 coordinates from the top of stack and puts value in position of field by this coordinate.
	 * @throws RuntimeException If stack contains less than 3 operand.
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context) {
		if(context.size() < 3) {
			log.info(context.size() + " elements");
			throw new RuntimeException("Modificator needs 3 operands");
		}
		int value, x, y;
		value = context.get();
		context.pop();
		x = context.get();
		context.pop();
		y = context.get();
		context.push(x);
		context.push(value);
		context.changeField((char)value, x, y);
		log.info("Puts " + (char)value + " to " +  x + ":" + y);
		context.changePosition();
	}
	static final Logger log = Logger.getLogger(Modificator.class.getName());
}