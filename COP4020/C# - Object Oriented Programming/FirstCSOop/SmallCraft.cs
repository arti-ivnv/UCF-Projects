using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FirstCSOop
{
    class SmallCraft : IUFO
    {
        string color = "Red";
        int size = 10;

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
            Console.WriteLine("SmallCraft flies");
        }

        public void goToHyperSpace()
        {
            Console.WriteLine("SmallCraft goes to hyper space");
        }

        public void land()
        {
            Console.WriteLine("SmallCraft lands");
        }
    }
}
