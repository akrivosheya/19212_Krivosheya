import java.lang.RuntimeException;
import java.io.*;

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
		String text = "";
		context.changePosition();
		while(context.getKey() != '"') {
			text += context.getKey();
			context.changePosition();
		}
		context.getIO().println(text);
		context.changePosition();
	}
}