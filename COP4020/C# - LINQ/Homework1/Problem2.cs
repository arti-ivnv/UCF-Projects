using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Homework1
{
    public class Problem2 
    {
        public static IEnumerable<int> myFilter(IEnumerable<int> input)
        {
            IEnumerable<int> lol;

            lol = input.Where(x => (x % 6 != 0 && x < 42)).Select(x => x * x).Where(x => x % 2 == 0);

            return lol;
        }
    }
}
