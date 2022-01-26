/**
 * 
 * @author Artem Ivanov
 * 4131859
 * Assignment3
 * Program that counts area and perimeter of the Square and Circle. Also, counting Volume of the Cube.
 */

import java.awt.Color;


public abstract class Shape 
{
    public Color mColor;
    public String mName;

//Shape constructor
    
public Shape(Color red, String mName)
{
    this.mColor = red;
    this.mName = mName;
}

public String getName ()
{
    return mName;
}

public Color getColor()
{
    return mColor;
}


public void setName (String mName)
{
    this.mName = mName;
}

public void setColor (Color mColor)
{
    this.mColor = mColor;
}


abstract public void print();

}