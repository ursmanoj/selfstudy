using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            connectJSRDB();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
        

        private async void connectJSRDB()
        {
            //192.168.123.106 : 8089
            string host = "192.168.123.106";
            string port = "8089";
            IPAddress ip = IPAddress.Parse(host);

            Socket s = new Socket(AddressFamily.InterNetwork,
                SocketType.Stream,
                ProtocolType.Tcp);

            Console.WriteLine("Establishing Connection to {0}",
                host);
            s.Connect(ip, 8089);
            Console.WriteLine("Connection established");

            byte[] buffer = new byte[1000];

            s.Receive(buffer);

            txtBoxResponse.Text += "\n";
            txtBoxResponse.Text += System.Text.Encoding.ASCII.GetString(buffer);

            //JsonConvert;

        }
    }
}
