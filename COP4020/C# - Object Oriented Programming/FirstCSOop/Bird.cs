using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FirstCSOop
{
    class Bird : Animal
    {
        public void sing()
        {
            Console.WriteLine("kurr kurr kurr");
        }

        public void wash()
        {
            Console.WriteLine("*Bird swims somewhere*");
        }

        public void turnAround()
        {
            Console.WriteLine("*Bird turns around*");
        }
    }
}
