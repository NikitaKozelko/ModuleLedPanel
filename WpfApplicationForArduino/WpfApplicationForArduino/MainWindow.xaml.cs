using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WpfApplicationForArduino
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        bool isConnected = false;
        String[] ports;
        SerialPort port;

        public MainWindow()
        {
            InitializeComponent();
        }
        
        private void SendButton_Click(object sender, RoutedEventArgs e)
        {
            string message = MessageTextBox.Text;
            string rColor = RedColorTextBox.Text;
            string gColor = GreenColorTextBox.Text;
            string bColor = BlueColorTextBox.Text;
            string command = "#TEXT" + rColor + gColor + bColor + "01" + message + "\n";
            MessageBox.Show(command);
            port.Write(command);
        }

        private void Connect_Click(object sender, RoutedEventArgs e)
        {
            isConnected = true;
            string selectedPort = comboBox.SelectedValue.ToString();

            MessageBox.Show(selectedPort);

            port = new SerialPort(selectedPort, 9600, Parity.None, 8, StopBits.One);
            port.Open();
            //port.Write("#STAR\n");
            //button1.Text = "Disconnect";
            //enableControls();
        }

        private void Led1_Click(object sender, RoutedEventArgs e)
        {
            port.Write("#LED1\n");
        }

        private void Disable_Click(object sender, RoutedEventArgs e)
        {
            port.Close();
        }
    }
}
