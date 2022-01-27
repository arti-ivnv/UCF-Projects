using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FirstCSOop
{
    class Dog : Animal
    {
        public void sing()
        {
            Console.WriteLine("Bork bork bork");
        }

        public void wash()
        {
            Console.WriteLine("Lick lick lick like doggo");
        }

        public void turnAround()
        {
            Console.WriteLine("*Dog turns around*");
        }
    }
}
