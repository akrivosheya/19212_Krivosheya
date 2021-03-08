import java.lang.RuntimeException;

public class OutputterChar implements Command{
	@Override
	public void execute(Context context){
		context.getWriter().println((char)context.get());
		context.changePosition();
	}
}