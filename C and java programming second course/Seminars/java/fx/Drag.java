import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.shape.Circle;
import javafx.scene.shape.StrokeType;
import javafx.scene.effect.BoxBlur;
import javafx.scene.shape.Rectangle;
import javafx.scene.paint.LinearGradient;
import javafx.scene.paint.Stop;
import javafx.scene.paint.CycleMethod;
import javafx.scene.effect.BlendMode;
import static java.lang.Math.random;
import javafx.animation.Timeline;
import javafx.scene.Node;
import javafx.util.Duration;
import javafx.animation.KeyValue;
import javafx.animation.KeyFrame;
import javafx.event.*;
import javafx.scene.input.MouseEvent;
import javafx.scene.paint.Color;

public class Drag extends Application {
 
    @Override
    public void start(Stage primaryStage) {
        Group root = new Group();

        Scene scene = new Scene(root, 800, 600, Color.BLACK);
        primaryStage.setScene(scene);


	Rectangle colors = new Rectangle(100, 100, Color.AZURE);
		colors.setOnMouseDragged(new EventHandler<MouseEvent>() {
 
            @Override
            public void handle(MouseEvent event) {
                System.out.println("Hello World!");
            }
        });

	root.getChildren().add(colors);

        primaryStage.show();
    }
 
 public static void main(String[] args) {
        launch(args);
    }
}