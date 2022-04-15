import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
 
public class FXML extends Application {
    
    @Override
    public void start(Stage primaryStage) throws Exception {
        FXMLLoader loader = new FXMLLoader();
	loader.setController(new MainSceneController());
	loader.setLocation(getClass().getResource("/mainScene.fxml"));
	Parent root = loader.load();

	primaryStage.setScene(new Scene(root));
	primaryStage.show();
    }
 public static void main(String[] args) {
        launch(args);
    }
}