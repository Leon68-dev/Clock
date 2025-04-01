using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data; 

namespace Clock_csc
{
	/// <summary>
	/// Summary description for FShotDown.
	/// </summary>
	public class FShutDown : System.Windows.Forms.Form
	{
        private DateTime mTm;
        private System.Windows.Forms.CheckBox chkIsWork;
        public bool isShutDown;
        public bool isShutDownTmp;
        public bool isSleep = false;
        public bool isSleepTmp = false;

        private System.Windows.Forms.Button btnOK;
		private System.Windows.Forms.Button btnCancel;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.Label label1;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;
        private CheckBox chkIsSleep;
        private System.Windows.Forms.DateTimePicker tmShutDown;
		

		public DateTime tm
		{
			set{mTm = value;}
			get{return mTm;}
		}
		
		public FShutDown()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}

		public FShutDown(DateTime tm, bool sd, bool sl)
        {
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			this.mTm = new DateTime();
			this.mTm = tm;
			this.tmShutDown.Value = this.mTm; 
			this.chkIsWork.Checked = sd;
            this.set_tmShutDown(this.chkIsWork.Checked);
            this.isShutDownTmp = sd;
            this.isSleep = sl;
            this.isSleepTmp = sl;
            this.chkIsSleep.Checked = isSleep; 
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
            btnOK = new Button();
            btnCancel = new Button();
            groupBox1 = new GroupBox();
            label1 = new Label();
            tmShutDown = new DateTimePicker();
            chkIsWork = new CheckBox();
            chkIsSleep = new CheckBox();
            SuspendLayout();
            // 
            // btnOK
            // 
            btnOK.FlatStyle = FlatStyle.System;
            btnOK.ImeMode = ImeMode.NoControl;
            btnOK.Location = new Point(22, 140);
            btnOK.Name = "btnOK";
            btnOK.Size = new Size(105, 35);
            btnOK.TabIndex = 0;
            btnOK.Text = "OK";
            btnOK.Click += btnOK_Click;
            // 
            // btnCancel
            // 
            btnCancel.FlatStyle = FlatStyle.System;
            btnCancel.ImeMode = ImeMode.NoControl;
            btnCancel.Location = new Point(140, 140);
            btnCancel.Name = "btnCancel";
            btnCancel.Size = new Size(105, 35);
            btnCancel.TabIndex = 1;
            btnCancel.Text = "Cancel";
            btnCancel.Click += btnCancel_Click;
            // 
            // groupBox1
            // 
            groupBox1.FlatStyle = FlatStyle.System;
            groupBox1.Location = new Point(6, 73);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(252, 6);
            groupBox1.TabIndex = 2;
            groupBox1.TabStop = false;
            // 
            // label1
            // 
            label1.FlatStyle = FlatStyle.System;
            label1.ImeMode = ImeMode.NoControl;
            label1.Location = new Point(28, 12);
            label1.Name = "label1";
            label1.Size = new Size(118, 25);
            label1.TabIndex = 3;
            label1.Text = "Time shut down";
            // 
            // tmShutDown
            // 
            tmShutDown.CustomFormat = "HH:mm";
            tmShutDown.Format = DateTimePickerFormat.Custom;
            tmShutDown.Location = new Point(152, 7);
            tmShutDown.Name = "tmShutDown";
            tmShutDown.ShowUpDown = true;
            tmShutDown.Size = new Size(100, 27);
            tmShutDown.TabIndex = 5;
            tmShutDown.Value = new DateTime(2005, 7, 20, 10, 21, 0, 0);
            // 
            // chkIsWork
            // 
            chkIsWork.FlatStyle = FlatStyle.System;
            chkIsWork.ImeMode = ImeMode.NoControl;
            chkIsWork.Location = new Point(56, 43);
            chkIsWork.Name = "chkIsWork";
            chkIsWork.Size = new Size(184, 30);
            chkIsWork.TabIndex = 6;
            chkIsWork.Text = "checkBox1";
            chkIsWork.CheckedChanged += chkIsWork_CheckedChanged;
            // 
            // chkIsSleep
            // 
            chkIsSleep.FlatStyle = FlatStyle.System;
            chkIsSleep.ImeMode = ImeMode.NoControl;
            chkIsSleep.Location = new Point(56, 87);
            chkIsSleep.Name = "chkIsSleep";
            chkIsSleep.Size = new Size(184, 30);
            chkIsSleep.TabIndex = 7;
            chkIsSleep.Text = "Sleep";
            chkIsSleep.CheckedChanged += chkIsSleep_CheckedChanged;
            // 
            // FShutDown
            // 
            AutoScaleBaseSize = new Size(7, 20);
            ClientSize = new Size(259, 188);
            Controls.Add(chkIsSleep);
            Controls.Add(chkIsWork);
            Controls.Add(tmShutDown);
            Controls.Add(label1);
            Controls.Add(groupBox1);
            Controls.Add(btnCancel);
            Controls.Add(btnOK);
            FormBorderStyle = FormBorderStyle.FixedToolWindow;
            MaximizeBox = false;
            MinimizeBox = false;
            Name = "FShutDown";
            Opacity = 0.85D;
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Shut down";
            ResumeLayout(false);
        }
        #endregion

        private void btnOK_Click(object sender, System.EventArgs e)
		{
			int hour = this.tmShutDown.Value.Hour;
			int minute = this.tmShutDown.Value.Minute;
			mTm = new DateTime(1999, 12, 16, hour, minute, 0);

			DataSet ds = new DataSet();
			ds.ReadXml(@cPubFunc.fileNameSet());
			ds.Tables[0].Rows[0]["timeOff"] = mTm;
            ds.Tables[0].Rows[0]["chkOff"] = isShutDown;  
			ds.WriteXml(@cPubFunc.fileNameSet());

			if(!isShutDown)
			{
 				this.Close();
			}
			
			ds.WriteXml(@cPubFunc.fileNameSet());

            isSleepTmp = isSleep;

            this.Close();
		}

		private void btnCancel_Click(object sender, System.EventArgs e)
		{
			isShutDown = isShutDownTmp;
            isSleep = isSleepTmp;
            if (!isShutDown)
                isSleep = false;

            this.Close();
		}

		private void set_tmShutDown(bool chkState)
		{
			if(chkState)
			{
				this.chkIsWork.Text = "Shut down \"On\"";
				this.tmShutDown.Enabled = true;

                this.isShutDown = true;
                this.chkIsSleep.Checked = this.isSleep;
            }
            else
			{
				this.chkIsWork.Text = "Shut down \"Off\"";
				this.tmShutDown.Enabled = false;
                this.isShutDown = false;

                this.chkIsSleep.Checked = false;
                this.isSleep = false;
			}

            this.chkIsSleep.Enabled = this.tmShutDown.Enabled;
        }

		private void chkIsWork_CheckedChanged(object sender, System.EventArgs e)
		{
            var v = sender as CheckBox;
			set_tmShutDown(v.Checked);
		}

        private void chkIsSleep_CheckedChanged(object sender, EventArgs e)
        {
            var v = sender as CheckBox;
            isSleep = v.Checked;
        }
    }
}
