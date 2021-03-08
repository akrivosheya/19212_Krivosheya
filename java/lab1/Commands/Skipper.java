import java.lang.RuntimeException;

public class Skipper implements Command{
	@Override
	public void execute(Context context){
		context.changePosition();
		context.changePosition();
	}
}
