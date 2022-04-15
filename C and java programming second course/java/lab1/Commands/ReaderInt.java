import java.lang.RuntimeException;
import java.io.IOException;
import java.util.logging.Logger;

/**
 * Class for reading number. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class ReaderInt implements Command {
	/**
	 * Reads number and puts it in stack.
	 * @throws RuntimeException If reading ended with an error.
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context) {
		String text = null;
		text = context.getIO().readLine();
		int numb = 0;
		for(int i = 0; i < text.length(); ++i)  {
			char symb = text.charAt(i);
			if(!Character.isDigit(symb)){
				break;
			}
			numb = numb * 10 + Character.digit(symb, Character.MAX_RADIX);
		}
		log.info("Pushes " + numb);
		context.push(numb);
		context.changePosition();
	}
	static final Logger log = Logger.getLogger(ReaderInt.class.getName());
}