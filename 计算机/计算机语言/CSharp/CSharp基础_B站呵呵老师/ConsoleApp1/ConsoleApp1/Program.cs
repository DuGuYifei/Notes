using System;
using System.Collections.Generic;

namespace ConsoleApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            int aa = 0;
            List<int> b = new List<int>();
            b.Add(aa);
            aa = 5;
            Console.WriteLine(b[0]);
        }
    }
}
