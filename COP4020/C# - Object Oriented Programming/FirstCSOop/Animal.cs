using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FirstCSOop
{
    class Animal
    {
        void move(string tp)
        {
            Console.WriteLine("*{0} moves*", tp);
        }

        void sleep(string tp)
        {
            Console.WriteLine("*{0} sleeps*", tp);
        }
        
        void eat(string tp)
        {
            Console.WriteLine("*{0} eats*", tp);
        }


        static void Main(string[] args)
        {
            Bird bd = new Bird();
            Cat ct = new Cat();
            Dog dg = new Dog();
            SmallCraft smc = new SmallCraft();
            LargeCraft lrc = new LargeCraft();
            BossCraft bsc = new BossCraft();

            bd.move("Bird");
            bd.sleep("Bird");
            bd.eat("Bird");
            bd.sing();
            bd.wash();
            bd.turnAround();

            Console.WriteLine();

            ct.move("Cat");
            ct.sleep("Cat");
            ct.eat("Cat");
            ct.sing();
            ct.wash();
            ct.turnAround();

            Console.WriteLine();

            dg.move("Dog");
            dg.sleep("Dog");
            dg.eat("Dog");
            dg.sing();
            dg.wash();
            dg.turnAround();

            Console.WriteLine();

            Console.WriteLine("The color of SmallCraft: " + smc.Color);
            Console.WriteLine("The size of SmallCraft: " + smc.Size);
            smc.fly();
            smc.goToHyperSpace();
            smc.land();

            Console.WriteLine();

            Console.WriteLine("The color of LargeCraft: " + lrc.Color);
            Console.WriteLine("The size of LargeCraft: " + lrc.Size);
            lrc.fly();
            lrc.goToHyperSpace();
            lrc.land();

            Console.WriteLine();

            Console.WriteLine("The color of BossCraft: " + bsc.Color);
            Console.WriteLine("The size of BossCraft: " + bsc.Size);
            bsc.fly();
            bsc.goToHyperSpace();
            bsc.land();

            Console.WriteLine();

        }
    }
}
