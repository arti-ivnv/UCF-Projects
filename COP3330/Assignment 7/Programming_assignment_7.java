/*
 * @author Artem Ivanov
 * 4131859
 * Assignment1
 * Program is doing:
    1)by pressing sum: factorial from 1 to 50 (final 1225) as a background proccess
    2)by pressig Add 1: adding one to the variable (i.e. 0,1,2,3,4,5...) possible to do during sum
    EXTRA! 3)by pressing Add 1 to sum: adding 1 to the current sum(even if sum runs) possible to do during sum
 */
 
package programming_assignment_7;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

/**
 *
 * @author Artem
 */
public class Programming_assignment_7 extends Application {
    
    @Override
    public void start(Stage stage) throws Exception {
        Parent root = FXMLLoader.load(getClass().getResource("FXMLDocument.fxml"));
        
        Scene scene = new Scene(root);
        
        stage.setScene(scene);
        stage.show();
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }
    
}
