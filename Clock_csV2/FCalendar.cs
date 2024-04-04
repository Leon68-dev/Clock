using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace Clock
{
	/// <summary>
	/// Summary description for Form2.
	/// </summary>
	public class FCalendar : System.Windows.Forms.Form
	{
		private System.Windows.Forms.MonthCalendar monthCalendar1;
		private System.Windows.Forms.Button button1;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public FCalendar()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if(components != null)
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

        #region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            monthCalendar1 = new MonthCalendar();
            button1 = new Button();
            SuspendLayout();
            // 
            // monthCalendar1
            // 
            monthCalendar1.ImeMode = ImeMode.NoControl;
            monthCalendar1.Location = new Point(10, 5);
            monthCalendar1.MaxDate = new DateTime(2100, 1, 1, 0, 0, 0, 0);
            monthCalendar1.MaxSelectionCount = 1;
            monthCalendar1.MinDate = new DateTime(1900, 1, 1, 0, 0, 0, 0);
            monthCalendar1.Name = "monthCalendar1";
            monthCalendar1.TabIndex = 0;
            monthCalendar1.TodayDate = new DateTime(2000, 12, 16, 0, 0, 0, 0);
            monthCalendar1.TrailingForeColor = Color.Green;
            // 
            // button1
            // 
            button1.FlatStyle = FlatStyle.System;
            button1.ImeMode = ImeMode.NoControl;
            button1.Location = new Point(58, 218);
            button1.Name = "button1";
            button1.Size = new Size(105, 36);
            button1.TabIndex = 0;
            button1.Text = "&Ok";
            button1.Click += button1_Click;
            // 
            // FCalendar
            // 
            AcceptButton = button1;
            AutoScaleBaseSize = new Size(7, 20);
            ClientSize = new Size(213, 264);
            Controls.Add(button1);
            Controls.Add(monthCalendar1);
            DoubleBuffered = true;
            FormBorderStyle = FormBorderStyle.FixedToolWindow;
            Name = "FCalendar";
            Opacity = 0.85D;
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Calendar";
            Load += Form2_Load;
            ResumeLayout(false);
        }
        #endregion

        private void Form2_Load(object sender, System.EventArgs e)
		{
			setCalendar();
		}
		
		private void setCalendar()
		{
			int dday = DateTime.Now.Day;
			int mmonth = DateTime.Now.Month;
			int yyear = DateTime.Now.Year;
			
			DateTime bBeg = new DateTime(yyear, mmonth, dday);
			DateTime eEnd = new DateTime(yyear, mmonth, dday);
			
			monthCalendar1.SelectionRange = new SelectionRange(bBeg, eEnd);
			monthCalendar1.TodayDate = bBeg;
		}

		private void button1_Click(object sender, System.EventArgs e)
		{
			this.Close();
		}
	}
}
