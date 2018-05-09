using System;
using System.Collections.Generic;
using System.ComponentModel;
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
    public partial class MainWindow : Window
    {
        bool isConnected = false;
        String[] ports;
        SerialPort port;

        public MainWindow()
        {
            InitializeComponent();

            Disable.IsEnabled = false; 
            SendMessageButton.IsEnabled = false;
            SendPicButton.IsEnabled = false;
            TestSnakeButton.IsEnabled = false;
            ColorPicker.IsEnabled = false;
            ModePicker.IsEnabled = false;
            MessageTextBox.IsEnabled = false;
            for (int i = 0; i < 100; i++)
            {
                var myTextBlock = (CheckBox)this.FindName("CheckBox"+i);
                myTextBlock.IsEnabled = false;
            }
        }
        
        private void Connect_Click(object sender, RoutedEventArgs e)
        {
            isConnected = true;
            string selectedPort = ComboBox.SelectedValue.ToString();

            MessageBox.Show(selectedPort);

            port = new SerialPort(selectedPort, 9600, Parity.None, 8, StopBits.One);
            port.Open();

            Connect.IsEnabled = false;
            Disable.IsEnabled = true;
            SendMessageButton.IsEnabled = true;
            SendPicButton.IsEnabled = true;
            TestSnakeButton.IsEnabled = true;
            ColorPicker.IsEnabled = true;
            ModePicker.IsEnabled = true;
            MessageTextBox.IsEnabled = true;
            for (int i = 0; i < 100; i++)
            {
                var myTextBlock = (CheckBox)this.FindName("CheckBox" + i);
                myTextBlock.IsEnabled = true;
            }
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
            Connect.IsEnabled = true; 
            Disable.IsEnabled = false;
            SendMessageButton.IsEnabled = false;
            SendPicButton.IsEnabled = false;
            TestSnakeButton.IsEnabled = false;
            ColorPicker.IsEnabled = false;
            ModePicker.IsEnabled = false;
            MessageTextBox.IsEnabled = false;

            port.Close();

        }

        private void SendPicButton_Click(object sender, RoutedEventArgs e)
        {
            string rColor = ColorPicker.SelectedColor.Value.R.ToString();
            string gColor = ColorPicker.SelectedColor.Value.G.ToString();
            string bColor = ColorPicker.SelectedColor.Value.B.ToString();
            while (rColor.Length != 3)
            {
                rColor = "0" + rColor;
            }
            while (gColor.Length != 3)
            {
                gColor = "0" + gColor;
            }
            while (bColor.Length != 3)
            {
                bColor = "0" + bColor;
            }
            string mode = ((ComboBoxItem)ModePicker.SelectedItem).Name;
            mode = mode[1].ToString();
            while (mode.Length != 2)
            {
                mode = "0" + mode;
            }
            string message = "";
            //for (int i = 0; i < 100; i++)
            //{
            //    var myTextBlock = (CheckBox)this.FindName("CheckBox" + i);
            //    if (myTextBlock.IsChecked == true) message = message + "1";
            //    else message = message + "0";
            //}
            int i = 0;
            while (i < 100)
            {
                int step = 1;
                int res = 0;
                for (int j = 0; j < 10; j++, i++)
                {
                    var myTextBlock = (CheckBox)this.FindName("CheckBox" + i);
                    if (myTextBlock.IsChecked == true)
                    {
                        res += step; 
                    }
                    step *= 2;
                }
                if (res < 10) message += "000";
                else if (res < 100) message += "00";
                else if (res < 1000) message += "0";
                message += res.ToString(); 
            }
            string command = "#UGLV" + rColor + gColor + bColor + mode + message + "a@";
            MessageBox.Show(command);
            port.Write(command);
        }

        private void SendMessageButton_Click(object sender, RoutedEventArgs e)
        {
            string message = MessageTextBox.Text;
            string rColor = ColorPicker.SelectedColor.Value.R.ToString();
            string gColor = ColorPicker.SelectedColor.Value.G.ToString();
            string bColor = ColorPicker.SelectedColor.Value.B.ToString();
            while (rColor.Length != 3)
            {
                rColor = "0" + rColor; 
            }
            while (gColor.Length != 3)
            {
                gColor = "0" + gColor;
            }
            while (bColor.Length != 3)
            {
                bColor = "0" + bColor;
            }
            //string mode = ((ComboBoxItem)ModePicker.SelectedItem).Content.ToString();
            string mode = ((ComboBoxItem) ModePicker.SelectedItem).Name;
            mode = mode[1].ToString();
            if (mode == "3" || mode == "4")
            {
                MessageBox.Show("Mode 3,4 is't enable for text message");
                return;
            }
            while (mode.Length != 2)
            {
                mode = "0" + mode;
            }
            string command = "#TEXT" + rColor + gColor + bColor + mode + message + "a@";
            MessageBox.Show(command);
            port.Write(command);
        }

        private void TestSnake_Click(object sender, RoutedEventArgs e)
        {
            string rColor = ColorPicker.SelectedColor.Value.R.ToString();
            string gColor = ColorPicker.SelectedColor.Value.G.ToString();
            string bColor = ColorPicker.SelectedColor.Value.B.ToString();
            string command = "#SNAK" + rColor + gColor + bColor + "a@";
            port.Write(command);
        }

        private void LedShowButton_Click(object sender, RoutedEventArgs e)
        {
            string command = "#LDSH" + "a@";
            port.Write(command);
        }

        private void MainWindow_Closed(object sender, EventArgs e)
        {
            port.Close();
        }

        private void ModePicker_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox comboBox = (ComboBox)sender;
            ComboBoxItem selectedItem = (ComboBoxItem)comboBox.SelectedItem;
            if (selectedItem.Content == null) return; 
            MessageBox.Show(selectedItem.Name.ToString());
        }
    }
}
