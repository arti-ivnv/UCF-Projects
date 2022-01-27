namespace WindowsFormsApp
{
    partial class CopForm
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
            this.lblInput = new System.Windows.Forms.Label();
            this.txtIn = new System.Windows.Forms.TextBox();
            this.cmbInConversion = new System.Windows.Forms.ComboBox();
            this.lblInType = new System.Windows.Forms.Label();
            this.lblOutType = new System.Windows.Forms.Label();
            this.cmbOutType = new System.Windows.Forms.ComboBox();
            this.lblResult = new System.Windows.Forms.Label();
            this.lblResultOut = new System.Windows.Forms.Label();
            this.btnCalc = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // lblInput
            // 
            this.lblInput.AutoSize = true;
            this.lblInput.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F);
            this.lblInput.Location = new System.Drawing.Point(12, 30);
            this.lblInput.Name = "lblInput";
            this.lblInput.Size = new System.Drawing.Size(146, 24);
            this.lblInput.TabIndex = 0;
            this.lblInput.Text = "Enter a number:";
            this.lblInput.Click += new System.EventHandler(this.lblInput_Click);
            // 
            // txtIn
            // 
            this.txtIn.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F);
            this.txtIn.Location = new System.Drawing.Point(164, 27);
            this.txtIn.Name = "txtIn";
            this.txtIn.Size = new System.Drawing.Size(149, 29);
            this.txtIn.TabIndex = 1;
            // 
            // cmbInConversion
            // 
            this.cmbInConversion.BackColor = System.Drawing.SystemColors.Window;
            this.cmbInConversion.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbInConversion.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F);
            this.cmbInConversion.FormattingEnabled = true;
            this.cmbInConversion.Location = new System.Drawing.Point(164, 81);
            this.cmbInConversion.Name = "cmbInConversion";
            this.cmbInConversion.Size = new System.Drawing.Size(149, 32);
            this.cmbInConversion.TabIndex = 2;
            this.cmbInConversion.SelectedIndexChanged += new System.EventHandler(this.cmbInConversion_SelectedIndexChanged);
            // 
            // lblInType
            // 
            this.lblInType.AutoSize = true;
            this.lblInType.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F);
            this.lblInType.Location = new System.Drawing.Point(16, 89);
            this.lblInType.Name = "lblInType";
            this.lblInType.Size = new System.Drawing.Size(122, 24);
            this.lblInType.TabIndex = 3;
            this.lblInType.Text = "Convert from:";
            // 
            // lblOutType
            // 
            this.lblOutType.AutoSize = true;
            this.lblOutType.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F);
            this.lblOutType.Location = new System.Drawing.Point(16, 191);
            this.lblOutType.Name = "lblOutType";
            this.lblOutType.Size = new System.Drawing.Size(100, 24);
            this.lblOutType.TabIndex = 4;
            this.lblOutType.Text = "Convert to:";
            this.lblOutType.Click += new System.EventHandler(this.label1_Click);
            // 
            // cmbOutType
            // 
            this.cmbOutType.BackColor = System.Drawing.SystemColors.Window;
            this.cmbOutType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbOutType.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F);
            this.cmbOutType.FormattingEnabled = true;
            this.cmbOutType.Location = new System.Drawing.Point(164, 188);
            this.cmbOutType.Name = "cmbOutType";
            this.cmbOutType.Size = new System.Drawing.Size(149, 32);
            this.cmbOutType.TabIndex = 5;
            // 
            // lblResult
            // 
            this.lblResult.AutoSize = true;
            this.lblResult.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F);
            this.lblResult.Location = new System.Drawing.Point(30, 366);
            this.lblResult.Name = "lblResult";
            this.lblResult.Size = new System.Drawing.Size(67, 24);
            this.lblResult.TabIndex = 6;
            this.lblResult.Text = "Result:";
            // 
            // lblResultOut
            // 
            this.lblResultOut.AutoSize = true;
            this.lblResultOut.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F);
            this.lblResultOut.Location = new System.Drawing.Point(103, 366);
            this.lblResultOut.Name = "lblResultOut";
            this.lblResultOut.Size = new System.Drawing.Size(0, 24);
            this.lblResultOut.TabIndex = 7;
            // 
            // btnCalc
            // 
            this.btnCalc.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F);
            this.btnCalc.Location = new System.Drawing.Point(12, 277);
            this.btnCalc.Name = "btnCalc";
            this.btnCalc.Size = new System.Drawing.Size(119, 46);
            this.btnCalc.TabIndex = 8;
            this.btnCalc.Text = "Calculate";
            this.btnCalc.UseVisualStyleBackColor = true;
            this.btnCalc.Click += new System.EventHandler(this.btnCalc_Click);
            // 
            // CopForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.btnCalc);
            this.Controls.Add(this.lblResultOut);
            this.Controls.Add(this.lblResult);
            this.Controls.Add(this.cmbOutType);
            this.Controls.Add(this.lblOutType);
            this.Controls.Add(this.lblInType);
            this.Controls.Add(this.cmbInConversion);
            this.Controls.Add(this.txtIn);
            this.Controls.Add(this.lblInput);
            this.Name = "CopForm";
            this.Text = "COP Form";
            this.Load += new System.EventHandler(this.CopForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblInput;
        private System.Windows.Forms.TextBox txtIn;
        private System.Windows.Forms.ComboBox cmbInConversion;
        private System.Windows.Forms.Label lblInType;
        private System.Windows.Forms.Label lblOutType;
        private System.Windows.Forms.ComboBox cmbOutType;
        private System.Windows.Forms.Label lblResult;
        private System.Windows.Forms.Label lblResultOut;
        private System.Windows.Forms.Button btnCalc;
    }
}

