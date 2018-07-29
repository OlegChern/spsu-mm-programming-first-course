namespace Task6.Curves
{
    partial class CurveForm
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
            this.comboBoxCurves = new System.Windows.Forms.ComboBox();
            this.CurveLabel = new System.Windows.Forms.Label();
            this.ScaleLabel = new System.Windows.Forms.Label();
            this.ScaleChangeLabel = new System.Windows.Forms.Label();
            this.Dec1 = new System.Windows.Forms.Button();
            this.Inc1 = new System.Windows.Forms.Button();
            this.Dec2 = new System.Windows.Forms.Button();
            this.Inc2 = new System.Windows.Forms.Button();
            this.buildButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // comboBoxCurves
            // 
            this.comboBoxCurves.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.comboBoxCurves.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxCurves.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.comboBoxCurves.FormattingEnabled = true;
            this.comboBoxCurves.Location = new System.Drawing.Point(12, 32);
            this.comboBoxCurves.Name = "comboBoxCurves";
            this.comboBoxCurves.Size = new System.Drawing.Size(178, 24);
            this.comboBoxCurves.TabIndex = 0;
            // 
            // CurveLabel
            // 
            this.CurveLabel.AutoSize = true;
            this.CurveLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.CurveLabel.Location = new System.Drawing.Point(13, 13);
            this.CurveLabel.Name = "CurveLabel";
            this.CurveLabel.Size = new System.Drawing.Size(60, 16);
            this.CurveLabel.TabIndex = 1;
            this.CurveLabel.Text = "Curves:";
            // 
            // ScaleLabel
            // 
            this.ScaleLabel.AutoSize = true;
            this.ScaleLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.ScaleLabel.Location = new System.Drawing.Point(13, 68);
            this.ScaleLabel.Name = "ScaleLabel";
            this.ScaleLabel.Size = new System.Drawing.Size(169, 16);
            this.ScaleLabel.TabIndex = 2;
            this.ScaleLabel.Text = "Scale  (from 0.1 to 4.9) :";
            // 
            // ScaleChangeLabel
            // 
            this.ScaleChangeLabel.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.ScaleChangeLabel.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.ScaleChangeLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.ScaleChangeLabel.Location = new System.Drawing.Point(66, 94);
            this.ScaleChangeLabel.Name = "ScaleChangeLabel";
            this.ScaleChangeLabel.Size = new System.Drawing.Size(71, 56);
            this.ScaleChangeLabel.TabIndex = 3;
            this.ScaleChangeLabel.Text = "1";
            this.ScaleChangeLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Dec1
            // 
            this.Dec1.BackColor = System.Drawing.SystemColors.ControlLight;
            this.Dec1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Dec1.Location = new System.Drawing.Point(12, 94);
            this.Dec1.Name = "Dec1";
            this.Dec1.Size = new System.Drawing.Size(48, 25);
            this.Dec1.TabIndex = 4;
            this.Dec1.Text = "- 0.1";
            this.Dec1.UseVisualStyleBackColor = false;
            this.Dec1.Click += new System.EventHandler(this.buttonIncDec_Click);
            // 
            // Inc1
            // 
            this.Inc1.BackColor = System.Drawing.SystemColors.ControlLight;
            this.Inc1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Inc1.Location = new System.Drawing.Point(143, 94);
            this.Inc1.Name = "Inc1";
            this.Inc1.Size = new System.Drawing.Size(47, 25);
            this.Inc1.TabIndex = 5;
            this.Inc1.Text = "+ 0.1";
            this.Inc1.UseVisualStyleBackColor = false;
            this.Inc1.Click += new System.EventHandler(this.buttonIncDec_Click);
            // 
            // Dec2
            // 
            this.Dec2.BackColor = System.Drawing.SystemColors.ControlLight;
            this.Dec2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Dec2.Location = new System.Drawing.Point(12, 125);
            this.Dec2.Name = "Dec2";
            this.Dec2.Size = new System.Drawing.Size(48, 25);
            this.Dec2.TabIndex = 6;
            this.Dec2.Text = "- 1";
            this.Dec2.UseVisualStyleBackColor = false;
            this.Dec2.Click += new System.EventHandler(this.buttonIncDec_Click);
            // 
            // Inc2
            // 
            this.Inc2.BackColor = System.Drawing.SystemColors.ControlLight;
            this.Inc2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Inc2.Location = new System.Drawing.Point(143, 125);
            this.Inc2.Name = "Inc2";
            this.Inc2.Size = new System.Drawing.Size(48, 25);
            this.Inc2.TabIndex = 7;
            this.Inc2.Text = "+ 1";
            this.Inc2.UseVisualStyleBackColor = false;
            this.Inc2.Click += new System.EventHandler(this.buttonIncDec_Click);
            // 
            // buildButton
            // 
            this.buildButton.BackColor = System.Drawing.SystemColors.ControlLight;
            this.buildButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buildButton.ForeColor = System.Drawing.SystemColors.ControlText;
            this.buildButton.Location = new System.Drawing.Point(12, 171);
            this.buildButton.Name = "buildButton";
            this.buildButton.Size = new System.Drawing.Size(178, 25);
            this.buildButton.TabIndex = 8;
            this.buildButton.Text = "build curve";
            this.buildButton.UseVisualStyleBackColor = false;
            this.buildButton.Click += new System.EventHandler(this.buildButton_Click);
            // 
            // CurveForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(744, 421);
            this.Controls.Add(this.buildButton);
            this.Controls.Add(this.Inc2);
            this.Controls.Add(this.Dec2);
            this.Controls.Add(this.Inc1);
            this.Controls.Add(this.Dec1);
            this.Controls.Add(this.ScaleChangeLabel);
            this.Controls.Add(this.ScaleLabel);
            this.Controls.Add(this.CurveLabel);
            this.Controls.Add(this.comboBoxCurves);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximumSize = new System.Drawing.Size(760, 460);
            this.MinimumSize = new System.Drawing.Size(760, 460);
            this.Name = "CurveForm";
            this.Text = "Curves";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox comboBoxCurves;
        private System.Windows.Forms.Label CurveLabel;
        private System.Windows.Forms.Label ScaleLabel;
        private System.Windows.Forms.Label ScaleChangeLabel;
        private System.Windows.Forms.Button Dec1;
        private System.Windows.Forms.Button Inc1;
        private System.Windows.Forms.Button Dec2;
        private System.Windows.Forms.Button Inc2;
        private System.Windows.Forms.Button buildButton;
    }
}

