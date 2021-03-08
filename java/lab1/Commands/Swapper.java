import java.lang.RuntimeException;

public class Swapper implements Command{
	@Override
	public void execute(Context context){
		int firstOperand, secondOperand;
		if(context.size() < 2){
			throw new RuntimeException("Swapper needs 2 operands");
		}
		firstOperand = context.get();
		context.pop();
		secondOperand = context.get();
		context.pop();
		context.push(firstOperand);
		context.push(secondOperand);
		context.changePosition();
	}
}