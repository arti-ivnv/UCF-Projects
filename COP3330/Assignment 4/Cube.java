/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ShareWithStudents;

import java.awt.Color;
import java.awt.Graphics;

/**
 *
 * @author neslisah
 */
public class Cube extends Square implements I_threeD{
    
    public boolean mFilled;

    public Cube(Color color, String name, int side) {
        super(color, name, side);
    }

    public float computeVolume() {
        
        return (this.mSide * this.mSide * this.mSide);
    }
    
    public void print(){
        System.out.println("Cube ("+this.mName+") side : "+this.mSide+" and color : "+this.mColor.toString());
    }
    
    public void paint(Graphics g) {
        
        if (mFilled)
        {
            g.setColor(mColor);
            g.fill3DRect(mX-55, mX-55, mY-20, mY-20, mFilled);
            g.setColor(Color.red);
            g.drawRect(mX - 60, mY - 60, mSide , mSide);
            g.drawRect(mX - 30, mY - 30, mSide , mSide);
            g.drawLine(mX-60, mY-60, mX-30, mY-30);
            g.drawLine(mX+40, mY-60, mX+70, mY-30);
            g.drawLine(mX-60, mY+40, mX-30, mY+70);
            g.drawLine(mX+40, mY+40, mX+70, mY+70);
        }
        else
        {
            g.drawRect(mX - 60, mY - 60, mSide , mSide);
            g.drawRect(mX - 30, mY - 30, mSide , mSide);
            g.drawLine(mX-60, mY-60, mX-30, mY-30);
            g.drawLine(mX+40, mY-60, mX+70, mY-30);
            g.drawLine(mX-60, mY+40, mX-30, mY+70);
            g.drawLine(mX+40, mY+40, mX+70, mY+70);
        }
        
        final int step = 20; 
    }

}
