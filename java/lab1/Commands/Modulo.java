import java.lang.RuntimeException;

public class Modulo implements Command{
	@Override
	public void execute(Context context){
		int firstOperand, secondOperand;
		if(context.size() < 2){
			throw new RuntimeException("Addition needs 2 operands");
		}
		firstOperand = context.get();
		context.pop();
		secondOperand = context.get();
		if (secondOperand == 0){
			throw new RuntimeException("% by zero");
		}
		context.push(firstOperand);
		context.push(firstOperand % secondOperand);
		context.changePosition();
	}
}