using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FirstCSOop
{
    interface IUFO
    {
        string Color { get; set; }
        int Size { get; set; }

        void fly();
        void goToHyperSpace();
        void land();

    }
}
