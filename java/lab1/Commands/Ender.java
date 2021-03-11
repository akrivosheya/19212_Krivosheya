/**
 * Class for finishing executing. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Ender implements Command {
	/**
	 * Changes flag jobIsFinished in the context.
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context) {
		context.finishJob();
	}
}