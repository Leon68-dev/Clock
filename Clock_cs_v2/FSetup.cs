﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Clock_cs_v2
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
        public int mValOpacity = 100;
        public int mClose = -1;
        public bool mChkSound = false;

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
    bool ChkSound,
    int ValOpacity)
        {
            this.mChkGMT = ChkGMT;
            this.mChkDate = ChkDate;
            this.mChkDay = ChkDay;
            this.mChkMoving = ChkMoving;
            this.mChkAlwaysOnTop = ChkAlwaysOnTop;
            this.mChkTransparent = ChkTransparent;
            this.mChkBorder = ChkBorder;
            this.mChkSound = ChkSound;

            this.chkGMT.Checked = this.mChkGMT;
            this.chkDate.Checked = this.mChkDate;
            this.chkDay.Checked = this.mChkDay;
            this.chkMoving.Checked = this.mChkMoving;
            this.chkAlwaysOnTop.Checked = this.mChkAlwaysOnTop;
            this.chkTransparent.Checked = this.mChkTransparent;
            this.chkBorder.Checked = this.mChkBorder;
            this.chkSound.Checked = this.mChkSound;
            setOpacity(ValOpacity);

            if (!cPubFunc.existsTickTackWav())
            {
                this.chkSound.Checked = false;
                this.chkSound.Enabled = false;
            }
            else
                this.chkSound.Enabled = true;

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

            if (!cPubFunc.existsTickTackWav())
                this.mChkSound = false;
            else
                this.mChkSound = this.chkSound.Checked;

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
            this.toolTip1.SetToolTip(this.trckBarOpacity, this.trckBarOpacity.Value.ToString());
        }

    }
}
