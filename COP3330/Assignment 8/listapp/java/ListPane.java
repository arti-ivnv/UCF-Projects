/*
 * @author Artem Ivanov
 * Assignment8
 * Program is doing:
    Application that works with list. Adding numbers from 1 to 5 and also doing sorting.
 */

package listapp.java;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.layout.Region;
import javafx.scene.layout.VBox;

public class ListPane extends VBox implements EventHandler<ActionEvent>
{
    private static final int NUM_BUTTONS = 5;
    private static final String OUTPUT_TEXT = "mHead -> %s";

    // Instance of variables
    private Integer[] num;
    private Button[] num_Button;
    private Label lab_Disp;
    private Button Reset;
    private Button Close;
    private GenLinkedList<Integer> numList;



    public ListPane()
    {
        this.num_Button = new Button[NUM_BUTTONS];
        this.num = new Integer[NUM_BUTTONS];
        this.numList = new GenLinkedList<Integer>();

        // VBox setting
        setPadding(new Insets(10, 10, 5, 10));
        setSpacing(20);

        //  Initialization buttons
        for (int i = 0; i < NUM_BUTTONS; i++)
        {
            this.num[i] = new Integer(i + 1);

            // Button creating
            this.num_Button[i] = new Button("" + (i + 1));
            this.num_Button[i].setOnAction(this);
            this.num_Button[i].setPrefSize(80, 30);
        }

        // Creating a button box
        NumButton_Box();

        // Creating a label box
        Label_Box();

        // Adding Reset and Close buttons
        Control_Button_Box();
    }


    // This function adding number buttons
    private void NumButton_Box()
    {
        HBox hBox = new HBox();

        // Adding a region to center align buttons
        Region region = new Region();
        HBox.setHgrow(region, Priority.ALWAYS);
        hBox.getChildren().add(region);

        // Adding number buttons to the hBox
        for (int i = 0; i < NUM_BUTTONS; i++)
            hBox.getChildren().add(this.num_Button[i]);

        // Adding a region to center align buttons
        Region region2 = new Region();
        HBox.setHgrow(region2, Priority.ALWAYS);
        hBox.getChildren().add(region2);

        // Adding hbox to vbox
        getChildren().add(hBox);
    }



    //This function is creating and adding display label
    private void Label_Box()
    {
        HBox hBox = new HBox();

        // Adding a region to center align label
        Region region = new Region();
        HBox.setHgrow(region, Priority.ALWAYS);
        hBox.getChildren().add(region);

        // Adding display label
        lab_Disp = new Label(String.format(OUTPUT_TEXT, ""));
        hBox.getChildren().add(lab_Disp);

        // Adding a region to center align label
        Region region2 = new Region();
        HBox.setHgrow(region2, Priority.ALWAYS);
        hBox.getChildren().add(region2);

        // Adding hbox to vbox
        getChildren().add(hBox);
    }




    //This function is adding Reset and Close buttons
    private void Control_Button_Box()
    {
        HBox hBox = new HBox();
        hBox.setSpacing(10);

        // Adding a region to left align buttons
        Region region = new Region();
        HBox.setHgrow(region, Priority.ALWAYS);
        hBox.getChildren().add(region);

        // Creating a Reset button
        Reset = new Button("Reset");
        Reset.setOnAction(this);

        // Adding a Reset button
        hBox.getChildren().add(Reset);

        // Creating a Close button
        Close = new Button("Close");
        Close.setOnAction(this);

        // Adding a Close button
        hBox.getChildren().add(Close);

        // Adding hbox to vbox
        getChildren().add(hBox);
    }


    //This function is updating the label text
    private void Label_Updating(String text)
    {
        this.lab_Disp.setText(String.format(OUTPUT_TEXT, text));
    }


    //This function will be working with our Reset button. It enables buttons and clears our list.
    private void Reset_function()
    {
        for (int i = 0; i < NUM_BUTTONS; i++)
            this.num_Button[i].setDisable(false);

        // Clearing our list
        this.numList.clearList();

        // Updating a label
        Label_Updating("");
    }


    // Handles button click function
    @Override
    public void handle(ActionEvent e)
    {
        Button btn = (Button) e.getSource();

        if (btn == Close) // If Close pressed
            System.exit(0);
        else if (btn == Reset) //If Reset pressed
            Reset_function();
        else
        {
            // Checking for number buttons
            for (int i = 0; i < NUM_BUTTONS; i++)
            {
                if (btn == this.num_Button[i])
                {
                    this.num_Button[i].setDisable(true);

                    // Add number to the list
                    this.numList.insertItem(this.num[i]);

                    break;
                }
            }

            // Updating display label
            Label_Updating(this.numList.printList());
        }
    }
}
