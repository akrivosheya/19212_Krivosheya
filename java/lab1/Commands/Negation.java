import java.lang.RuntimeException;

public class Negation implements Command{
	@Override
	public void execute(Context context){
		int operand;
		if(context.size() < 1){
			throw new RuntimeException("Stack is empty");
		}
		operand = context.get();
		context.push(!operand);
		context.changePosition();
	}
}