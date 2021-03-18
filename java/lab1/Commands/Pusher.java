import java.lang.RuntimeException;

/**
 * Class for pushing number in the top of stack. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Pusher implements Command {
	/**
	 * Pushes number to the top of stack.
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context) {
		context.push(Character.digit(context.getKey(), Character.MAX_RADIX));
		context.changePosition();
	}
}