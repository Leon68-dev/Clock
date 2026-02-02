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
    public partial class FSetup : Form
    {
        public bool mChkGMT = false;
        public bool mChkDate = true;
        public bool mChkDay = true;
        public bool mChkMoving = true;
        public bool mChkAlwaysOnTop = false;
        public bool mChkTransparent = false;
        public bool mChkBorder = true;
        public int  mValOpacity = 100;
        public int  mClose = -1;
        public bool mChkSmooth = false;
        public bool mChkTickTak = false;
        public bool mChk1530 = false;
        public bool mChkHours = false;

        public FSetup()
        {
            InitializeComponent();
        }

        public void initialization(
            bool ChkGMT,
            bool ChkDate,
            bool ChkDay,
            bool ChkMoving,
            bool ChkAlwaysOnTop,
            bool ChkTransparent,
            bool ChkBorder,
            int  ValOpacity,
            bool ChkSmooth,
            bool ChkSoundTickTak,
            bool ChkSound1530,
            bool ChkSoundHours)
        {
            this.mChkGMT = ChkGMT;
            this.mChkDate = ChkDate;
            this.mChkDay = ChkDay;
            this.mChkMoving = ChkMoving;
            this.mChkAlwaysOnTop = ChkAlwaysOnTop;
            this.mChkTransparent = ChkTransparent;
            this.mChkBorder = ChkBorder;
            this.mChkSmooth = ChkSmooth;
            this.mChkTickTak = ChkSoundTickTak;
            this.mChk1530 = ChkSound1530;
            this.mChkHours = ChkSoundHours;

            this.chkGMT.Checked = this.mChkGMT;
            this.chkDate.Checked = this.mChkDate;
            this.chkDay.Checked = this.mChkDay;
            this.chkMoving.Checked = this.mChkMoving;
            this.chkAlwaysOnTop.Checked = this.mChkAlwaysOnTop;
            this.chkTransparent.Checked = this.mChkTransparent;
            this.chkBorder.Checked = this.mChkBorder;
            this.chkSmooth.Checked = this.mChkSmooth;
            this.chkTickTack.Checked = this.mChkTickTak;
            this.chk1530.Checked = this.mChk1530;
            this.chkHours.Checked = this.mChkHours;

            setOpacity(ValOpacity);
        }

        private void btnOk_Click(object sender, EventArgs e)
        {
            this.mClose = 1;

            this.mChkGMT = this.chkGMT.Checked;
            this.mChkDate = this.chkDate.Checked;
            this.mChkDay = this.chkDay.Checked;
            this.mChkMoving = this.chkMoving.Checked;
            this.mChkAlwaysOnTop = this.chkAlwaysOnTop.Checked;
            this.mChkMoving = this.chkMoving.Checked;
            this.mChkTransparent = this.chkTransparent.Checked;
            this.mChkBorder = this.chkBorder.Checked;
            this.mValOpacity = this.trckBarOpacity.Value;
            this.mChkSmooth = this.chkSmooth.Checked;
            this.mChkTickTak = this.chkTickTack.Checked;
            this.mChk1530 = this.chk1530.Checked;
            this.mChkHours = this.chkHours.Checked;

            this.Close();
        }

        public void setOpacity(int val)
        {
            mValOpacity = (int)val;
            this.trckBarOpacity.Value = mValOpacity;
            this.toolTip1.SetToolTip(this.trckBarOpacity, this.trckBarOpacity.Value.ToString());
        }

        //private double getOpacity()
        //{
        //    return this.trckBarOpacity.Value;
        //}

        private void trckBarOpacity_ValueChanged(object sender, EventArgs e)
        {
            //mValOpacity = this.trckBarOpacity.Value;
            this.toolTip1.SetToolTip(this.trckBarOpacity, this.trckBarOpacity.Value.ToString());
        }

    }
}
