using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Printing;
using System.Linq;
using System.Net.NetworkInformation;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp4
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            
            string vardasPavarde = textBox1.Text;
            string pazymiaiString = textBox2.Text;
            string egzaminoBalasString = textBox3.Text;

           
            List<double> pazymiai = pazymiaiString.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries)
                .Where(s => !string.IsNullOrWhiteSpace(s)) 
                .Select(s => Double.Parse(s.Replace(',', '.'))) 
                .Where(s => s >= 1 && s <= 10) 
                .ToList();

            
            double egzaminoBalas;
            bool egzaminoBalasValid = Double.TryParse(egzaminoBalasString.Replace(',', '.'), out egzaminoBalas) && egzaminoBalas >= 1 && egzaminoBalas <= 10; 

            if (!egzaminoBalasValid || pazymiai.Count == 0)
            {
                MessageBox.Show("Neteisingi duomenys ivesti");
                return;
            }

            
            double rezultatas = 0;

            if (radioButton1.Checked) 
            {
                if (pazymiai.Count > 0)
                {
                    double suma = pazymiai.Sum();
                    rezultatas = (suma + egzaminoBalas) / (pazymiai.Count + 1);
                }
                else
                {
                    rezultatas = egzaminoBalas; 
                }
            }
            else if (radioButton2.Checked) 
            {
                List<double> pazymiaiKlonas = new List<double>(pazymiai);
                pazymiaiKlonas.Add(egzaminoBalas);
                pazymiaiKlonas.Sort();

                int vidurys = pazymiaiKlonas.Count / 2;
                if (pazymiaiKlonas.Count % 2 == 0)
                {
                    rezultatas = (pazymiaiKlonas[vidurys - 1] + pazymiaiKlonas[vidurys]) / 2;
                }
                else
                {
                    rezultatas = pazymiaiKlonas[vidurys];
                }
            }

            
            string visaInformacija = $"{vardasPavarde}\t {string.Join(" ", pazymiai)}\tEgzamino balas: {egzaminoBalas}\tRezultatas: {rezultatas.ToString("F6")}"; 

            
            listBox1.Items.Add(visaInformacija);
        }
        private void button2_Click(object sender, EventArgs e)
        {
           
            listBox1.Items.Clear();
        }


        private void button3_Click(object sender, EventArgs e)
        {
            
            foreach (object item in listBox1.Items)
            {
                textBox5.AppendText(item.ToString() + Environment.NewLine);
            }
        }
        


        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            
        }

        private void button4_Click_1(object sender, EventArgs e)
        {
            if (listBox1.SelectedItem != null)
            {
                
                textBox5.AppendText(listBox1.SelectedItem.ToString() + Environment.NewLine);
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
          
            textBox5.Clear();
        }

        private void button5_Click(object sender, EventArgs e)
        {
          
            OpenFileDialog openFileDialog = new OpenFileDialog();

          
            openFileDialog.Filter = "Text Files (*.txt)|*.txt|All Files (*.*)|*.*";

           
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                try
                {
                  
                    string fileContent = System.IO.File.ReadAllText(openFileDialog.FileName);

                  
                    textBox5.Text = fileContent;
                }
                catch (Exception ex)
                {
                    
                    MessageBox.Show($"Klaida: {ex.Message}");
                }
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            
            SaveFileDialog saveFileDialog = new SaveFileDialog();

           
            saveFileDialog.Filter = "Text Files (*.txt)|*.txt|All Files (*.*)|*.*";

            
            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    
                    System.IO.File.WriteAllText(saveFileDialog.FileName, textBox5.Text);
                    MessageBox.Show("Failas issaugotas");
                }
                catch (Exception ex)
                {
                   
                    MessageBox.Show($"Klaida: {ex.Message}");
                }
            }
        }

        private void button8_Click(object sender, EventArgs e)
        {
      
            PrintDialog printDialog = new PrintDialog();

           
            PrintDocument printDocument = new PrintDocument();
            printDocument.PrintPage += new PrintPageEventHandler(printDocument_PrintPage);

            printDialog.Document = printDocument;

            
            if (printDialog.ShowDialog() == DialogResult.OK)
            {
                try
                {
                  
                    printDocument.Print();
                }
                catch (Exception ex)
                {
                    
                    MessageBox.Show($"Klaida: {ex.Message}");
                }
            }
        }
        private void printDocument_PrintPage(object sender, PrintPageEventArgs e)
        {
          
            string textToPrint = textBox5.Text;

            
            Font printFont = new Font("Arial", 12);

           
            PointF printLocation = new PointF(10, 10);

           
            e.Graphics.DrawString(textToPrint, printFont, Brushes.Black, printLocation);
        }


    }
}
