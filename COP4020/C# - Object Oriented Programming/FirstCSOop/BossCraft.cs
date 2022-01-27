using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FirstCSOop
{
    class BossCraft : IUFO
    {
        string color = "Purple";
        int size = 30;

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
            Console.WriteLine("BossCraft flies");
        }

        public void goToHyperSpace()
        {
            Console.WriteLine("BossCraft goes to hyper space");
        }

        public void land()
        {
            Console.WriteLine("BossCraft lands");
        }
    }
}
