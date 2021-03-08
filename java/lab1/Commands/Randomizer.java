import java.lang.RuntimeException;
import java.util.Random;

public class Randomizer implements Command{
	@Override
	public void execute(Context context){
		Random rand = new Random();
		int randomNumb = rand.nextInt(COUNT_OF_WAYS);
		switch(randomNumb){
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

	private int COUNT_OF_WAYS = 3;
}