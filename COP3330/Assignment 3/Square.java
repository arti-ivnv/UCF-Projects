/**
 * 
 * @author Artem Ivanov
 * 4131859
 * Assignment3
 * Program that counts area and perimeter of the Square and Circle. Also, counting Volume of the Cube.
 */


import java.awt.Color;

public class Square extends Shape implements I_twoD 
{
    public float mSide;
    
    public Square (Color mColor, String mName, float mSide)
    {
         //Calling the shape construction with the arguments
        super (mColor, mName);
        this.mSide = mSide;
    }

    //implementation between circle class and I_twoD interface that is counting the Area of the Square.
    @Override
    public float computeArea() 
    {
       return (float) Math.pow(mSide, 2);
       
    }
    
    //implementation between circle class and I_twoD interface that is counting the Area of the Square.
    @Override
    public float computePerimeter() 
    {
        return mSide*4;
    }
    
    public float getSide()
    {
        return mSide;
    }
    
    public void setSide (float mSide)
    {
        this.mSide = mSide;
    }
    
    //Using the super class Shape to output the square results.
    @Override
    public void print() 
    {
        System.out.println("Square ("+getName()+") side"+getSide()+"and color:"+getColor());
    }
    
}
