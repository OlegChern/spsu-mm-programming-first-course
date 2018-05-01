namespace WinFormsTechnology
{
    partial class MainForm
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
            System.Windows.Forms.Label CurveListLabel;
            System.Windows.Forms.Label ScaleLabel;
            this.CurveListComboBox = new System.Windows.Forms.ComboBox();
            this.PictureBox = new System.Windows.Forms.PictureBox();
            this.BtnScaleUp = new System.Windows.Forms.Button();
            this.BtnScaleDown = new System.Windows.Forms.Button();
            CurveListLabel = new System.Windows.Forms.Label();
            ScaleLabel = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.PictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // CurveListLabel
            // 
            CurveListLabel.AutoSize = true;
            CurveListLabel.Location = new System.Drawing.Point(8, 20);
            CurveListLabel.Name = "CurveListLabel";
            CurveListLabel.Size = new System.Drawing.Size(149, 17);
            CurveListLabel.TabIndex = 1;
            CurveListLabel.Text = "Choose curve to draw:";
            // 
            // ScaleLabel
            // 
            ScaleLabel.AutoSize = true;
            ScaleLabel.Location = new System.Drawing.Point(8, 125);
            ScaleLabel.Name = "ScaleLabel";
            ScaleLabel.Size = new System.Drawing.Size(43, 17);
            ScaleLabel.TabIndex = 4;
            ScaleLabel.Text = "Scale";
            // 
            // CurveListComboBox
            // 
            this.CurveListComboBox.FormattingEnabled = true;
            this.CurveListComboBox.Location = new System.Drawing.Point(11, 43);
            this.CurveListComboBox.Name = "CurveListComboBox";
            this.CurveListComboBox.Size = new System.Drawing.Size(149, 24);
            this.CurveListComboBox.TabIndex = 0;
            this.CurveListComboBox.SelectedIndexChanged += new System.EventHandler(this.CurveListComboBoxSelectedIndexChanged);
            // 
            // PictureBox
            // 
            this.PictureBox.BackColor = System.Drawing.Color.White;
            this.PictureBox.Location = new System.Drawing.Point(167, 0);
            this.PictureBox.MinimumSize = new System.Drawing.Size(555, 555);
            this.PictureBox.Name = "PictureBox";
            this.PictureBox.Size = new System.Drawing.Size(555, 555);
            this.PictureBox.TabIndex = 2;
            this.PictureBox.TabStop = false;
            // 
            // BtnScaleUp
            // 
            this.BtnScaleUp.Location = new System.Drawing.Point(51, 150);
            this.BtnScaleUp.Name = "BtnScaleUp";
            this.BtnScaleUp.Size = new System.Drawing.Size(30, 30);
            this.BtnScaleUp.TabIndex = 3;
            this.BtnScaleUp.Text = "+";
            this.BtnScaleUp.UseVisualStyleBackColor = true;
            this.BtnScaleUp.Click += new System.EventHandler(this.BtnScaleUpClick);
            // 
            // BtnScaleDown
            // 
            this.BtnScaleDown.Location = new System.Drawing.Point(11, 150);
            this.BtnScaleDown.Name = "BtnScaleDown";
            this.BtnScaleDown.Size = new System.Drawing.Size(30, 30);
            this.BtnScaleDown.TabIndex = 5;
            this.BtnScaleDown.Text = "-";
            this.BtnScaleDown.UseVisualStyleBackColor = true;
            this.BtnScaleDown.Click += new System.EventHandler(this.BtnScaleDownClick);
            // 
            // MainForm
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(722, 555);
            this.Controls.Add(this.BtnScaleDown);
            this.Controls.Add(ScaleLabel);
            this.Controls.Add(this.BtnScaleUp);
            this.Controls.Add(this.PictureBox);
            this.Controls.Add(CurveListLabel);
            this.Controls.Add(this.CurveListComboBox);
            this.Cursor = System.Windows.Forms.Cursors.Default;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimumSize = new System.Drawing.Size(740, 600);
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Algebraic Curve";
            ((System.ComponentModel.ISupportInitialize)(this.PictureBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox CurveListComboBox;
        private System.Windows.Forms.PictureBox PictureBox;
        private System.Windows.Forms.Button BtnScaleUp;
        private System.Windows.Forms.Button BtnScaleDown;
    }
}