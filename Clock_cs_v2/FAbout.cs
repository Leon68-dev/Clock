using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Management;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Clock_cs_v2
{
    public partial class FAbout : Form
    {
        public FAbout()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, System.EventArgs e)
        {
            this.Close();
        }

        private void label1_Click(object sender, System.EventArgs e)
        {

        }

        private void Form3_Load(object sender, System.EventArgs e)
        {
            // ���������� ��� �������� �� �����.
            foreach (Control c in Controls)
            {
                // ���� ������� ���� ������� ������ ButtonBase,
                if (c is ButtonBase)
                {
                    // �� ��������� ����� XP.
                    ((ButtonBase)c).FlatStyle = FlatStyle.System;
                }
            }


            label1.Text = "Clock Version " + Application.ProductVersion;

            ManagementObjectSearcher s = new ManagementObjectSearcher("SELECT Caption, Version, ServicePackMajorVersion, TotalVisibleMemorySize FROM Win32_OperatingSystem");

            string winver = null;
            string winmem = null;
            int valmem = 0;
            foreach (ManagementObject m in s.Get())
            {
                winver = m["Caption"].ToString() + " (" + m["Version"].ToString();
                winver += " Service Pack " + m["ServicePackMajorVersion"].ToString() + ")";

                valmem = Convert.ToInt32(m["TotalVisibleMemorySize"].ToString());
                winmem = "Physical memory available: " + valmem.ToString("### ### ### ###") + " KB";

            }

            label2.Text = winver;
            label3.Text = winmem;
        }

    }
}
