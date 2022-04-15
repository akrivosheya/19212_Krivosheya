import java.lang.*;
import java.io.*;
import java.util.logging.Logger;

/**
 * Class for writing text. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class StringMode implements Command {
	/**
	 * Starts read text until second quatation mark and writes this text.
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context) {
		StringBuilder text = new StringBuilder("");
		context.changePosition();
		while(context.getKey() != '"') {
			text.append(context.getKey());
			context.changePosition();
		}
		log.info("prints " + text.toString());
		context.getIO().println(text.toString());
		context.changePosition();
	}
	static final Logger log = Logger.getLogger(StringMode.class.getName());
}