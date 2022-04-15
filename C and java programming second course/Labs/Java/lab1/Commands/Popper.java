import java.lang.RuntimeException;
import java.util.logging.Logger;

/**
 * Class for deleting value from the top of stack. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Popper implements Command {
	/**
	 * Deletes value from the top of stack.
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context) {
		log.info("Removes last element");
		context.pop();
		context.changePosition();
	}
	static final Logger log = Logger.getLogger(Popper.class.getName());
}