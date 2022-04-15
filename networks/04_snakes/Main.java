import org.newdawn.slick.AppGameContainer;
import org.newdawn.slick.SlickException;

public class Main{
	public static void main(String[] argv){
		String gameName = "LOL";
		int sizeX = 500;
		int sizeY = 500;
		boolean isFull = false;
		try{
			AppGameContainer appgc;
			appgc = new AppGameContainer(new View(gameName));
			appgc.setDisplayMode(sizeX, sizeY, isFull);
			appgc.start();
		}
		catch (SlickException exception){
			System.err.println(exception);
		}
	}
	
	
}