using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Clock_csc_v2
{
    public partial class FShutDown : Form
    {
        private DateTime mTm;
        public bool isShutDown;
        public bool isShutDownTmp;
        public bool isSleep = false;
        public bool isSleepTmp = false;

        public DateTime tm
        {
            set { mTm = value; }
            get { return mTm; }
        }

        public FShutDown()
        {
            InitializeComponent();
        }
        public FShutDown(DateTime tm, bool sd, bool sl)
        {
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

        private void btnOK_Click(object sender, EventArgs e)
        {
            int hour = this.tmShutDown.Value.Hour;
            int minute = this.tmShutDown.Value.Minute;
            mTm = new DateTime(1999, 12, 16, hour, minute, 0);

            DataSet ds = new DataSet();
            ds.ReadXml(@cPubFunc.fileNameSet());
            ds.Tables[0].Rows[0]["timeOff"] = mTm;
            ds.Tables[0].Rows[0]["chkOff"] = isShutDown;
            ds.WriteXml(@cPubFunc.fileNameSet());

            if (!isShutDown)
            {
                this.Close();
            }

            ds.WriteXml(@cPubFunc.fileNameSet());

            isSleepTmp = isSleep;

            this.Close();

        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            isShutDown = isShutDownTmp;
            isSleep = isSleepTmp;
            if (!isShutDown)
                isSleep = false;

            this.Close();

        }

        private void set_tmShutDown(bool chkState)
        {
            if (chkState)
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


        private void chkIsWork_CheckedChanged(object sender, EventArgs e)
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
