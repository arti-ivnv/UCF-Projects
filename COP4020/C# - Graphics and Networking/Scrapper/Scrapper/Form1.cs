using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using OpenQA.Selenium;
using OpenQA.Selenium.Chrome;

namespace Scrapper
{
    public partial class Form1 : Form
    {

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void Find_Data()
        {
            HtmlAgilityPack.HtmlWeb driver = new HtmlAgilityPack.HtmlWeb();
            HtmlAgilityPack.HtmlDocument dc = driver.Load("http://rickleinecker.com/index.html");
            var outPut = dc.DocumentNode.SelectNodes("//div[@class='PaneText']").ToList();

            foreach (var item in outPut)
            {
                txtResults.AppendText(item.InnerText + "\t\r");
                txtResults.AppendText("\t\r");
            }
        }

        private void btnStartScrap_Click(object sender, EventArgs e)
        {
            Find_Data();
        }
    }
}
