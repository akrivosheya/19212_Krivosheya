import java.lang.RuntimeException;
import java.util.logging.Logger;

/**
 * Class for choosing direction by value in the top of stack. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class VerticalIf implements Command {
	/**
	 * Takes value from the top of stack.
	 * If value is 0 changes direction to DOWN. Else to RIGHT.
	 * @throws RuntimeException If stack contains less than 1 operand.
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context)  {
		int value;
		if(context.size() < 1){
			log.info(context.size() + " elements");
			throw new RuntimeException("Stack is empty");
		}
		value = context.get();
		if(value != 0) {
			log.info("!= 0 => UP");
			context.changeWayUp();
		}
		else{
			log.info("== 0 => DOWN");
			context.changeWayDown();
		}
		context.changePosition();
	}
	static final Logger log = Logger.getLogger(VerticalIf.class.getName());
}