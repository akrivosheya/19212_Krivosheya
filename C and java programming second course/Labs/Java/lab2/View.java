import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.stage.*;
import javafx.scene.shape.Rectangle;
import javafx.scene.Node;
import javafx.event.*;
import javafx.scene.input.MouseEvent;
import javafx.scene.paint.Color;
import javafx.scene.shape.StrokeType;
import java.util.*;
import javafx.animation.AnimationTimer;
import java.time.Duration;
import javafx.scene.text.*;
import javafx.scene.control.*;

/**
 * Class for showing process of game
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class View extends Application {

	/**
	 * Set starting configurations of scene.
	 * @param primaryStage - stage where everything is happening.
	*/
    @Override
    public void start(Stage primaryStage) {
		timer.cancel();
		stage = primaryStage;
		Group root = new Group();
        Scene scene = new Scene(root, SCENE_WIDTH, SCENE_HEIGHT + MENU_HEIGHT, Color.GREY);
		game = new Group();
		mainMenu = new Group();
		levelsInfo = new Group();
		menuBar = createMenuBar();
		Rectangle menuLine = new Rectangle(SCENE_WIDTH, MENU_HEIGHT, Color.WHITE);
		root.getChildren().add(menuLine);
		root.getChildren().add(menuBar);
		root.getChildren().add(game);
		root.getChildren().add(mainMenu);
		root.getChildren().add(levelsInfo);
        primaryStage.setScene(scene);
		primaryStage.setTitle("Let's play a game");
		levels = createLevels();
		for(Button level : levels){
			mainMenu.getChildren().add(level);
		}
		Rectangle info = new Rectangle(INFO_WIDTH, SCENE_HEIGHT + MENU_HEIGHT, Color.YELLOW);
		info.setX(SCENE_WIDTH - INFO_WIDTH);
		info.setY(0);
		mainMenu.getChildren().add(info);
		setLevelsText(levelsInfo);
		primaryStage.setMaxHeight(SCENE_HEIGHT + MENU_HEIGHT + TITLE_HEIGHT);
		primaryStage.setMinHeight(SCENE_HEIGHT + MENU_HEIGHT + TITLE_HEIGHT);
		primaryStage.setMaxWidth(SCENE_WIDTH + OUTLINE_WIDTH);
		primaryStage.setMinWidth(SCENE_WIDTH + OUTLINE_WIDTH);
		primaryStage.show();
    }

	/**
	 * Creates information about current level.
	 * @param game - group that contains attributes for playing.
	*/
	private void setGameText(Group game){
		StringBuilder stringLevel = new StringBuilder("Level ");
		String stringStepsValue = new String(String.valueOf(contr.getSteps()));
		stringLevel.append(contr.getLevel());
		Text level = new Text(TEXT_POSITION_X, 50, stringLevel.toString());
		Text steps = new Text(TEXT_POSITION_X, 100, "Steps");
		stepsValue = new Text(TEXT_POSITION_X, 150, String.valueOf(contr.getSteps()));
		Text time = new Text(TEXT_POSITION_X, 200, "Time");
		timeValue = new Text(TEXT_POSITION_X, 250, "00:00");
		Text best = new Text(TEXT_POSITION_X, 300, "Best time");
		Text bestValue = new Text(TEXT_POSITION_X, 350, contr.getBest());
		level.setFont(Font.font("Tahoma", FontWeight.NORMAL, 30));
		steps.setFont(Font.font("Tahoma", FontWeight.NORMAL, 30));
		time.setFont(Font.font("Tahoma", FontWeight.NORMAL, 30));
		stepsValue.setFont(Font.font("Tahoma", FontWeight.NORMAL, 30));
		timeValue.setFont(Font.font("Tahoma", FontWeight.NORMAL, 30));
		bestValue.setFont(Font.font("Tahoma", FontWeight.NORMAL, 30));
		best.setFont(Font.font("Tahoma", FontWeight.NORMAL, 30));
		game.getChildren().add(level);
		game.getChildren().add(steps);
		game.getChildren().add(time);
		game.getChildren().add(stepsValue);
		game.getChildren().add(timeValue);
		game.getChildren().add(best);
		game.getChildren().add(bestValue);
	}
	
	/**
	 * Creates information about all levels.
	 * @param mainMenu - group that contains attributes main menu.
	*/
	private void setLevelsText(Group levelsInfo){
		levelsInfo.getChildren().clear();
		List<String> text = new ArrayList<String>();
		text = contr.getLevelsInfo();
		for(int i = 0; i < text.size(); ++i){
			Text line = new Text(TEXT_POSITION_X, i * SCENE_HEIGHT / text.size() + MENU_HEIGHT, text.get(i));
			line.setFont(Font.font("Tahoma", FontWeight.NORMAL, 20));
			levelsInfo.getChildren().add(line);
		}
	}
	
	/**
	 * Creates and shows stage for getting confirmation for actions.
	 * @param window - stage where will be all attributes.
	 * @param info - text that will be showing in stage.
	 * @param value - action that will be done if user choose "yes".
	*/
	private void confirm(Stage window, String info, EventHandler<ActionEvent> value){
		Group root = new Group();
        Scene scene = new Scene(root, WINDOW_WIDTH, WINDOW_HEIGHT, Color.GREY);
        window.setScene(scene);
		window.setTitle("Confirm reset");
		Text text = new Text(0, WINDOW_HEIGHT / 10, info);
		text.setFont(Font.font("Tahoma", FontWeight.NORMAL, 15));
		Button yes = new Button("YES");
		Button no = new Button("NO");
		yes.setOnAction(value);
		no.setOnAction(e -> window.close());
		yes.setFont(Font.font("Tahoma", FontWeight.NORMAL, 15));
		no.setFont(Font.font("Tahoma", FontWeight.NORMAL, 15));
		yes.setTranslateY((double)(WINDOW_HEIGHT / 2));
		no.setTranslateX((double)(WINDOW_WIDTH / 2));
		no.setTranslateY((double)(WINDOW_HEIGHT / 2));
		root.getChildren().add(yes);
		root.getChildren().add(no);
		root.getChildren().add(text);
		window.setMaxWidth(WINDOW_WIDTH + OUTLINE_WIDTH);
		window.setMinWidth(WINDOW_WIDTH + OUTLINE_WIDTH);
		window.setMaxHeight(WINDOW_HEIGHT + TITLE_HEIGHT);
		window.setMinHeight(WINDOW_HEIGHT + TITLE_HEIGHT);
		window.initModality(Modality.APPLICATION_MODAL);
		window.show();
	}
	
	/**
	 * Creates menu bar.
	*/
	private MenuBar createMenuBar(){
		MenuBar newMenu;
		gameMenu = new Menu("Game");
		Menu help = new Menu("Help");
		MenuItem scores = new MenuItem("Scores");
		reset = new MenuItem("Reset the game");
		restart = new MenuItem("Restart");
		MenuItem exit = new MenuItem("Exit");
		scores.setOnAction(e -> {if(infoWindow != null){
										infoWindow.exit();
									}
									infoWindow = new Information("Scores", contr, Controller.Mode.TAB);
									infoWindow.start(new Stage());
								});
		reset.setOnAction(e -> {Stage window = new Stage();
								confirm(window, "Are you sure you want to reset scores?", t -> {contr.reset();
																					setLevelsText(levelsInfo);
																					window.close();});});
		restart.setOnAction(e -> {Stage window = new Stage();
								confirm(window, "Are you sure you want to restart?", t -> {loadLevel(contr.getCurrentLevel());
																								window.close();});});
		exit.setOnAction(e -> {timer.cancel();
								Platform.exit();});
		gameMenu.getItems().add(scores);
		gameMenu.getItems().add(reset);
		gameMenu.getItems().add(exit);
		MenuItem viewHelp = new MenuItem("View help");
		MenuItem about = new MenuItem("About");
		viewHelp.setOnAction(e -> {if(infoWindow != null){
										infoWindow.exit();
									}
									infoWindow = new Information("Help", contr, Controller.Mode.HELP);
									infoWindow.start(new Stage());
								});
		about.setOnAction(e -> {if(infoWindow != null){
										infoWindow.exit();
									}
									infoWindow = new Information("About", contr, Controller.Mode.ABOUT);
									infoWindow.start(new Stage());
								});
		help.getItems().add(viewHelp);
		help.getItems().add(about);
		
		newMenu = new MenuBar(gameMenu, help);
		return newMenu;
	}
	
	/**
	 * Creates all buttons of levels on main menu.
	*/
	private List<Button> createLevels(){
		List<Button> levels = new ArrayList<Button>();
		List<String> names = contr.getLevelsNames();
		int i = 0;
		for(String name : names){
			Button level = new Button(name);
			level.setOnAction(e -> loadLevel(name + ".txt"));
			level.setFont(Font.font("Tahoma", FontWeight.NORMAL, 30));
			level.setTranslateX((double)(i % COLUMS * (DISTANCE + DISTANCE / 2)));
			level.setTranslateY((double)(i / COLUMS * DISTANCE / 1.7 + MENU_HEIGHT * 2));
			levels.add(level);
			++i;
		}
		return levels;
	}
	
	/**
	 * Load choosen level.
	 * @param name - name of file with level's configurations, that is giving by pushed button.
	*/
	private void loadLevel(String name){
		game.getChildren().clear();
		
		timer.cancel();
		timer = new Timer();
		rectangles = contr.getRectangles(name);
		if(rectangles == null){
			timer.cancel();
			return;
		}	
		mainMenu.setVisible(false);
		levelsInfo.setVisible(false);
		game.setVisible(true);
		gameMenu.getItems().remove(1);
		gameMenu.getItems().add(1, restart);
	
		for(Rectangle rectangle : rectangles){
			rectangle.setY(rectangle.getY() + MENU_HEIGHT);
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
					if(isShifted){
						if(typeOfPlatform == MOVE_HORIZONTAL){
							if((shiftedX < oldX && oldX < event.getSceneX()) ||
								(shiftedX > oldX && oldX > event.getSceneX())){
									isShifted = false;
							}
							else{
								return;
							}
						} else {
							if((shiftedY < oldY && oldY < event.getSceneY()) ||
								(shiftedY > oldY && oldY > event.getSceneY())){
									isShifted = false;
							}
							else{
								return;
							}
						}
					}
					double x = event.getSceneX() - (oldX - rectangle.getX());
					double y = event.getSceneY() - (oldY - rectangle.getY()) - MENU_HEIGHT;
					int res = 0;
					try{
						res = contr.move(rectangle.getX(), rectangle.getY() - MENU_HEIGHT,
								x, y);
					}catch(Exception e){
						System.out.println("bad");//Change
					}
					if(res == MOVE_HORIZONTAL){
								rectangle.setX(x);
								typeOfPlatform = res;
					} else if (res == MOVE_VERTICAL){
								rectangle.setY(y + MENU_HEIGHT);
								typeOfPlatform = res;
					}
					else{
						isShifted = true;
						shiftedX = event.getSceneX();
						shiftedY = event.getSceneY();
						oldX = oldX - rectangle.getX();
						oldY = oldY - rectangle.getY();
						rectangle.setX(contr.getViewCoord(rectangle.getX()));
						rectangle.setY(contr.getViewCoord(rectangle.getY() - MENU_HEIGHT) + MENU_HEIGHT);
						oldX = oldX + rectangle.getX();
						oldY = oldY + rectangle.getY();
						return;
					}
					oldX = event.getSceneX();
					oldY = event.getSceneY();
				}

			});
			rectangle.setOnMouseReleased(new EventHandler<MouseEvent>() {
				@Override
				public void handle(MouseEvent event) {
					isShifted = false;
					if(contr.isFinished()){
						game.setVisible(false);
						gameMenu.getItems().remove(1);
						timer.cancel();
						if(contr.isRecord()){
							saveResult();
						}
						gameMenu.getItems().add(1, reset);
						mainMenu.setVisible(true);
						levelsInfo.setVisible(true);
						return;
					}
					contr.increaseSteps();
					stepsValue.setText(String.valueOf(contr.getSteps()));
					rectangle.setX(contr.getViewCoord(rectangle.getX()));
					rectangle.setY(contr.getViewCoord(rectangle.getY() - MENU_HEIGHT) + MENU_HEIGHT);
				}
			});
			game.getChildren().add(rectangle);
		}
		Rectangle info = new Rectangle(INFO_WIDTH, SCENE_HEIGHT + MENU_HEIGHT, Color.GREEN);
		info.setX(SCENE_WIDTH - INFO_WIDTH);
		info.setY(0);
		game.getChildren().add(info);
		setGameText(game);
		timer.schedule(new TimerTask(){
			@Override
			public void run(){
				contr.increaseTime();
				timeValue.setText(contr.getTime());
			}
		}, SECOND, SECOND);
	}

	/**
	 * Save new best time of current level.
	*/
	private void saveResult(){
		Group root = new Group();
        Scene scene = new Scene(root, WINDOW_WIDTH, WINDOW_HEIGHT, Color.GREY);
		Stage window = new Stage();
        window.setScene(scene);
		window.setTitle("Save result");
		TextField name = new TextField();
		Text nameWriting = new Text(0, WINDOW_HEIGHT / 10, "Your name:");
		nameWriting.setFont(Font.font("Tahoma", FontWeight.NORMAL, 15));
		Button ok = new Button("OK");
		Button cancel = new Button("CANCEL");
		ok.setOnAction(e -> {contr.saveResult(name.getText());
							setLevelsText(levelsInfo);
							window.close();});
		cancel.setOnAction(e -> window.close());
		ok.setFont(Font.font("Tahoma", FontWeight.NORMAL, 15));
		cancel.setFont(Font.font("Tahoma", FontWeight.NORMAL, 15));
		ok.setTranslateY((double)(WINDOW_HEIGHT / 2));
		cancel.setTranslateX((double)(WINDOW_WIDTH / 2));
		cancel.setTranslateY((double)(WINDOW_HEIGHT / 2));
		name.setTranslateX((double)(WINDOW_WIDTH / 2));
		root.getChildren().add(ok);
		root.getChildren().add(cancel);
		root.getChildren().add(name);
		root.getChildren().add(nameWriting);
		window.show();
	}

 	/**
	 * Main function. Launches scene.
	 * @param args - entered arguements.
	*/
 public static void main(String[] args) {
        launch(args);
    }

	/**
	 * X position of cursor when some platform is pushed or dragged.
	*/
	private double oldX;
	/**
	 * Y position of cursor when some platform is pushed or dragged.
	*/
	private double oldY;
	/**
	 * X position of shifted cursor when some platform is pushed or dragged.
	*/
	private double shiftedX;
	/**
	 * Y position of shifted cursor when some platform is pushed or dragged.
	*/
	private double shiftedY;
	/**
	 * Y position of shifted cursor when some platform is pushed or dragged.
	*/
	private int typeOfPlatform;
	/**
	 * Controller that connects View and Model.
	*/
	private Controller contr = new Controller();
	/**
	 * Rectangles of current level.
	*/
	private List<Rectangle> rectangles = null;
	/**
	 * Signal that current dragged platform can't move.
	*/
	private int CANT_MOVE = 1;
	/**
	 * Signal that current dragged platform is horizontal.
	*/
	private int MOVE_HORIZONTAL = 2;
	/**
	 * Signal that current dragged platform is vertical.
	*/
	private int MOVE_VERTICAL = 3;
	/**
	 * Milliseconds in one second.
	*/
	private int SECOND = 1000;
	/**
	 * Count of levels in main menu in one row.
	*/
	private int COLUMS = 2;
	/**
	 * Distance between buttons in main menu.
	*/
	private int DISTANCE = 200;
	/**
	 * Height of menu bar.
	*/
	private double MENU_HEIGHT = 25;
	/**
	 * Height of scene.
	*/
	private double SCENE_HEIGHT = 600;
	/**
	 * Width of scene.
	*/
	private double SCENE_WIDTH = 800;
	/**
	 * Width of scene in stage with information.
	*/
	private double INFO_WIDTH = 200;
	/**
	 * Signal that information is tab of scores.
	*/
	private int TAB = 0;
	/**
	 * Signal that information is rules of game.
	*/
	private int ABOUT = 1;
	/**
	 * Signal that information is help information.
	*/
	private int HELP = 2;
	/**
	 * Height of confirmition window.
	*/
	private double WINDOW_HEIGHT = 200;
	/**
	 * Height of title of window.
	*/
	private double TITLE_HEIGHT = 35;
	/**
	 * Width of outline.
	*/
	private double OUTLINE_WIDTH = 15;
	/**
	 * Width of confirmation window.
	*/
	private double WINDOW_WIDTH = 300;
	/**
	 * X position of information text.
	*/
	private double TEXT_POSITION_X = 600;
	/**
	 * Text of made steps in currents level.
	*/
	private Text stepsValue = null;
	/**
	 * Text of time in current level.
	*/
	private Text timeValue = null;
	/**
	 * Timer for getting next time in current level.
	*/
	private Timer timer = new Timer();
	/**
	 * Menu bar.
	*/
	private MenuBar menuBar = null;
	/**
	 * Buttons for choosing levels in main menu.
	*/
	private List<Button> levels = null;
	/**
	 * Group that contains attributes of current level.
	*/
	private Group game = null;
	/**
	 * Group that contains attributes of main menu.
	*/
	private Group mainMenu = null;
	/**
	 * Group for information about all levels.
	*/
	private Group levelsInfo = null;
	/**
	 * Object for showing information about game.
	*/
	private Information infoWindow = null;
	/**
	 * Main window of game.
	*/
	private Stage stage;
	/**
	 * Button "Reset scores" in menu bar. Is visible in main menu.
	*/
	private MenuItem reset = null;
	/**
	 * Button "Restart" in menu bar. Is visible in current level.
	*/
	private MenuItem restart = null;
	/**
	 * Menu in menu bar for game's instructions.
	*/
	private Menu gameMenu = null;
	/**
	 * Flag that cursor is shifted.
	*/
	private boolean isShifted = false;
}