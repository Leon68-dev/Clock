using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace toolbar
{
    public partial class FMain : Form
    {
        private int mOldX;
        private int mOldY;
        private bool mMouseDown;
        private DateTime mDate;
        private bool mTopMost = false;

        public FMain()
        {
            InitializeComponent();
            
            this.lblTime.Text = DateTime.Now.ToString("HH:mm:ss");
            
            this.mCalCurr.SetDate(DateTime.Now);
            this.mCalCurr.TodayDate = DateTime.Now;
            
            setDateTime(DateTime.Now);

            //this.mCalPrev.TrailingForeColor
            
            this.TopMost = mTopMost;
        }

        private void FMain_MouseDown(object sender, MouseEventArgs e)
        {
            mMouseDown = true;
            mOldX = e.X;
            mOldY = e.Y;
        }

        private void FMain_MouseUp(object sender, MouseEventArgs e)
        {
            mMouseDown = false;
        }

        private void FMain_MouseMove(object sender, MouseEventArgs e)
        {
            if (mMouseDown)
            {
                this.Left = this.Left + e.X - mOldX;
                this.Top = this.Top + e.Y - mOldY;
            }
        }

        /// <summary>
        /// Выход из проги
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        /// <summary>
        /// Таймер
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tmr_Tick(object sender, EventArgs e)
        {
            currTime();
        }

        /// <summary>
        /// Установка текущего времени
        /// </summary>
        private void currTime()
        {
            this.lblTime.Text = DateTime.Now.ToString("HH:mm:ss");

            if (DateTime.Now.Hour == 0 & DateTime.Now.Minute == 0 & DateTime.Now.Second == 0)
            {
                this.mCalCurr.SetDate(DateTime.Now);
                this.mCalCurr.TodayDate = DateTime.Now;

                setDateTime(DateTime.Now);
            }
        }

        /// <summary>
        /// Установки календарей "перед" и "следущий"
        /// </summary>
        /// <param name="dt"></param>
        private void setDateTime(DateTime dt)
        {
            mDate = dt;
            mDate = mDate.AddMonths(-1);
            this.mCalPrev.SetDate(mDate);
            
            mDate = dt;
            mDate = mDate.AddMonths(1);
            this.mCalNext.SetDate(mDate);

            int day = (int)DateTime.Now.DayOfWeek;
            switch (day)
            {
                case 0:
                    this.grpTime.Text = "Воскресение";
                    break;
                case 1:
                    this.grpTime.Text = "Понедельник";
                    break;
                case 2:
                    this.grpTime.Text = "Вторник";
                    break;
                case 3:
                    this.grpTime.Text = "Среда";
                    break;
                case 4:
                    this.grpTime.Text = "Четверг";
                    break;
                case 5:
                    this.grpTime.Text = "Пятница";
                    break;
                case 6:
                    this.grpTime.Text = "Суббота";
                    break;
            }
        }
        
        private void ntfIcon_DoubleClick(object sender, EventArgs e)
        {
            mTopMost = !mTopMost;
            this.TopMost = mTopMost;
        }


        private void lblTime_DoubleClick(object sender, EventArgs e)
        {
            this.mCalCurr.SetDate(DateTime.Now);
            this.mCalCurr.TodayDate = DateTime.Now;
            setDateTime(DateTime.Now);
        }

        private void mCalCurr_DateChanged(object sender, DateRangeEventArgs e)
        {
            DateTime dt = e.Start.Date;
            setDateTime(dt);
        }

    }
}