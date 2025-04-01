using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Clock_csc_v2
{
    public partial class FAbout : Form
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct MEMORYSTATUSEX
        {
            public uint dwLength;
            public uint dwMemoryLoad;
            public ulong ullTotalPhys;
            public ulong ullAvailPhys;
            public ulong ullTotalPageFile;
            public ulong ullAvailPageFile;
            public ulong ullTotalVirtual;
            public ulong ullAvailVirtual;
            public ulong ullAvailExtendedVirtual;
        }

        [DllImport("kernel32.dll")]
        public static extern bool GlobalMemoryStatusEx(ref MEMORYSTATUSEX lpBuffer);


        public FAbout()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void FAbout_Load(object sender, EventArgs e)
        {
            try
            {
                var ver = "1.0.0";
                //label1.Text = "Clock Version " + Application.ProductVersion;
                label1.Text = $"Clock Version {ver}";
                this.lblCopyright.Text = $"Copyright (C) 2004-{DateTime.Now.Year}";

                var os = RuntimeInformation.OSDescription;
                if (os.Contains("Windows"))
                {
                    lblWinVersion.Text = os;

                    MEMORYSTATUSEX memStatus = new MEMORYSTATUSEX();
                    memStatus.dwLength = (uint)Marshal.SizeOf(typeof(MEMORYSTATUSEX));

                    if (GlobalMemoryStatusEx(ref memStatus))
                    {
                        lblTotalPhysicalMem.Text = ($"Total Physical Memory {memStatus.ullTotalPhys / (1024 * 1024 * 1024)} GB");
                        lblAvailablePhysicalMem.Text = ($"Available Physical Memory {memStatus.ullAvailPhys / (1024 * 1024 * 1024)} GB");
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Console.WriteLine(ex.StackTrace);
            }

        }
    }
}
