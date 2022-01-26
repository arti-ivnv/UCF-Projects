/**
 * 
 *@author Artem Ivanov
 * 4131859
 * Assignment5
 * Program that is creating simulation of fish in a fish tank (with an extra fish model)
 **/

package assignment5_sharewithstudents;


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
import java.util.Calendar;
import java.util.Random;
import javax.swing.JPanel;
import javax.swing.JToggleButton;
import javax.swing.JToolBar;
import javax.swing.JFrame;
import java.util.Timer;
import java.util.TimerTask;
import javax.swing.border.EtchedBorder;

class GlobalVariables {
    public ArrayList<Fish> mFish;
    public FishTank mFishTank;

    private GlobalVariables() {
        mFish = new ArrayList<Fish>();
        mFishTank = new FishTank();
    }

    private static GlobalVariables instance;

    public static GlobalVariables getInstance() {
        if (instance == null){
            instance = new GlobalVariables();
        }
        return instance;
    }
}

class Fish implements Comparable<Fish>{
    
    int mX;
    int mY;
    int mId;
    Color mColor;
    
    public Fish(int id, int x, int y, Color color){
        
        mId = id;
        mX = x;
        mY = y;
        mColor = color;
    }
    
    
    public void paint(Graphics g){
        
        // Ths function draws a fish in three parts by polygons that creat triangle and by circle that creats body of the fish. After, we fill it by color. 
        
        int mX = this.mX;
        int mY = this.mY;
       
        
        //Bottom of the fish that created by polygones
        int[] bot_fish_x = {mX + 5, mX + 5, mX + 13};
        int[] bot_fish_y = {mY + 9, mY + 23, mY + 15};
        
        //Top part that created by drawing circle
        g.drawOval(mX+13, mY+11, 11 , 9);
        
        //Color for our model
        g.setColor(this.mColor);
        g.fillPolygon(bot_fish_x, bot_fish_y, 3);
        g.fillOval(mX+13, mY+11, 11 , 9);
    }
    
    public void move(){
         
        // Makes our fish move in random way
        
        
        Random rand = new Random();
        int randX = (rand.nextInt(3)-1)*30;
        int randY = (rand.nextInt(3)-1)*30;
        int newX = this.mX+randX;
        int newY = this.mY+randY;
        
        //we are making our borders
        if (newX < 0 || newY < 0 || newX > 570 || newY > 570) 
        {
            return;
        }
        for (Fish o : GlobalVariables.getInstance().mFish) 
        {
            if (o.mX == newX && o.mY == newY) 
            {
                return;
            }
        }
        this.mX = newX;
        this.mY = newY;
    }

    @Override
    public int compareTo(Fish o) //we are checking if the spot is clear or not, by comparing two objects of the list.
    {
        if (this.mId != o.mId) 
        {
            if (this.mX == o.mX && o.mY == this.mY) 
            {
            return 1;
            }
        }
        return 0;
    }
    
    
}


class FishTick extends TimerTask{

    @Override
    public void run() {
     
        if (FishTank.mSimulateStatus){
            
            for (int x=0;x<GlobalVariables.getInstance().mFish.size();x++){
                
                Fish f = GlobalVariables.getInstance().mFish.get(x);
                f.move();
                GlobalVariables.getInstance().mFish.set(x, f);
            }
              
            GlobalVariables.getInstance().mFishTank.mDrawPanel.paint();
        }
    }
}

public class FishTank extends javax.swing.JFrame implements java.awt.event.MouseListener, java.awt.event.MouseMotionListener{

    private final int mNumRows = 20;
    private final int mNumCols = 20;
    private final int mGridSz = 30;
    
    private int mSelectedFishIndex = -1;
    private boolean mDragged = false;
    
    private int mTopHeight;
           
    JToolBar mToolbar;
    JToggleButton mSimulationButton;
    DrawPanel mDrawPanel;
    
    private int mFishIndex = 0;
    
    static public boolean mSimulateStatus = false;
    
    public static void main(String[] args) {
 
        GlobalVariables global = GlobalVariables.getInstance();
        
        if (global == null){
            System.out.println("Cannot initialize, exiting ....");
            return;
        }
        
    }

    private JToggleButton addButton(String title){
        
        JToggleButton button = new JToggleButton(title);
        button.addItemListener(new ItemListener() {
           public void itemStateChanged(ItemEvent ev) {
               mSimulateStatus = !mSimulateStatus;
           }
        }); 
        
        this.mToolbar.add(button);
        
        return (button);
    }
    
    public FishTank()
    {  
        JFrame guiFrame = new JFrame();
 
        guiFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        guiFrame.setTitle("MY FISH TANK");
        
        // Create a toolbar and give it an etched border.
        this.mToolbar = new JToolBar();
        this.mToolbar.setBorder(new EtchedBorder());
        
        mSimulationButton = addButton("Simulate");
        this.mToolbar.add(mSimulationButton);
 
        //This will center the JFrame in the middle of the screen
        guiFrame.setLocationRelativeTo(null);
    
        this.mDrawPanel = new DrawPanel(mNumRows, mNumCols, mGridSz);
        
        this.mDrawPanel.setBackground(Color.cyan); 
        this.mDrawPanel.paint();
        
        guiFrame.add(mDrawPanel);
        guiFrame.add(this.mToolbar, BorderLayout.NORTH);
        
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
        guiFrame.addMouseMotionListener(this);
        
        //make sure the JFrame is visible
        guiFrame.setVisible(true);
        
        mTopHeight = guiFrame.getInsets().top + mToolbar.getHeight();
        guiFrame.setSize(mNumRows * mGridSz, mNumCols * mGridSz + mTopHeight);
        
        Timer timer = new Timer("tick", true);
        timer.scheduleAtFixedRate(new FishTick(), Calendar.getInstance().get(Calendar.MILLISECOND), 500);
    }
    

    
    @Override
    public void mouseClicked(MouseEvent e) {
        
        // Implement this function
         if (!this.mSimulateStatus) 
         {
            
            //mouse pointers
            int mx = e.getX() - 8;
            int my = e.getY() - 5;
            int x = (mx - (mx % this.mGridSz));
            int y = (my - (my % this.mGridSz)) - 60;
             
            //creating randomizer for our new color
            Random r = new Random();
            float red = r.nextFloat();
            float blue = r.nextFloat();
            float green = r.nextFloat();
            Color rgb = new Color (red,blue, green);
          
          
            //creating a new object
            int pointer = 0;
            Fish newFish = new Fish(this.mFishIndex++, x, y, rgb);
            GlobalVariables.getInstance().mFishTank.mDrawPanel.paint();
                
                //compare if the space is avaliable
                for (Fish o : GlobalVariables.getInstance().mFish) 
                {
                    if (newFish.compareTo(o) == 1) 
                    {
                        pointer = 1;
                        break;
                    }
                }
                
                if (pointer == 0)
                {
                    if (x <= 570&& y <= 570)
                    {
                        GlobalVariables.getInstance().mFish.add(newFish);
                    }
                }
        }
          
        repaint();
    }

    @Override
    public void mousePressed(MouseEvent e) {
    }

    @Override
    public void mouseReleased(MouseEvent e) {
         
         //basic release function that goes fron click anb grag.
         if (this.mDragged && this.mSelectedFishIndex != -1) 
         {
            Fish newFish = GlobalVariables.getInstance().mFish.get(this.mSelectedFishIndex);
            newFish.mX = e.getX() - (e.getX() % 30);
            newFish.mY = e.getY() - (e.getY() % 30) - 60;
            GlobalVariables.getInstance().mFishTank.mDrawPanel.paint();
        }
         
        this.mSelectedFishIndex = -1;
        this.mDragged = false;
    }

    @Override
    public void mouseEntered(MouseEvent e) {
    }

    @Override
    public void mouseExited(MouseEvent e) {
    }

    @Override
    public void mouseDragged(MouseEvent e) {
        //function that checks mouse pointer and makes mDragged = true for release
        if (!this.mSimulateStatus) 
        {
            this.mDragged = true;
            
            //mouse pointer
            int newX = ((e.getX() - 8) / 30) * 30;
            int newY = ((e.getY() - 8) / 30) * 30 - 60;
          
            for (Fish o : GlobalVariables.getInstance().mFish) 
            {
                if (o.mX == newX && o.mY == newY) 
                {
                    this.mSelectedFishIndex = GlobalVariables.getInstance().mFish.indexOf(o);
                    break;
                }
            }
        repaint();
        }
    }

    @Override
    public void mouseMoved(MouseEvent e) {
    }
}

class DrawPanel extends JPanel{

    int mRows;
    int mCols;
    int mGridSz;
    int maxGridSz;
    
    ArrayList<Fish> mFish;
    
    public DrawPanel(int numberOfRows, int numberOfCols, int gridSz){
        
        mGridSz = gridSz;
        mRows = numberOfRows;
        mCols = numberOfCols;
        maxGridSz = mGridSz * mRows;
    }
    
    private void paintBackground(Graphics g){
        
        for (int i = 1; i < mRows; i++) { 
            g.drawLine(i * mGridSz, 0, i * mGridSz, maxGridSz); 
        }
        
        for (int mAnimateStatus = 1; mAnimateStatus < mCols; mAnimateStatus++) { 
            g.drawLine(0, mAnimateStatus * mGridSz, maxGridSz, mAnimateStatus * mGridSz); 
        }
    }
    
    @Override
    public void paintComponent(Graphics g){
        
        super.paintComponent(g);
        
        paintBackground(g);
        
        for (Fish f:GlobalVariables.getInstance().mFish){  
            f.paint(g);
        }
        
    }

    public void paint(){ 
        repaint();
    }
}