using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Homework1
{
    public class TestProblem2
    {
       public static IEnumerable<int> merge(IEnumerable<int> input1, IEnumerable<int> input2, IEnumerable<int> input3, IEnumerable<int> input4)
        {

            IEnumerable<int> foo;
            IEnumerable<int> foo1;
            IEnumerable<int> foo2;
            IEnumerable<int> foo3;
            IEnumerable<int> foo4;

            foo1 = input1.Where(x => x % 10 == 0);
            foo2 = input2.Where(x => x % 10 == 0);
            foo3 = input3.Where(x => x % 10 == 0);
            foo4 = input4.Where(x => x % 10 == 0);

            foo = foo1.Intersect(foo2).Intersect(foo3).Intersect(foo4);
           
            return foo;
        }
    }
}
