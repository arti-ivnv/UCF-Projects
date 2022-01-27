using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace multithread_program
{
    class MultithreadProgram
    {
        static int numThreads = 4;

        static Thread thrd;
        static Thread[] multiThrd = new Thread[numThreads];
        static int[] data = new int[10000000];

        static void calc(int startingIndex, int reps)
        {
            for (int i = startingIndex; i < startingIndex + reps; i++)
            {
                data[i] = (int)(Math.Atan(i) * Math.Acos(i) * Math.Cos(i) * Math.Sin(i));
            }
        }

        static void Main(string[] args)
        {
            thrd = new Thread(() => calc(0, data.Length));
            thrd.Start();
            DateTime dt = DateTime.Now;
            thrd.Join();
            TimeSpan ts = DateTime.Now - dt;

            int repsPerThreads = data.Length / multiThrd.Length;

            for (int i = 0; i < multiThrd.Length; i++)
            {
                int j = i;
                multiThrd[i] = new Thread(() => calc(j * repsPerThreads, repsPerThreads));
                multiThrd[i].Start();
            }

            DateTime dt2 = DateTime.Now;

            for (int i = 0; i < multiThrd.Length; i++)
            {
                multiThrd[i].Join();
            }

            TimeSpan ts2 = DateTime.Now - dt2;
            Console.WriteLine("Sequentially, calc takes: {0} milliseconds to run.", ts.TotalMilliseconds);
            Console.WriteLine("Multithreaded, calc takes {0} milliseconds to run.", ts2.TotalMilliseconds);

            Console.WriteLine();
            Console.WriteLine("Press Enter to continue...");
            Console.ReadLine();
            return;
        }
    }
}
