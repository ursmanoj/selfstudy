using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsFormsApp1
{
    class TestClass
    {
        public static void testBytes()
        {
            //testArray();
            testStr();
        }

        private static void testStr()
        {
            string text = "0/{\"type\":\"command\",\"name\":\"next1\"}\n12/{\"type\":\"command\",\"name\":\"next2\"}\n4/{\"type\":\"command\",\"name\":\"next3\"}\n";
            char[] sep = {'\n'};
            string[] jsons = text.Split(sep, StringSplitOptions.RemoveEmptyEntries);

            Console.WriteLine(jsons);
        }

        private static void testResponse()
        {
            string text = "{\"type\":\"command\",\"name\":\"next1\"}\n{\"type\":\"command\",\"name\":\"next2\"}\n{\"type\":\"command\",\"name\":\"next3\"}\n";
            char[] sep = { '\n' };
            string[] jsons = text.Split(sep, StringSplitOptions.RemoveEmptyEntries);

            Console.WriteLine(jsons);
        }

        private static void testArray()
        {
            byte[] bytes = Encoding.Default.GetBytes("My name is khan");

            Console.WriteLine(bytes.Length);
            byte[] buffer = new byte[bytes.Length];
            Array.Copy(bytes, buffer, 7);

            string txt = System.Text.Encoding.ASCII.GetString(buffer);

            Console.WriteLine("Trimmed buffer: " + txt);
        }
    }
}
