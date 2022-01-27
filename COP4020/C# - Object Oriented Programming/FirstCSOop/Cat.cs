using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FirstCSOop
{
    class Cat : Animal
    {
        public void sing()
        {
            Console.WriteLine("Meow meow meow");
        }

        public void wash()
        {
            Console.WriteLine("Lick lick lick like cat");
        }

        public void turnAround()
        {
            Console.WriteLine("*Cat turns around*");
        }
    }
}
