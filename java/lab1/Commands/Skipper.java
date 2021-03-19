import java.lang.RuntimeException;
import java.util.logging.Logger;

/**
 * Class for duplicating next command. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Skipper implements Command {
	/**
	 * Skips next command in the field.
	 * @throws RuntimeException If stack contains less than 1 operand.
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context) {
		log.info("Changes position twice");
		context.changePosition();
		context.changePosition();
	}
	static final Logger log = Logger.getLogger(Skipper.class.getName());
}