using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Homework1
{
    public class Problem1
    {
        public static IEnumerable<int> myFilter(IEnumerable<int> input)
        {
            IEnumerable<int> covid19;

            covid19 = input.Where(x => (x % 5 != 0 && x > 50)).Select(x => x * x * x).Where(x => x % 2 != 0);

            return covid19;
        }
    }
    /*
    class Pogram1
    {
        static void Main(string[] args)
        {
            Random rnd = new Random(5); // Important to seed with 5 for repeatability.

            var listForProblem = Enumerable.Range(1, 100).Select(i => rnd.Next() % 101);
            var answer = Problem1.myFilter(listForProblem);

            foreach (int i in answer)
            {
                Console.WriteLine(i);
            }

            Console.WriteLine("Press enter to close...");
            Console.ReadLine();
        }
    }
    */
}
