import java.lang.RuntimeException;

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
		context.changePosition();
		context.changePosition();
	}
}