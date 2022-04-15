import java.lang.RuntimeException;
import java.util.logging.Logger;

/**
 * Class for getting symbol in defined position of field. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Getter implements Command {
	/**
	 * Takes 2 coordinatesfrom the top of stack and puts symbol int this position of field in stack.
	 * @throws RuntimeException If stack contains less than 2 operands.
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context) {
		if(context.size() < 2) {
			throw new RuntimeException("Getter needs 2 operands");
		}
		int x, y;
		x = context.get();
		context.pop();
		y = context.get();
		context.push(x);
		char value = context.getKey(x, y);
		context.push((int)value);
		context.changePosition();
		log.info("Pushes " + value + " from " + x + ":" + y);
	}
	static final Logger log = Logger.getLogger(Getter.class.getName());
}