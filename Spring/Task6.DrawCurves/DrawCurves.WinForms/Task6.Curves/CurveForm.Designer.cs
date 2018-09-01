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
            this.Small_Decrease = new System.Windows.Forms.Button();
            this.Small_Increase = new System.Windows.Forms.Button();
            this.Large_Decrease = new System.Windows.Forms.Button();
            this.Large_Increase = new System.Windows.Forms.Button();
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
            // Small_Decrease
            // 
            this.Small_Decrease.BackColor = System.Drawing.SystemColors.ControlLight;
            this.Small_Decrease.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Small_Decrease.Location = new System.Drawing.Point(12, 94);
            this.Small_Decrease.Name = "Small_Decrease";
            this.Small_Decrease.Size = new System.Drawing.Size(48, 25);
            this.Small_Decrease.TabIndex = 4;
            this.Small_Decrease.Text = "- 0.1";
            this.Small_Decrease.UseVisualStyleBackColor = false;
            this.Small_Decrease.Click += new System.EventHandler(this.buttonIncDec_Click);
            // 
            // Small_Increase
            // 
            this.Small_Increase.BackColor = System.Drawing.SystemColors.ControlLight;
            this.Small_Increase.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Small_Increase.Location = new System.Drawing.Point(143, 94);
            this.Small_Increase.Name = "Small_Increase";
            this.Small_Increase.Size = new System.Drawing.Size(47, 25);
            this.Small_Increase.TabIndex = 5;
            this.Small_Increase.Text = "+ 0.1";
            this.Small_Increase.UseVisualStyleBackColor = false;
            this.Small_Increase.Click += new System.EventHandler(this.buttonIncDec_Click);
            // 
            // Large_Decrease
            // 
            this.Large_Decrease.BackColor = System.Drawing.SystemColors.ControlLight;
            this.Large_Decrease.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Large_Decrease.Location = new System.Drawing.Point(12, 125);
            this.Large_Decrease.Name = "Large_Decrease";
            this.Large_Decrease.Size = new System.Drawing.Size(48, 25);
            this.Large_Decrease.TabIndex = 6;
            this.Large_Decrease.Text = "- 1";
            this.Large_Decrease.UseVisualStyleBackColor = false;
            this.Large_Decrease.Click += new System.EventHandler(this.buttonIncDec_Click);
            // 
            // Large_Increase
            // 
            this.Large_Increase.BackColor = System.Drawing.SystemColors.ControlLight;
            this.Large_Increase.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Large_Increase.Location = new System.Drawing.Point(143, 125);
            this.Large_Increase.Name = "Large_Increase";
            this.Large_Increase.Size = new System.Drawing.Size(48, 25);
            this.Large_Increase.TabIndex = 7;
            this.Large_Increase.Text = "+ 1";
            this.Large_Increase.UseVisualStyleBackColor = false;
            this.Large_Increase.Click += new System.EventHandler(this.buttonIncDec_Click);
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
            this.Controls.Add(this.Large_Increase);
            this.Controls.Add(this.Large_Decrease);
            this.Controls.Add(this.Small_Increase);
            this.Controls.Add(this.Small_Decrease);
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
        private System.Windows.Forms.Button Small_Decrease;
        private System.Windows.Forms.Button Small_Increase;
        private System.Windows.Forms.Button Large_Decrease;
        private System.Windows.Forms.Button Large_Increase;
        private System.Windows.Forms.Button buildButton;
    }
}

