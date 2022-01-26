/**
 * 
 * @author Artem Ivanov
 * 4131859
 * Assignment3
 * Program that counts area and perimeter of the Square and Circle. Also, counting Volume of the Cube.
 */


import java.awt.Color;



public class Circle extends Shape implements I_twoD
{
    //Variable declaration
    public float mRadius;
    
    
    public Circle (Color red, String mName, float mRadius)
    {
        //Calling the shape construction with the arguments
        super(red, mName);
        this.mRadius = mRadius;
    }
 
    public float getRadius()
    {
        return mRadius;
    }
   
    public void setRadiuce(float mRadius)
    {
        this.mRadius = mRadius;
    }
    
    //implementation between circle class and I_twoD interface that is counting the Area of the Circle.
    @Override
    public float computeArea() 
    {
        return (float) (Math.PI* Math.pow(mRadius,2));
    }
    
    //implementation between circle class and I_twoD interface that is counting the Perimetr of the Circle.
    @Override
    public float computePerimeter() 
    {
        return (float) ((float) 2*Math.PI*mRadius);
    }
    
    
    
     //Using the super class Shape to output the circle results. 
    @Override
    public void print() 
    {
        System.out.println("Circle ("+getName()+ ") side"+getRadius()+"and color :"+getColor());
    }
}