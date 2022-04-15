import org.newdawn.slick.AppGameContainer;
import org.newdawn.slick.BasicGame;
import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.SlickException;
import org.newdawn.slick.Input;

public class View extends BasicGame
{
	public View(String gamename)
	{
		super(gamename);
		snakes = new Online();
		Thread thread = new Thread(() -> snakes.begin());
		thread.start();
	}

	@Override
	public void init(GameContainer container) throws SlickException {
	}

	@Override
	public void update(GameContainer container, int i) throws SlickException {}

	@Override
	public void render(GameContainer container, Graphics drawer) throws SlickException
	{
	}
	
	@Override
	public void keyPressed(int key, char c){
		switch(key){
			case Input.KEY_UP:
				snakes.changeDirection(UP);
				break;
			case Input.KEY_DOWN:
				snakes.changeDirection(DOWN);
				break;
			case Input.KEY_LEFT:
				snakes.changeDirection(LEFT);
				break;
			case Input.KEY_RIGHT:
				snakes.changeDirection(RIGHT);
				break;
		}
	}
	
	private Online snakes;
	private int UP = 0;
	private int DOWN = 1;
	private int LEFT = 2;
	private int RIGHT = 3;
	private Thread thread;
}