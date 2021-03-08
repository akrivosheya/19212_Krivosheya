import java.lang.RuntimeException;

public class Putter implements Command{
	@Override
	public void execute(Context context){
		int value, x, y;
		value = context.get();
		x = context.get();
		y = context.get();
		context.changeField((char)value, x, y);
		context.changePosition();
	}
}