/**
 * @author Artem Ivanov
 * 4131859
 * Assignment6
 * Character Histogram is showing character statistics according to the input string of information. Also, there are two types of output such as Pie Chart and Bar Chart. 
 */


package assignment6;

import java.net.URL;
import java.util.Arrays;
import java.util.Optional;
import java.util.ResourceBundle;
import javafx.application.Platform;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.chart.BarChart;
import javafx.scene.chart.PieChart;
import javafx.scene.chart.XYChart;
import javafx.scene.chart.XYChart.Series;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonBar.ButtonData;
import javafx.scene.control.ButtonType;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Dialog;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;

enum ChartType{barChart, pieChart};
/**
 *
 * @author neslisah
 */
public class FXMLDocumentController implements Initializable {
    
    
    final int TOTAL_CHARS = 26;  
    ChartType mChartType;
    int mChars[];
    
    @FXML
    private Button mButtonClose;
    
    @FXML
    private PieChart mPieChart;
    
    @FXML
    private BarChart mBarChart;
    
    @FXML
    private ComboBox mComboBox = new ComboBox();
   
    @FXML
    private void didClickCloseButton(ActionEvent event){
        Stage stage = (Stage) mButtonClose.getScene().getWindow();
        stage.close();
    }
    
    private String showInputDialog(){
        Dialog<String> dialog = new Dialog<>();
        dialog.setTitle("Input your text");

        ButtonType okButton = new ButtonType("OK", ButtonData.OK_DONE);
        dialog.getDialogPane().getButtonTypes().addAll(okButton, ButtonType.CANCEL);

        GridPane gridPane = new GridPane();
        gridPane.setHgap(10);
        gridPane.setVgap(10);
        
        TextField inputText = new TextField();
        inputText.setPromptText("Input Text");
    
        gridPane.add(inputText, 0, 0);
    
        dialog.getDialogPane().setContent(gridPane);

        Platform.runLater(()->inputText.requestFocus());

        dialog.setResultConverter((ButtonType dialogButton) -> {
            if (dialogButton == okButton) {
                return (inputText.getText());
            }
            return (null);
        });
        
        Optional<String> result = dialog.showAndWait();

        return (result.get());
    }
    
    private void paint(){
        
        XYChart.Series data = new XYChart.Series();
        mBarChart.getData().remove(0, mBarChart.getData().size());//refreshing either Bar Chart
        
        //adding each item and its occurance (for instance 'a', 2) (For Bar Chart)
        data.getData().add(new XYChart.Data("a",mChars[0]));
        data.getData().add(new XYChart.Data("b",mChars[1]));
        data.getData().add(new XYChart.Data("c",mChars[2]));
        data.getData().add(new XYChart.Data("d",mChars[3]));
        data.getData().add(new XYChart.Data("e",mChars[4]));
        data.getData().add(new XYChart.Data("f",mChars[5]));
        data.getData().add(new XYChart.Data("g",mChars[6]));
        data.getData().add(new XYChart.Data("h",mChars[7]));
        data.getData().add(new XYChart.Data("i",mChars[8]));
        data.getData().add(new XYChart.Data("j",mChars[9]));
        data.getData().add(new XYChart.Data("k",mChars[10]));
        data.getData().add(new XYChart.Data("l",mChars[11]));
        data.getData().add(new XYChart.Data("m",mChars[12]));
        data.getData().add(new XYChart.Data("n",mChars[13]));
        data.getData().add(new XYChart.Data("o",mChars[14]));
        data.getData().add(new XYChart.Data("p",mChars[15]));
        data.getData().add(new XYChart.Data("q",mChars[16]));
        data.getData().add(new XYChart.Data("r",mChars[17]));
        data.getData().add(new XYChart.Data("s",mChars[18]));
        data.getData().add(new XYChart.Data("t",mChars[19]));
        data.getData().add(new XYChart.Data("u",mChars[20]));
        data.getData().add(new XYChart.Data("v",mChars[21]));
        data.getData().add(new XYChart.Data("w",mChars[22]));
        data.getData().add(new XYChart.Data("x",mChars[23]));
        data.getData().add(new XYChart.Data("y",mChars[24]));
        data.getData().add(new XYChart.Data("z",mChars[25]));
        
        mPieChart.getData().remove(0, mPieChart.getData().size());//refreshing either Pie Chart
        
        //adding each item and its occurance (for instance 'a', 2) (For Pie Chart)
        mPieChart.getData().add(new PieChart.Data("a", mChars[0]));
        mPieChart.getData().add(new PieChart.Data("b", mChars[1]));
        mPieChart.getData().add(new PieChart.Data("c", mChars[2]));
        mPieChart.getData().add(new PieChart.Data("d", mChars[3]));
        mPieChart.getData().add(new PieChart.Data("e", mChars[4]));
        mPieChart.getData().add(new PieChart.Data("f", mChars[5]));
        mPieChart.getData().add(new PieChart.Data("g", mChars[6]));
        mPieChart.getData().add(new PieChart.Data("h", mChars[7]));
        mPieChart.getData().add(new PieChart.Data("i", mChars[8]));
        mPieChart.getData().add(new PieChart.Data("j", mChars[9]));
        mPieChart.getData().add(new PieChart.Data("k", mChars[10]));
        mPieChart.getData().add(new PieChart.Data("l", mChars[11]));
        mPieChart.getData().add(new PieChart.Data("m", mChars[12]));
        mPieChart.getData().add(new PieChart.Data("n", mChars[13]));
        mPieChart.getData().add(new PieChart.Data("o", mChars[14]));
        mPieChart.getData().add(new PieChart.Data("p", mChars[15]));
        mPieChart.getData().add(new PieChart.Data("q", mChars[16]));
        mPieChart.getData().add(new PieChart.Data("r", mChars[17]));
        mPieChart.getData().add(new PieChart.Data("s", mChars[18]));
        mPieChart.getData().add(new PieChart.Data("t", mChars[19]));
        mPieChart.getData().add(new PieChart.Data("u", mChars[20]));
        mPieChart.getData().add(new PieChart.Data("v", mChars[21]));
        mPieChart.getData().add(new PieChart.Data("w", mChars[22]));
        mPieChart.getData().add(new PieChart.Data("x", mChars[23]));
        mPieChart.getData().add(new PieChart.Data("y", mChars[24]));
        mPieChart.getData().add(new PieChart.Data("z", mChars[25]));

        mBarChart.getData().add(data);
    }
    
    @FXML
    private void didClickInputButton(ActionEvent event) {
        
        Arrays.fill(mChars, 0);
            
        String s = showInputDialog();
        
        if ((s!= null) && (s.trim().length() > 0)){
            
            s = s.toLowerCase();
            
            for (int i=0;i<s.length();i++){
                
                Character ch = s.charAt(i);
                
                if (Character.isAlphabetic(ch)){
                    
                    int index = ch - 'a';
                    mChars[index]++;
                }
            }
            
        }
        
        paint();
    }
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        mChars = new int[TOTAL_CHARS];//initializing mChart array
        mPieChart.setVisible(false);//making mPieChart hidden
        mChartType = ChartType.barChart;//setting mChartType to barChart
        mComboBox.getItems().addAll("Pie Chart","Bar Chart");//adding "BarChart" and "PieChart" to the comboBox
        mComboBox.getSelectionModel().select("Bar Chart");//setting selected item "BarChart" in the combobox 
        mComboBox.valueProperty().addListener(new ChangeListener()//adding ChangeListener to ComboBox, and implementing changed event 
                {
            @Override
            public void changed(ObservableValue observable, Object oldValue, Object newValue) //In the changed event updating the mChartType according to newValue
            {
                //update the visibility of the charts accordingly
                if (newValue == "Bar Chart")
                {
                    mChartType = ChartType.barChart;
                    mBarChart.setVisible(true);
                    mPieChart.setVisible(false);
                }
                else 
                {
                  mChartType = ChartType.pieChart;
                    mPieChart.setVisible(true);
                    mBarChart.setVisible(false);  
                }
            }
                });
        
        paint();//call the paint
                    
    }
    
}