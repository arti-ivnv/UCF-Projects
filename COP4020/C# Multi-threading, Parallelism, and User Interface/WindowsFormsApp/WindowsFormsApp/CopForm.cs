using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp
{
    public partial class CopForm : Form
    {
        public CopForm()
        {
            InitializeComponent();
        }

        private void lblInput_Click(object sender, EventArgs e)
        {

        }

        private void cmbInConversion_SelectedIndexChanged(object sender, EventArgs e)
        {
        }

        static string[] conversions = { "Farenheit", "Celsius", "Kelvin" };

        private void CopForm_Load(object sender, EventArgs e)
        {
            foreach (string type in conversions)
            {
                cmbInConversion.Items.Add(type);
            }

            foreach (string type in conversions)
            {
                cmbOutType.Items.Add(type);
            }


            cmbInConversion.SelectedIndex = 0;
            cmbOutType.SelectedIndex = 0;
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        String cleanMe( TextBox obj )
        {
            return obj.Text.Trim().Replace(",", "");
        }

        private void btnCalc_Click(object sender, EventArgs e)
        {
            double temp = 0;

            try
            {
                temp = Convert.ToDouble(cleanMe(txtIn));
            }
            catch
            {
                MessageBox.Show("Invalid input. Make sure you entering integer or decimal value");
            }

            if (cmbInConversion.SelectedIndex == 0 && cmbOutType.SelectedIndex == 0)
            {
                lblResultOut.Text = String.Format("Farenheits: {0:n2}", Convert.ToDouble(temp));
            }
            else if (cmbInConversion.SelectedIndex == 0 && cmbOutType.SelectedIndex == 1)
            {
                lblResultOut.Text = String.Format("Celsius: {0:n2}", Convert.ToDouble(temp - 32) * (5.0/9.0));
            }
            else if (cmbInConversion.SelectedIndex == 0 && cmbOutType.SelectedIndex == 2)
            {
                lblResultOut.Text = String.Format("Kelvins: {0:n2}", (Convert.ToDouble(temp - 32) * (5.0 / 9.0)) + 273.15);
            }
            else if (cmbInConversion.SelectedIndex == 1 && cmbOutType.SelectedIndex == 0)
            {
                lblResultOut.Text = String.Format("Farenheits: {0:n2}", (Convert.ToDouble(temp * (9.0 / 5.0)) + 32));
            }
            else if (cmbInConversion.SelectedIndex == 1 && cmbOutType.SelectedIndex == 1)
            {
                lblResultOut.Text = String.Format("Celsius: {0:n2}", Convert.ToDouble(temp));
            }
            else if (cmbInConversion.SelectedIndex == 1 && cmbOutType.SelectedIndex == 2)
            {
                lblResultOut.Text = String.Format("Kelvins: {0:n2}", Convert.ToDouble(temp + 273.15));
            }
            else if (cmbInConversion.SelectedIndex == 2 && cmbOutType.SelectedIndex == 0)
            {
                lblResultOut.Text = String.Format("Farenheits: {0:n2}", (Convert.ToDouble(temp - 273.15) * (9.0 / 5.0)) + 32);
            }
            else if (cmbInConversion.SelectedIndex == 2 && cmbOutType.SelectedIndex == 1)
            {
                lblResultOut.Text = String.Format("Celsius: {0:n2}", Convert.ToDouble(temp - 273.15));
            }
            else if (cmbInConversion.SelectedIndex == 2 && cmbOutType.SelectedIndex == 2)
            {
                lblResultOut.Text = String.Format("Kelvins: {0:n2}", Convert.ToDouble(temp));
            }

        }
    }
}
