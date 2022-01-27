using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ConfusedFacePicture
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            int w = this.ClientSize.Width;
            int h = this.ClientSize.Height;

            Pen p = new Pen(Color.Black,3);

            Brush br_or;
            Color col_or = Color.FromName("orange");
            br_or = new SolidBrush(col_or);

            Brush br_bl;
            Color col_bl = Color.FromName("black");
            br_bl = new SolidBrush(col_bl);

            Brush br_gr;
            Color col_gr = Color.FromArgb(0,204,0);
            br_gr = new SolidBrush(col_gr);

            Brush br_pr;
            Color col_pr = Color.FromArgb(102, 102, 255);
            br_pr = new SolidBrush(col_pr);

            Brush br_rd;
            Color col_rd = Color.FromArgb(204, 0, 0);
            br_rd = new SolidBrush(col_rd);

            Brush br_ye;
            Color col_ye = Color.FromName("yellow");
            br_ye = new SolidBrush(col_ye);

            Brush br_pk;
            Color col_pk = Color.FromArgb(255, 102, 102);
            br_pk = new SolidBrush(col_pk);



            g.FillRectangle(br_ye, 0, 0, w, h);
            g.FillEllipse(br_or, (w / 2) - 95, h / 2 - 100, 60, 60);
            g.FillEllipse(br_gr, w / 2 + 35, h / 2 - 100, 60, 60);
            g.DrawEllipse(p, (w/2) - 95, h / 2 - 100, 60, 60);
            g.DrawEllipse(p, w / 2 + 35, h / 2 - 100, 60, 60);
            g.FillRectangle(br_pr, w / 2 - 90, h / 2 + 70, 180, 20);
            g.DrawRectangle(p, w / 2 - 90, h / 2 + 70, 180, 20 );
            g.FillRectangle(br_bl, w / 2 - 67, h / 2 - 73, 5, 5);
            g.FillRectangle(br_bl, w / 2 + 63, h / 2 - 73, 5, 5);

            Point[] pts1 = new Point[3];
            pts1[0].X = w / 2;
            pts1[0].Y = h / 2 - 30;
            pts1[1].X = w / 2 + 30;
            pts1[1].Y = h / 2 + 30;
            pts1[2].X = w / 2 - 30;
            pts1[2].Y = h / 2 + 30;
            g.FillPolygon(br_rd, pts1);

            Point[] pts = new Point[3];
            pts[0].X = w / 2;
            pts[0].Y = h / 2 - 30;
            pts[1].X = w / 2 + 30;
            pts[1].Y = h / 2 + 30;
            pts[2].X = w / 2 - 30;
            pts[2].Y = h / 2 + 30;
            g.DrawPolygon(p, pts);

            Font f = new Font("Arial", 10, FontStyle.Bold);
            g.DrawString("It is anether day in paradise",f, br_pk, w / 2 - 87, h / 2 + 120);
            g.DrawString("Click the mouse to continue", f, br_pr, w / 2 - 89, h / 2 + 140);
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            Invalidate();
        }

        private void Form1_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
