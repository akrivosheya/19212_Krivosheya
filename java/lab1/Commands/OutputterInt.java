import java.lang.RuntimeException;

public class OutputterInt implements Command{
	@Override
	public void execute(Context context){
		context.getWriter().println(context.get());
		context.changePosition();
	}
}