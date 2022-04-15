import javafx.application.Application;
import javafx.stage.*;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.scene.shape.Line;
import javafx.scene.text.*;
import javafx.application.Platform;
import java.util.*;

/**
 * Class for showing information about the game.
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Information extends Application{
	
	/**
	 * Sets base options for object
	 * @param initTitle - title of window.
	 * @param initContr - controller for getting information from model.
	 * @param initMode - flag that choose current information.
	*/
	public Information(String initTitle, Controller initContr, Controller.Mode initMode){
		title = initTitle;
		contr = initContr;
		mode = initMode;
	}
	
	/**
	 * Creates window with information.
	 * @param primaryStage - using window.
	*/
	@Override
	public void start(Stage primaryStage){
		Group root = new Group();
        Scene scene = new Scene(root, SCENE_WIDTH, SCENE_HEIGHT, Color.GREY);
        primaryStage.setScene(scene);
		primaryStage.setTitle(title);
		List<String> text = contr.getInfoText(mode);
		double y = FIRST_Y;
		if(mode == Controller.Mode.TAB){
			Line vertical = new Line(SCENE_WIDTH / 2, 0, SCENE_WIDTH / 2, SCENE_HEIGHT);
			root.getChildren().add(vertical);
			for(int i = 0; i < HOR_LINES * 2; i += 2){
				Line horizontal = new Line(0, y, SCENE_WIDTH, y);
				root.getChildren().add(horizontal);
				Text gamer = new Text(0, y, text.get(i));
				gamer.setFont(Font.font("Tahoma", FontWeight.NORMAL, 15));
				Text score = new Text(SCENE_WIDTH / 2, y, text.get(i + 1));
				score.setFont(Font.font("Tahoma", FontWeight.NORMAL, 15));
				root.getChildren().add(gamer);
				root.getChildren().add(score);
				y += OFFSET;
			}
		}
		else{
			for(String line : text){
				Text viewLine = new Text(0, y, line);
				viewLine.setFont(Font.font("Tahoma", FontWeight.NORMAL, 15));
				root.getChildren().add(viewLine);
				y += OFFSET;
			}
		}
		primaryStage.setMaxWidth(SCENE_WIDTH + OUTLINE_WIDTH);
		primaryStage.setMinWidth(SCENE_WIDTH + OUTLINE_WIDTH);
		primaryStage.setMaxHeight(SCENE_HEIGHT + TITLE_HEIGHT);
		primaryStage.setMinHeight(SCENE_HEIGHT + TITLE_HEIGHT);
		primaryStage.initModality(Modality.APPLICATION_MODAL);
		
		currentStage = primaryStage;
		primaryStage.show();
	}
	
	/**
	 * Closes window.
	*/
	public void exit(){
		currentStage.close();
	}
	
	/**
	 * Window height.
	*/
	private double SCENE_HEIGHT = 250;
	/**
	 * Window width.
	*/
	private double SCENE_WIDTH = 400;
	/**
	 * Height of title of window.
	*/
	private double TITLE_HEIGHT = 35;
	/**
	 * Width of outline.
	*/
	private double OUTLINE_WIDTH = 15;
	/**
	 * Y position of first token in information.
	*/
	private double FIRST_Y = 25;
	/**
	 * Offset between attributes of information in y.
	*/
	private double OFFSET = 25;
	/**
	 * Window title.
	*/
	private String title = null;
	/**
	 * Controller fo getting information of model.
	*/
	private Controller contr = null;
	/**
	 * Information mode.
	*/
	private Controller.Mode mode;
	/**
	 * Count of horizontal lines in tab.
	*/
	private int HOR_LINES = 10;
	/**
	 * Window.
	*/
	private Stage currentStage;
	
}