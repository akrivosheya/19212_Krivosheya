import java.util.logging.Logger;

/**
 * Class for pushing number in the top of stack. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Putter implements Command{
	/**
	 * Pushes number to the top of stack.
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context){
		log.info("Pushes " + Character.digit(context.getKey(), Character.MAX_RADIX));
		context.push(Character.digit(context.getKey(), Character.MAX_RADIX));
		context.changePosition();
	}
	static final Logger log = Logger.getLogger(Putter.class.getName());
}