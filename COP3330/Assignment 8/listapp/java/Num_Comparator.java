/*
 * @author Artem Ivanov
 * Assignment8
 * Program is doing:
    Application that works with list. Adding numbers from 1 to 5 and also doing sorting.
 */

package listapp.java;


import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.Comparator;

public class Num_Comparator implements Comparator<Number>
{
    @Override
    public int compare(Number num1, Number num2)
    {
        if (num1 instanceof Short && num2 instanceof Short)
        {
           return ((Short) num1).compareTo((Short) num2);
        }
        else if (num1 instanceof Long && num2 instanceof Long)
        {
           return ((Long) num1).compareTo((Long) num2);
        }
        else if (num1 instanceof Integer && num2 instanceof Integer)
        {
           return ((Integer) num1).compareTo((Integer) num2);
        }
        else if (num1 instanceof Float && num2 instanceof Float)
        {
           return ((Float) num1).compareTo((Float) num2);
        }
        else if (num1 instanceof Double && num2 instanceof Double)
        {
           return ((Double) num1).compareTo((Double) num2);
        }
        else if (num1 instanceof Byte && num2 instanceof Byte)
        {
           return ((Byte) num1).compareTo((Byte) num2);
        }
        else if (num1 instanceof BigInteger && num2 instanceof BigInteger)
        {
           return ((BigInteger) num1).compareTo((BigInteger) num2);
        }
        else if (num1 instanceof BigDecimal && num2 instanceof BigDecimal)
        {
           return ((BigDecimal) num1).compareTo((BigDecimal) num2);
        }
        else
        {
           throw new RuntimeException("Not implemented");
        }
    }
}
