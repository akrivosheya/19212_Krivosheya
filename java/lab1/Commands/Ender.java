public class Ender implements Command{
	@Override
	public void execute(Context context){
		context.finishJob();
	}
}