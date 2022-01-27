using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FirstCSOop
{
    class LargeCraft : IUFO
    {
        string color = "Blue";
        int size = 20;

        public string Color
        {
            get { return color; }
            set { color = value; }
        }

        public int Size
        {
            get { return size; }
            set { size = value; }
        }

        public void fly()
        {
            Console.WriteLine("LargeCraft flies");
        }

        public void goToHyperSpace()
        {
            Console.WriteLine("LargCraft goes to hyper space");
        }

        public void land()
        {
            Console.WriteLine("LargCraft lands");
        }
    }
}
