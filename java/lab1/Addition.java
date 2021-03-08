package commands;

import java.lang.RuntimeException;

public class Addition implements Command{
	@Override
	public void execute(Context context){
		int firstOperand, secondOperand;
		if(context.size() < 2){
			throw new RuntimeException("Addition need 2 operands");
		}
		firstOperand = context.get();
		context.pop();
		secondOperand = context.get();
		context.push(firstOperand);
		context.push(firstOperand + secondOperand);
	}
}
