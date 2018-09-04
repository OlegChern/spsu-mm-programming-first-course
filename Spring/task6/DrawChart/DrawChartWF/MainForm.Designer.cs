namespace DrawChartWF
{
    partial class MainForm
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.pbChart = new System.Windows.Forms.PictureBox();
            this.cmbCharts = new System.Windows.Forms.ComboBox();
            this.lblInfo = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.pbChart)).BeginInit();
            this.SuspendLayout();
            // 
            // pbChart
            // 
            this.pbChart.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.pbChart.Location = new System.Drawing.Point(0, 0);
            this.pbChart.Name = "pbChart";
            this.pbChart.Size = new System.Drawing.Size(494, 471);
            this.pbChart.TabIndex = 0;
            this.pbChart.TabStop = false;
            // 
            // cmbCharts
            // 
            this.cmbCharts.Dock = System.Windows.Forms.DockStyle.Top;
            this.cmbCharts.FormattingEnabled = true;
            this.cmbCharts.Location = new System.Drawing.Point(0, 0);
            this.cmbCharts.Name = "cmbCharts";
            this.cmbCharts.Size = new System.Drawing.Size(494, 21);
            this.cmbCharts.TabIndex = 1;
            this.cmbCharts.SelectedIndexChanged += new System.EventHandler(this.CbChartsSelectedIndexChanged);
            // 
            // lblInfo
            // 
            this.lblInfo.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.lblInfo.AutoSize = true;
            this.lblInfo.Location = new System.Drawing.Point(116, 449);
            this.lblInfo.Name = "lblInfo";
            this.lblInfo.Size = new System.Drawing.Size(292, 13);
            this.lblInfo.TabIndex = 2;
            this.lblInfo.Text = "Для изменения масштаба используйте колесико мыши";
            this.lblInfo.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(494, 471);
            this.Controls.Add(this.lblInfo);
            this.Controls.Add(this.cmbCharts);
            this.Controls.Add(this.pbChart);
            this.Name = "MainForm";
            this.Text = "Charts WF";
            this.Load += new System.EventHandler(this.MainFormLoad);
            this.SizeChanged += new System.EventHandler(this.MainFormSizeChanged);
            ((System.ComponentModel.ISupportInitialize)(this.pbChart)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pbChart;
        private System.Windows.Forms.ComboBox cmbCharts;
        private System.Windows.Forms.Label lblInfo;
    }
}

