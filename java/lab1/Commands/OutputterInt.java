import java.lang.RuntimeException;

/**
 * Class for printing number in the top of stack. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class OutputterInt implements Command {
	/**
	 * Takes number from the top of stack and prints it.
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context) {
		context.getIO().printInt(context.get());
		context.changePosition();
	}
}