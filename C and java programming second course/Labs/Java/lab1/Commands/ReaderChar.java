import java.lang.RuntimeException;
import java.io.IOException;
import java.util.logging.Logger;

/**
 * Class for reading character. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class ReaderChar implements Command{
	/**
	 * Reads character and puts its value in stack.
	 * @throws RuntimeException If reading ended with an error.
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context){
		char symb = context.getIO().read();
		log.info("Pushes " +symb);
		context.push((int)symb);
		context.changePosition();
	}
	static final Logger log = Logger.getLogger(ReaderChar.class.getName());
}