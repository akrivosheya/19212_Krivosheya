import java.lang.RuntimeException;

public class Getter implements Command{
	@Override
	public void execute(Context context){
		int x, y;
		x = context.get();
		context.pop();
		y = context.get();
		context.push(x);
		char value = context.getKey(x, y);
		context.push((int)value);
		context.changePosition();
	}
}