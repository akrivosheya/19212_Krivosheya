import java.util.Vector;

public class Addition implements Command{
	@Override
	public boolean execute(Vector<Integer> stack){
		int firstOperand, secondOperand;
		if(stack.size() < 2){
			System.out.println("Addition need 2 operands");
			return !success;
		}
		firstOperand = stack.lastElement();
		stack.remove(stack.size() - 1);
		secondOperand = stack.lastElement();
		stack.remove(stack.size() - 1);
		stack.add(firstOperand + secondOperand);
		return success;
	}
}
