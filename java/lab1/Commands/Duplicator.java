import java.lang.RuntimeException;

public class Duplicator implements Command{
	@Override
	public void execute(Context context){
		int value;
		if(context.size() < 1){
			throw new RuntimeException("Stack is empty");
		}
		value = context.get();
		context.push(value);
		context.changePosition();
	}
}