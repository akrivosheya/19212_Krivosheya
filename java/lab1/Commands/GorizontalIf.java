import java.lang.RuntimeException;

public class GorizontalIf implements Command{
	@Override
	public void execute(Context context){
		int value;
		if(context.size() < 1){
			throw new RuntimeException("Stack is empty");
		}
		value = context.get();
		if(value != 0){
			context.changeWayLeft();
		}
		else{
			context.changeWayRight();
		}
		context.changePosition();
	}
}