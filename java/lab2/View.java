import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.shape.Rectangle;
import javafx.scene.Node;
import javafx.event.*;
import javafx.scene.input.MouseEvent;
import javafx.scene.paint.Color;
import javafx.scene.shape.StrokeType;
import java.util.*;
import javafx.animation.AnimationTimer;
import java.time.Duration;

/**
 * Class for showing process of game
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class View extends Application {

	/**
	 * Set starting configurations of scene.
	 * @param primaryStage.
	*/
    @Override
    public void start(Stage primaryStage) {
        Group root = new Group();
        Scene scene = new Scene(root, 600, 600, Color.GREY);
        primaryStage.setScene(scene);
	primaryStage.setTitle("Let's play a game");


	rectangles = contr.getRectangles("file.txt");
	if(rectangles == null){
        	primaryStage.show();
		return;
	}
	
	for(Rectangle rectangle : rectangles){
		rectangle.setOnMousePressed(new EventHandler<MouseEvent>() {
 
            		@Override
            		public void handle(MouseEvent event) {
				oldX = event.getSceneX();
				oldY = event.getSceneY();
            		}
        		});
		rectangle.setOnMouseDragged(new EventHandler<MouseEvent>() {
 
            		@Override
            		public void handle(MouseEvent event) {
				double x = event.getSceneX() - (oldX - rectangle.getX());
				double y = event.getSceneY() - (oldY - rectangle.getY());
				int res = 0;
				try{
					if((res = contr.move(rectangle.getX(), rectangle.getY(),
					x, y)) == CANT_MOVE){
					return;
				}
				}catch(Exception e){
					System.out.println("bad");//Change
				}
				if(res == IS_FINISH){
					//Checking
				}
				if(res == MOVE_HORIZONTAL){
                			rectangle.setX(x);
				}else{
                			rectangle.setY(y);
				}
				oldX = event.getSceneX();
				oldY = event.getSceneY();
            			}
        		});
			root.getChildren().add(rectangle);
	}
		

        primaryStage.show();
    }
 	/**
	 * Main function. Launches scene.
	 * @param args - entered arguements.
	*/
 public static void main(String[] args) {
        launch(args);
    }

	private double oldX;
	private double oldY;
	/**
	 * Controller that connects View and Model.
	*/
	private Controller contr = new Controller();
	private List<Rectangle> rectangles;
	private int CANT_MOVE = 1;
	private int IS_FINISH = 2;
	private int MOVE_HORIZONTAL = 3;
	private int MOVE_VERTICAL = 4;
}