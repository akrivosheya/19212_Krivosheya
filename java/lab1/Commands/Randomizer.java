import java.lang.RuntimeException;
import java.util.Random;

/**
 * Class for choosing random direction. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Randomizer implements Command {
	/**
	 * Chooses random direction.
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context) {
		Random rand = new Random();
		int randomNumb = rand.nextInt(COUNT_OF_WAYS);
		switch(randomNumb) {
			case 0:
				context.changeWayUp();
				break;
			case 1:
				context.changeWayDown();
				break;
			case 2:
				context.changeWayLeft();
				break;
			case 3:
				context.changeWayRight();
				break;
		}
		context.changePosition();
	}

	private int COUNT_OF_WAYS = 4;
}