
/**
 *
 * @author Artem Ivanov
 * Program1
 * Program that prints different types of triangles
 */

public class Program1 {
    private final int HEIGHT = 11;

    public enum Patterns {
        bottomLeftTriangle,
        bottomRightTriangle,
        topLeftTriangle,
        topRightTriangle,
        centerTriangle
    };

    //Function to print a isosceles triangle.
    //For each level I subtracted i from height and multiplied by 2, and subtracted 1 because it needs to be odd nuber.
    void printCenter(char ch)
    {
        for(int i = HEIGHT - 1; i > 0; i--)
           {
            for(int j = 0; j < i; j++)
            {
                System.out.print(' ');
            }
            for(int j = 0; j < (HEIGHT - i)*2-1; j++)
            {
                System.out.print(ch);
            }
            System.out.println();
        }
    }

    //Function to pront a right triangle with corner on bottom left.
    //Base was the same as height.
    void printBottomLeft(char ch)
    {
        for(int i = 1; i <= HEIGHT; i++)
        {
            for(int j = 1; j <= i; j++)
            {
                System.out.print(ch);
            }
            System.out.println();
        }
    }

    //Function to pront a right triangle with corner on top left.
    //Base was the same as height.
    void printTopLeft(char ch)
    {
        for(int i = HEIGHT; i > 0; i--)
        {
            for(int j = 0; j < i; j++)
            {
                System.out.print(ch);
            }
            System.out.println();
        }
    }

    //Function to pront a right triangle with corner on bottom right.
    //Base was the same as height.
    //The first for loop prints out the spaces before the output.
    //The number of spaces is i.
    void printBottomRight(char ch)
    {
        for(int i = HEIGHT-1; i >= 0; i--)
        {
            for(int j = HEIGHT; j > HEIGHT - i; j--)
            {
                System.out.print(' ');
            }
            for(int j = HEIGHT - i; j > 0; j--)
            {
                System.out.print(ch);
            }
            System.out.println();
        }
    }

    //Function to pront a right triangle with corner on bottom right.
    //Base was the same as height.
    //The first for loop prints out the spaces before the output.
    //The number of spaces is i.
    //The outer of the for loop is opposite with the previous function.
    void printTopRight(char ch)
    {
        for(int i = 0; i < HEIGHT; i++)
        {
            for(int j = HEIGHT; j > HEIGHT - i; j--)
            {
                System.out.print(' ');
            }
            for(int j = HEIGHT - i; j > 0; j--)
            {
                System.out.print(ch);
            }
            System.out.println();
        }
    }

    public void printPattern(Patterns patternId, char ch) {
        switch(patternId) {
            case bottomLeftTriangle:
                this.printBottomLeft(ch);
                break;
            case bottomRightTriangle:
                this.printBottomRight(ch);
                break;
            case topLeftTriangle:
                this.printTopLeft(ch);
                break;
            case topRightTriangle:
                this.printTopRight(ch);
                break;
            case centerTriangle:
                this.printCenter(ch);
                break;
            default:
                this.printTopLeft(ch);
                break;
        }
    }

    public static void main(String[] args) {
        Program1 ass1 = new Program1();
        ass1.printPattern(Program1.Patterns.bottomLeftTriangle, '*');
        System.out.println();//A space between the outputs
        ass1.printPattern(Program1.Patterns.bottomRightTriangle, '#');
        System.out.println();//A space between the outputs
        ass1.printPattern(Program1.Patterns.topLeftTriangle, '@');
        System.out.println();//A space between the outputs
        ass1.printPattern(Program1.Patterns.topRightTriangle, '%');
        System.out.println();//A space between the outputs
        ass1.printPattern(Program1.Patterns.centerTriangle, '^');
    }
}
