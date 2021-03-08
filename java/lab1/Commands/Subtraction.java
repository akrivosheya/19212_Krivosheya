import java.lang.RuntimeException;

public class Subtraction implements Command{
	@Override
	public void execute(Context context){
		int firstOperand, secondOperand;
		if(context.size() < 2){
			throw new RuntimeException("Subtraction needs 2 operands");
		}
		firstOperand = context.get();
		context.pop();
		secondOperand = context.get();
		context.push(firstOperand);
		context.push(firstOperand - secondOperand);
		context.changePosition();
	}
}