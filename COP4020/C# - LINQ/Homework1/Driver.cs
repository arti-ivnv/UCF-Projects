using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Homework1
{
    class Driver
    {
        static void Main(string[] args)
        {
            Random rnd1 = new Random(5); // Important to seed with 5 for repeatability.
            var listForProblem = Enumerable.Range(1, 100).Select(i => rnd1.Next() % 101);
            var answer1 = Problem1.myFilter(listForProblem);

            Console.WriteLine("Problem 1: ");

            foreach (int i in answer1)
            {
                Console.WriteLine(i);
            }

            Console.WriteLine();

            Random rnd = new Random();

            var listForProblem2 = Enumerable.Range(1, 100).Select(i => rnd.Next() % 101);

            var answer2 = Problem2.myFilter(listForProblem2);

            Console.WriteLine("Problem 2: ");

            foreach (int i in answer2)

            {
                Console.WriteLine(i);

            }

            Console.WriteLine();

            var list1 = Enumerable.Range(1, 15);// Generate list here.
            var list2 = Enumerable.Range(2, 42).Where(x => (x % 2 == 0) && (x <= 42));// Generate list here.
            var list3 = Enumerable.Range(3, 21).Where(x => (x % 2 != 0) && (x <= 21));// Generate list here.
            var list4 = Enumerable.Range(5, 105).Where(x => (x % 5 == 0) && (x <= 105));// Generate list here.

            var answer3 = TestProblem2.merge(list1, list2, list3, list4);

            Console.WriteLine("Problem 3: ");

            foreach (int i in answer3)
            {
                Console.WriteLine(i);
            }

            Console.WriteLine();


            Console.WriteLine("Press any buttom to exit");
            Console.ReadLine();
        }
    }
}
