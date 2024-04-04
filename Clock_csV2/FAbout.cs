using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Management;

namespace frmAbout
{
	
	/// <summary>
    /// Summary description for FAbout.
	/// </summary>
	public class FAbout : System.Windows.Forms.Form
	{
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private Label lblCopyright;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public FAbout()
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
            button1 = new Button();
            label1 = new Label();
            groupBox1 = new GroupBox();
            label2 = new Label();
            label3 = new Label();
            lblCopyright = new Label();
            SuspendLayout();
            // 
            // button1
            // 
            button1.FlatStyle = FlatStyle.System;
            button1.ImeMode = ImeMode.NoControl;
            button1.Location = new Point(353, 77);
            button1.Name = "button1";
            button1.Size = new Size(73, 38);
            button1.TabIndex = 0;
            button1.Text = "&Ok";
            button1.Click += button1_Click;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.FlatStyle = FlatStyle.System;
            label1.ImeMode = ImeMode.NoControl;
            label1.Location = new Point(11, 2);
            label1.Name = "label1";
            label1.Size = new Size(57, 20);
            label1.TabIndex = 2;
            label1.Text = "Version";
            label1.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // groupBox1
            // 
            groupBox1.FlatStyle = FlatStyle.System;
            groupBox1.Location = new Point(6, 50);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(420, 13);
            groupBox1.TabIndex = 3;
            groupBox1.TabStop = false;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.FlatStyle = FlatStyle.System;
            label2.ImeMode = ImeMode.NoControl;
            label2.Location = new Point(11, 69);
            label2.Name = "label2";
            label2.Size = new Size(17, 20);
            label2.TabIndex = 4;
            label2.Text = "  ";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.FlatStyle = FlatStyle.System;
            label3.ImeMode = ImeMode.NoControl;
            label3.Location = new Point(11, 93);
            label3.Name = "label3";
            label3.Size = new Size(17, 20);
            label3.TabIndex = 5;
            label3.Text = "  ";
            // 
            // lblCopyright
            // 
            lblCopyright.AutoSize = true;
            lblCopyright.FlatStyle = FlatStyle.System;
            lblCopyright.ImeMode = ImeMode.NoControl;
            lblCopyright.Location = new Point(11, 26);
            lblCopyright.Name = "lblCopyright";
            lblCopyright.Size = new Size(173, 20);
            lblCopyright.TabIndex = 7;
            lblCopyright.Text = "Copyright (C) 2004-20XX";
            // 
            // FAbout
            // 
            AcceptButton = button1;
            AutoScaleBaseSize = new Size(7, 20);
            ClientSize = new Size(436, 122);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(groupBox1);
            Controls.Add(label1);
            Controls.Add(button1);
            Controls.Add(lblCopyright);
            FormBorderStyle = FormBorderStyle.FixedToolWindow;
            Name = "FAbout";
            Opacity = 0.85D;
            ShowInTaskbar = false;
            StartPosition = FormStartPosition.CenterScreen;
            Text = "About";
            Load += Form3_Load;
            ResumeLayout(false);
            PerformLayout();
        }
        #endregion

        private void button1_Click(object sender, System.EventArgs e)
		{
			this.Close();
		}

		private void Form3_Load(object sender, System.EventArgs e)
		{
			// ���������� ��� �������� �� �����.
			foreach(Control c in Controls)
			{
				// ���� ������� ���� ������� ������ ButtonBase,
				if(c is ButtonBase)
				{
					// �� ��������� ����� XP.
					((ButtonBase)c).FlatStyle = FlatStyle.System;
				}
			}


            label1.Text = "Clock Version " + Application.ProductVersion;

            //ManagementObjectSearcher s = new ManagementObjectSearcher("SELECT Caption, Version, ServicePackMajorVersion, TotalVisibleMemorySize FROM Win32_OperatingSystem");

            //string winver = null;
            //string winmem = null;
            //int valmem = 0;
            //foreach (ManagementObject m in s.Get())
            //{
            //    winver = m["Caption"].ToString() + " (" + m["Version"].ToString();
            //    winver += " Service Pack " + m["ServicePackMajorVersion"].ToString() + ")";

            //    valmem = Convert.ToInt32(m["TotalVisibleMemorySize"].ToString());
            //    winmem = "Physical memory available: " + valmem.ToString("### ### ### ###") + " KB";

            //}

            //label2.Text = winver;
            //label3.Text = winmem;

            label2.Text = getOSInfo();

            this.lblCopyright.Text = $"Copyright (C) 2004-{DateTime.Now.Year}";
        }

        private string getOSInfo()
        {
            //Get Operating system information.
            OperatingSystem os = Environment.OSVersion;
            //Get version information about the os.
            Version vs = os.Version;

            //Variable to hold our return value
            string operatingSystem = "";

            if (os.Platform == PlatformID.Win32Windows)
            {
                //This is a pre-NT version of Windows
                switch (vs.Minor)
                {
                    case 0:
                        operatingSystem = "95";
                        break;
                    case 10:
                        if (vs.Revision.ToString() == "2222A")
                            operatingSystem = "98SE";
                        else
                            operatingSystem = "98";
                        break;
                    case 90:
                        operatingSystem = "Me";
                        break;
                    default:
                        break;
                }
            }
            else if (os.Platform == PlatformID.Win32NT)
            {
                switch (vs.Major)
                {
                    case 3:
                        operatingSystem = "NT 3.51";
                        break;
                    case 4:
                        operatingSystem = "NT 4.0";
                        break;
                    case 5:
                        if (vs.Minor == 0)
                            operatingSystem = "2000";
                        else
                            operatingSystem = "XP";
                        break;
                    case 6:
                        if (vs.Minor == 0)
                            operatingSystem = "Vista";
                        else if (vs.Minor == 1)
                            operatingSystem = "7";
                        else if (vs.Minor == 2)
                            operatingSystem = "8";
                        else
                            operatingSystem = "8.1";
                        break;
                    case 10:
                        operatingSystem = "10";
                        break;
                    default:
                        break;
                }
            }
            //Make sure we actually got something in our OS check
            //We don't want to just return " Service Pack 2" or " 32-bit"
            //That information is useless without the OS version.
            if (operatingSystem != "")
            {
                //Got something.  Let's prepend "Windows" and get more info.
                operatingSystem = "Windows " + operatingSystem;
                //See if there's a service pack installed.
                if (os.ServicePack != "")
                {
                    //Append it to the OS name.  i.e. "Windows XP Service Pack 3"
                    operatingSystem += " " + os.ServicePack;
                }
                //Append the OS architecture.  i.e. "Windows XP Service Pack 3 32-bit"
                //operatingSystem += " " + getOSArchitecture().ToString() + "-bit";
            }
            //Return the information we've gathered.
            return operatingSystem;
        }

    }
}
