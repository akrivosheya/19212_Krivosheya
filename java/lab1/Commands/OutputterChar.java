import java.lang.RuntimeException;

/**
 * Class for printing character with value in the top of stack. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class OutputterChar implements Command {
	/**
	 * Takes value from the top of stack and prints character with this value.
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context) {
		context.getIO().printChar((char)context.get());
		context.changePosition();
	}
}