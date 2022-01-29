/*
 * @author Artem Ivanov
 * Assignment8
 * Program is doing:
    Application that works with list. Adding numbers from 1 to 5 and also doing sorting.
 */

package listapp.java;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class ListApp extends Application
{
    @Override
    public void start(Stage primaryStage)
    {
        // Set resizable
        primaryStage.setResizable(false);

        // Set size as the size of the scene
        primaryStage.sizeToScene();

        // Center frame to screen
        primaryStage.centerOnScreen();

        // Create SpinningWheelPane
        ListPane pane = new ListPane();

        // Create a scene
        Scene scene = new Scene(pane, 450, 138);

        // Add scene to stage
        primaryStage.setScene(scene);

        // Show stage
        primaryStage.show();
    }

    public static void main(String[] args)
    {
          launch(args);
    }
}
