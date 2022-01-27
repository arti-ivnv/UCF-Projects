namespace Scrapper
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.txtResults = new System.Windows.Forms.RichTextBox();
            this.btnStartScrap = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // txtResults
            // 
            this.txtResults.Location = new System.Drawing.Point(12, 12);
            this.txtResults.Name = "txtResults";
            this.txtResults.Size = new System.Drawing.Size(565, 233);
            this.txtResults.TabIndex = 0;
            this.txtResults.Text = "";
            // 
            // btnStartScrap
            // 
            this.btnStartScrap.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F);
            this.btnStartScrap.Location = new System.Drawing.Point(231, 251);
            this.btnStartScrap.Name = "btnStartScrap";
            this.btnStartScrap.Size = new System.Drawing.Size(138, 62);
            this.btnStartScrap.TabIndex = 2;
            this.btnStartScrap.Text = "Start Scrapping";
            this.btnStartScrap.UseVisualStyleBackColor = true;
            this.btnStartScrap.Click += new System.EventHandler(this.btnStartScrap_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(589, 325);
            this.Controls.Add(this.btnStartScrap);
            this.Controls.Add(this.txtResults);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.RichTextBox txtResults;
        private System.Windows.Forms.Button btnStartScrap;
    }
}

