import java.lang.RuntimeException;

public class Navigator implements Command{
	@Override
	public void execute(Context context){
		if(context.size() < 1){
			throw new RuntimeException("Stack is empty");
		}
		char newWay = context.getKey();
		switch(newWay){
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