/*
 * @author Artem Ivanov
 * Assignment1
 * Program is doing:
    1)by pressing sum: factorial from 1 to 50 (final 1225) as a background proccess
    2)by pressig Add 1: adding one to the variable (i.e. 0,1,2,3,4,5...) possible to do during sum
    EXTRA! 3)by pressing Add 1 to sum: adding 1 to the current sum(even if sum runs) possible to do during sum
 */

package programming_assignment_7;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.application.Platform;
import javafx.concurrent.Service;
import javafx.concurrent.Task;
import javafx.concurrent.WorkerStateEvent;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;

/**
 *
 * @author Artem
 */
public class FXMLDocumentController implements Initializable {

//Creating Text field id
@FXML private TextField txt_sum;
private Service<Void> backgroundThread;

//Creating Text field id
@FXML private TextField txt_add;

//Creating Button id
@FXML private Button sum_bt;

//Creating Button id
@FXML private Button add_bt;

//Creating Text field id
@FXML private TextField txt_add_sum;

//Creating Button id
@FXML private Button add_sum_bt;

@Override
public void initialize(URL location, ResourceBundle resources)
{
}

    //function that allows us to add 1 to the sum during the process.
    @FXML
    void didClickAddOneSumButton(ActionEvent event)
    {
        txt_add_sum.setText((Integer.parseInt(txt_sum.getText())+1)+"");
    }


     //function that allows us to adding one to the variable(stats at 0) as much as we want, works separately from sum.
    @FXML
    void didClickAddOneButton(ActionEvent event)
    {
        txt_add.setText((Integer.parseInt(txt_add.getText())+1)+"");

    }

     //function that is counting and addind from 1 to 50.In other words, factorial of 50 (50!)
    @FXML
    void didClickSumButton(ActionEvent event)
    {
        sum_bt.setDisable(true);

        backgroundThread = new Service<Void>()
        {
            @Override
            protected Task<Void> createTask()
            {
               return new Task<Void>()
               {
                   @Override
                   protected Void call() throws Exception
                   {
                       int sum = 0;
                       for (int i = 0; i<50;i++)
                       {
                           Thread.sleep(220);//To change factorial speed, change number in the brakets.
                           sum+=i;
                           updateMessage(sum+"");
                       }
                       return null;
                   }
               };
            }
        };

        backgroundThread.setOnSucceeded(new EventHandler<WorkerStateEvent>()
        {
            @Override
            public void handle(WorkerStateEvent event)
            {
                System.out.println("Done");//self assist, that shows(in console) when summation is done.
                txt_sum.textProperty().unbind();
                sum_bt.setDisable(false);
            }
        });

        txt_sum.textProperty().bind(backgroundThread.messageProperty());
        backgroundThread.restart();
    }


}
