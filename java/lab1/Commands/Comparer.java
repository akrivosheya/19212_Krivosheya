import java.lang.RuntimeException;

public class Comparer implements Command{
	@Override
	public void execute(Context context){
		int firstOperand, secondOperand;
		if(context.size() < 2){
			throw new RuntimeException("Comparer needs 2 operands");
		}
		firstOperand = context.get();
		context.pop();
		secondOperand = context.get();
		context.push(firstOperand);
		context.push((firstOperand > secondOperand) ? 1 : 0);
		context.changePosition();
	}
}