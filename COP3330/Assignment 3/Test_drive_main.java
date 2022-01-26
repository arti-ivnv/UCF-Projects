
import java.awt.Color;

/**
 * 
 * @author Artem Ivanov
 * 4131859
 * Assignment3
 * Program that counts area and perimeter of the Square and Circle. Also, counting Volume of the Cube.
 */


public class Test_drive_main 
{

    public static void main(String[] args) {

        // TODO code application logic here

       

        Circle circle = new Circle(Color.RED, "myCircle", 2.f);

        circle.print();

        System.out.println("Area : "+circle.computeArea());

        System.out.println("Perimeter : "+circle.computePerimeter());

       

        Square square = new Square(Color.BLUE, "mySquare", 3.5f);

        square.print();

        System.out.println("Area : "+square.computeArea());

        System.out.println("Perimeter : "+square.computePerimeter());

       

        Cube cube = new Cube(Color.CYAN, "myCube", 2.3f);

        cube.print();

        System.out.println("Volume : "+cube.computeVolume());

    }
    
}
