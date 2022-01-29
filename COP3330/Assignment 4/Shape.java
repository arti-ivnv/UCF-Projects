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
 * @author Artem Ivanov
 */
public abstract class Shape {

    protected Color mColor;
    String mName;
    protected int mX;
    protected int mY;

    public Shape (Color color, String name){
        this.mColor = color;
        this.mName = name;
    }

    public String getName(){
        return (this.mName);
    }

    public Color getColor(){
        return (this.mColor);
    }

    public void setName(String name){
        this.mName = name;
    }

    public void setColor(Color color){
        this.mColor = color;
    }

    public abstract void print();
    public abstract void paint(Graphics g);

    public void setPos(int x, int y){
        mX = x;
        mY = y;
    }

}
