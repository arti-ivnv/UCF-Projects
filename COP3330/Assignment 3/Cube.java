/**
 * 
 * @author Artem Ivanov
 * 4131859
 * Assignment3
 * Program that counts area and perimeter of the Square and Circle. Also, counting Volume of the Cube.
 */

import java.awt.Color;

public class Cube extends Square implements I_threeD
{
    //using Squuare class to connect Shape super class to get info about the Cube
    public Cube (Color mColor, String mName, float mSide)
    {
     super(mColor, mName, mSide);   
    }

    //implementation between Cube class and I_theeD interface that is counting the Volume of the Cube.
    @Override
    public float computeVolume() 
    {
       return (float) Math.pow(mSide, 3); 
    }
    
     //Using Square class to communicate with the super class Shape to output cube results. 
    @Override
    public void print()
    {
        System.out.println("Cube ("+getName()+") side"+getSide()+"and color :"+getColor());
    }
    
    
}