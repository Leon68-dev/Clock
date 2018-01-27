using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data; 

namespace Clock
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
        
		private System.Windows.Forms.Button btnOK;
		private System.Windows.Forms.Button btnCancel;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.Label label1;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;
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

		public FShutDown(DateTime tm, bool sd)
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();
			this.mTm = new DateTime();
			this.mTm = tm;
			this.tmShutDown.Value = this.mTm; 
			this.chkIsWork.Checked = sd;
			set_tmShutDown(this.chkIsWork.Checked);
			isShutDownTmp = sd;
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
			this.btnOK = new System.Windows.Forms.Button();
			this.btnCancel = new System.Windows.Forms.Button();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.label1 = new System.Windows.Forms.Label();
			this.tmShutDown = new System.Windows.Forms.DateTimePicker();
			this.chkIsWork = new System.Windows.Forms.CheckBox();
			this.SuspendLayout();
			// 
			// btnOK
			// 
			this.btnOK.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.btnOK.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.btnOK.Location = new System.Drawing.Point(16, 56);
			this.btnOK.Name = "btnOK";
			this.btnOK.TabIndex = 0;
			this.btnOK.Text = "OK";
			this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
			// 
			// btnCancel
			// 
			this.btnCancel.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.btnCancel.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.btnCancel.Location = new System.Drawing.Point(100, 56);
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.TabIndex = 1;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
			// 
			// groupBox1
			// 
			this.groupBox1.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.groupBox1.Location = new System.Drawing.Point(4, 48);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(180, 3);
			this.groupBox1.TabIndex = 2;
			this.groupBox1.TabStop = false;
			// 
			// label1
			// 
			this.label1.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.label1.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.label1.Location = new System.Drawing.Point(20, 8);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(84, 16);
			this.label1.TabIndex = 3;
			this.label1.Text = "Time shut down";
			// 
			// tmShutDown
			// 
			this.tmShutDown.CustomFormat = "HH:mm";
			this.tmShutDown.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
			this.tmShutDown.Location = new System.Drawing.Point(108, 4);
			this.tmShutDown.Name = "tmShutDown";
			this.tmShutDown.ShowUpDown = true;
			this.tmShutDown.Size = new System.Drawing.Size(72, 20);
			this.tmShutDown.TabIndex = 5;
			this.tmShutDown.Value = new System.DateTime(2005, 7, 20, 10, 21, 0, 0);
			// 
			// chkIsWork
			// 
			this.chkIsWork.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.chkIsWork.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.chkIsWork.Location = new System.Drawing.Point(40, 28);
			this.chkIsWork.Name = "chkIsWork";
			this.chkIsWork.Size = new System.Drawing.Size(132, 20);
			this.chkIsWork.TabIndex = 6;
			this.chkIsWork.Text = "checkBox1";
			this.chkIsWork.CheckedChanged += new System.EventHandler(this.chkIsWork_CheckedChanged);
			// 
			// FShutDown
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(186, 86);
			this.Controls.Add(this.chkIsWork);
			this.Controls.Add(this.tmShutDown);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.groupBox1);
			this.Controls.Add(this.btnCancel);
			this.Controls.Add(this.btnOK);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "FShutDown";
			this.Opacity = 0.85;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Shot down";
			this.ResumeLayout(false);

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
			this.Close();
		}

		private void btnCancel_Click(object sender, System.EventArgs e)
		{
			isShutDown = isShutDownTmp;
			this.Close();
		}

		private void set_tmShutDown(bool chkState)
		{
			if(chkState)
			{
				this.chkIsWork.Text = "Shut down \"On\"";
				this.tmShutDown.Enabled = true;
				isShutDown = true;
			}
			else
			{
				this.chkIsWork.Text = "Shut down \"Off\"";
				this.tmShutDown.Enabled = false; 
				isShutDown = false; 
			}
		}

		private void chkIsWork_CheckedChanged(object sender, System.EventArgs e)
		{
			set_tmShutDown(this.chkIsWork.Checked);
		}

	}
}
