using System;

namespace HW2
{
    class Program
    {
        static void Main(string[] args)
        {
            //variables to calculate the areas

            //Menu components Triangle, Rectangle, Circle, Pentagon, Exit


            bool Exit = false;
            double Tbase, Theight; //Triangle variable
            double Rlength, Rwidth; //Rectangle
            double Pi = 3.14; double Radius; // Circle variables
            //float side;

            string triangle = "Triangle";
            string rectangle = "Rectangle";
            string circle = "Circle";
            string pentagon = "Pentagon";
            string exit = "Exit";
            string Echoice = "Enter your choice";

            while (!Exit) { 

                Console.WriteLine(triangle);
                Console.WriteLine(rectangle);
                Console.WriteLine(circle);
                Console.WriteLine(pentagon);
                Console.WriteLine(exit);
                Console.WriteLine("");
                Console.WriteLine(Echoice);
                Console.WriteLine("");


                string choice = Console.ReadLine();


                switch (choice)
                {
                    case "Triangle":
                        Console.WriteLine("Your choice is Triangle");
                        Console.WriteLine("Enter Base");
                        //CIN tbase
                        Tbase = Convert.ToDouble(Console.ReadLine());
                        Console.WriteLine("Enter Height");
                        //cin theight
                        Theight = Convert.ToDouble(Console.ReadLine());

                        //cout the area is... MAKE THIS A FUNCTION

                        double Tresult = (Tbase * Theight) / 2;
                        Console.WriteLine(String.Format("The area is: "));
                        Console.WriteLine(Tresult);
                        Console.WriteLine(" ");
                        break;

                    case "Rectangle":
                        Console.WriteLine("Your choice is Rectangle");
                        Console.WriteLine("Enter Lenght");
                        //cin
                        Rlength = Convert.ToDouble(Console.ReadLine());
                        Console.WriteLine("Enter Width");
                        //cin
                        Rwidth = Convert.ToDouble(Console.ReadLine());
                        //cout area is
                        Console.WriteLine(String.Format("The area is: "));
                        double Rresult = Rlength * Rwidth;
                        Console.WriteLine(Rresult);
                        Console.WriteLine(" ");
                        break;

                    case "Circle":
                        Console.WriteLine("Your choice is Circle");
                        Console.WriteLine("Enter Radius");
                        //cin
                        Radius = Convert.ToDouble(Console.ReadLine());
                        //cout the Area is
                        Console.WriteLine(String.Format("The area is: "));
                        double Cresult = Pi * (Radius*Radius);
                        Console.WriteLine(Cresult);
                        Console.WriteLine(" ");

                        break;

                    case "Pentagon":
                        Console.WriteLine("Your choice is Pentagon");
                        Console.WriteLine("Enter the side");
                        //cin
                        double side = Convert.ToDouble(Console.ReadLine());

                        Console.WriteLine(String.Format("The area is: "));
                        float Presult;

                       Presult = (float) (Math.Sqrt(5 * (5 + 2 * (Math.Sqrt(5)))) * side * side)/4;

                        Console.WriteLine(Presult);
                        Console.WriteLine(" ");
                        break;


                    case "Exit":
                        Console.WriteLine("See you soon!");
                        Exit = true;
                        break;
                }
            } 


           
        }
    }
}
