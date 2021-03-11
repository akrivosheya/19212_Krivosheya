import java.lang.RuntimeException;

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
				context.changeWayUp();
				break;
			case 'v':
				context.changeWayDown();
				break;
			case '<':
				context.changeWayLeft();
				break;
			case '>':
				context.changeWayRight();
				break;
		}
		context.changePosition();
	}
}