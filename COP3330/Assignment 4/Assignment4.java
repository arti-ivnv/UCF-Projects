/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ShareWithStudents;

//Imports are listed in full to show what's being used
//could just import javax.swing.* and java.awt.* etc..
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import javax.swing.JPanel;
import javax.swing.JToggleButton;
import javax.swing.JToolBar;
import javax.swing.JFrame;
import javax.swing.border.EtchedBorder;

enum ShapeSelected{
    None, Circle, Square, Cube, Filled;
};

public class Assignment4 extends javax.swing.JFrame implements java.awt.event.MouseListener{
 
    final int NUMBER_OF_SHAPES = 4;
    JToolBar mToolbar;
    ShapeSelected mSelectedAction;
    JToggleButton mCircleButton;
    JToggleButton mCubeButton;
    JToggleButton mSquareButton;
    JToggleButton mFillButton;
    DrawPanel mDrawPanel;
    
    static ArrayList<Shape> mShapes = new ArrayList<>();
  
    public static void main(String[] args) {
 
       new Assignment4();
    }
    private Object ShapeSelecteed;

    private JToggleButton addButton(String title, ShapeSelected shapeSelected){
        
        JToggleButton button = new JToggleButton(title);
        button.addItemListener(new ItemListener() {
           public void itemStateChanged(ItemEvent ev) {
               if(ev.getStateChange()==ItemEvent.SELECTED){
                   
                   // First if there is a button previously selected, reset it
                   switch (mSelectedAction){
                       case Circle:
                           mCircleButton.setSelected(false);
                           break;
                       case Cube:
                           mCubeButton.setSelected(false);
                           break;
                       case Square:
                           mSquareButton.setSelected(false);
                           break;
                       case Filled:
                           mFillButton.setSelected(false);
                           break;
                       
                   }
                   
                   // Update the selected button shape
                   mSelectedAction = shapeSelected;
                   
                } else if(ev.getStateChange()==ItemEvent.DESELECTED){
                   mSelectedAction = ShapeSelected.None;
                }
            }
        }); 
        
        this.mToolbar.add(button);
        
        return (button);
    }
    
    public Assignment4()
    {
        
        final int WIDTH = 1000;
        final int HEIGHT = 800;
        
        this.mSelectedAction = ShapeSelected.None;
        
        JFrame guiFrame = new JFrame();
 
            //make sure the program exits when the frame closes
        guiFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        guiFrame.setTitle("SHAPE GUI");
        guiFrame.setSize(WIDTH, HEIGHT);
 
        //This will center the JFrame in the middle of the screen
        guiFrame.setLocationRelativeTo(null);
    
        // Create a toolbar and give it an etched border.
        this.mToolbar = new JToolBar();
        this.mToolbar.setBorder(new EtchedBorder());
        
        this.mDrawPanel = new DrawPanel();
        
        this.mDrawPanel.setBackground(Color.blue); 
        this.mDrawPanel.paintDisplay(this.mShapes);
        
        guiFrame.add(mDrawPanel);
        guiFrame.add(this.mToolbar, BorderLayout.NORTH);
        
        this.mCircleButton = addButton("Circle", ShapeSelected.Circle);
        this.mCubeButton = addButton("Cube", ShapeSelected.Cube);
        this.mSquareButton = addButton("Square", ShapeSelected.Square);
        this.mFillButton = addButton("Filled Cube", ShapeSelected.Cube);
        
        // Add the Exit Action
        JButton button = new JButton("Quit");
        button.setToolTipText("Quit the program");
        button.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
            System.exit(0);
        }
        });
        mToolbar.add(button);
      
        guiFrame.addMouseListener(this);
        
        //make sure the JFrame is visible
        guiFrame.setVisible(true);
 }

    @Override
    public void mouseClicked(MouseEvent e) {
        
        int x = e.getX();    
	int y = e.getY();
        
        switch(this.mSelectedAction){
            case Circle:
                Circle circle = new Circle(Color.yellow, "crl", 50);
                circle.setPos(x, y - 50);
                mShapes.add(circle);
                break;
            case Cube:
                Cube cube = new Cube(Color.red, "cb", 100);
                cube.setPos(x, y - 50);
                mShapes.add(cube);
                break;
            case Square:
                Square square = new Square(Color.green, "sq", 100);
                square.setPos(x, y - 50);
                mShapes.add(square);
                break;
                 
                
        }
    
        this.mDrawPanel.paintDisplay(mShapes);
        
    }

    @Override
    public void mousePressed(MouseEvent e) {
    }

    @Override
    public void mouseReleased(MouseEvent e) {
    }

    @Override
    public void mouseEntered(MouseEvent e) {
    }

    @Override
    public void mouseExited(MouseEvent e) {
    }
 
}

class DrawPanel extends JPanel{

    ArrayList<Shape> mShapes;
    
    @Override
    public void paintComponent(Graphics g){
        
        super.paintComponent(g);
        
        for (Shape s : mShapes){
            s.paint(g);
        }
    }

    public void paintDisplay(ArrayList<Shape> shapes){
        mShapes = shapes;
        repaint();
    }

  
}