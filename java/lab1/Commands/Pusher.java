import java.lang.RuntimeException;

public class Pusher implements Command{
	@Override
	public void execute(Context context){
		context.push(Character.digit(context.getKey(), Character.MAX_RADIX));
		context.changePosition();
	}
}