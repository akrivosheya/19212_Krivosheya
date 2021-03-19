import java.lang.RuntimeException;
import java.util.logging.Logger;

/**
 * Class for changing direction. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Navigator implements Command {
	/**
	 * Changes position by symbol in the field.
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context) {
		char newWay = context.getKey();
		switch(newWay) {
			case '^':
				log.info("Way = UP");
				context.changeWayUp();
				break;
			case 'v':
				log.info("Way = DOWN");
				context.changeWayDown();
				break;
			case '<':
				log.info("Way = LEFT");
				context.changeWayLeft();
				break;
			case '>':
				log.info("Way = RIGHT");
				context.changeWayRight();
				break;
		}
		context.changePosition();
	}
	static final Logger log = Logger.getLogger(Navigator.class.getName());
}