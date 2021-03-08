import java.lang.RuntimeException;

public class Popper implements Command{
	@Override
	public void execute(Context context){
		context.pop();
		context.changePosition();
	}
}