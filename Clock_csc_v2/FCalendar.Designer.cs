namespace Clock_csc_v2
{
    partial class FCalendar
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
            button1 = new Button();
            monthCalendar1 = new MonthCalendar();
            SuspendLayout();
            // 
            // button1
            // 
            button1.FlatStyle = FlatStyle.System;
            button1.ImeMode = ImeMode.NoControl;
            button1.Location = new Point(60, 225);
            button1.Name = "button1";
            button1.Size = new Size(105, 36);
            button1.TabIndex = 1;
            button1.Text = "&Ok";
            button1.Click += button1_Click;
            // 
            // monthCalendar1
            // 
            monthCalendar1.ImeMode = ImeMode.NoControl;
            monthCalendar1.Location = new Point(12, 12);
            monthCalendar1.MaxDate = new DateTime(2100, 1, 1, 0, 0, 0, 0);
            monthCalendar1.MaxSelectionCount = 1;
            monthCalendar1.MinDate = new DateTime(1900, 1, 1, 0, 0, 0, 0);
            monthCalendar1.Name = "monthCalendar1";
            monthCalendar1.TabIndex = 2;
            monthCalendar1.TodayDate = new DateTime(2000, 12, 16, 0, 0, 0, 0);
            monthCalendar1.TrailingForeColor = Color.Green;
            // 
            // FCalendar
            // 
            AcceptButton = button1;
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(214, 265);
            Controls.Add(button1);
            Controls.Add(monthCalendar1);
            DoubleBuffered = true;
            FormBorderStyle = FormBorderStyle.FixedToolWindow;
            MaximizeBox = false;
            MinimizeBox = false;
            Name = "FCalendar";
            Opacity = 0.85D;
            ShowIcon = false;
            ShowInTaskbar = false;
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Calendar";
            Load += FCalendar_Load;
            ResumeLayout(false);
        }

        #endregion

        private Button button1;
        private MonthCalendar monthCalendar1;
    }
}