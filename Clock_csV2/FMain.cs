using System;
using System.Drawing;
using System.Windows.Forms;
using System.Data;
using System.IO;

namespace Clock
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class FMain : System.Windows.Forms.Form
	{
        private Pen pHandHr;
        private Pen pHandMin;
        private Pen pHhandSec;
        private int mSizeDefault;
        private int mXCenter;
        private int mYCenter;
        private int mDeskX;
        private int mDeskY;
        private bool msDown;
        private int mOldX;
        private int mOldY;
        int mTypeActivate = 0;
        private DateTime mCurDateTime;
        private DateTime mTimeShutDown;
        private bool mIsShutDown;
        private bool mIsSleep = false;
        //private int mCountBoom;
        //private bool mCanBoom;
        //private bool mTckTck = true;
        //private bool mCanClose;
        private bool mChkGMT = false;
        private bool mChkDate = true;
        private bool mChkDay = true;
        private bool mChkMoving = true;
        private bool mChkAlwaysOnTop = false;
        private bool mChkTransparent = false;
        private bool mChkBorder = true;
        private double mFrmOpacity = 1;
        private string mTblName = "clock_cs";
        //private int mCalcCountBoom = 20;
        //private Thread thr;
        private bool mChkSound = false;
        //private PaintEventArgs mPaintEventArgs = null;
        //private Color mColorBlackWhite;
        private int mClcTick = 0;
        private int mMaxCountTick = 0;
        private int mIntervalRefr = 1000;

        private System.Windows.Forms.Timer timer1; 
        private System.ComponentModel.IContainer components;
		private System.Windows.Forms.NotifyIcon notifyIcon1;
        private System.Windows.Forms.ContextMenu contextMenu1;
		private System.Windows.Forms.MenuItem mExit;
		private System.Windows.Forms.MenuItem menuItem9;
		private System.Windows.Forms.MenuItem mAbout;
        private System.Windows.Forms.MenuItem mOpen;
        private ContextMenuStrip contextMenuFMain;
        private ToolStripMenuItem cm_hide;
        private ToolStripMenuItem cm_calendar;
        private ToolStripMenuItem cm_setShutDownPC;
        private ToolStripSeparator toolStripSeparator1;
        private ToolStripMenuItem cm_about;
        private ToolStripSeparator toolStripSeparator2;
        private ToolStripMenuItem cm_exit;
        private ToolStripSeparator toolStripSeparator3;
        private ToolStripMenuItem cm_Setup;
        private ToolStripMenuItem cm_StartPosition;
        private MenuItem mSetup;
        private MenuItem menuItem1;

		public FMain()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}

        public void initialization()
        {
            //this.Visible = false;
            mClcTick = 0;
            int sH = (int)(this.Size.Height);
            int sW = (int)(this.Size.Width);
            this.Size = new Size(sW, sH);

            //Позиционирование
            startPosition(ref mDeskX, ref mDeskY);

            mTimeShutDown = new DateTime();
            mTimeShutDown = cPubFunc.chkTime();
            //mCountBoom = 0;
            //mTckTck = false;
            
            //string str = Environment.ExpandEnvironmentVariables("%SystemRoot%");
            //cPubFunc.playSound(@str + @"\Media\tada.wav");

            DataSet ds = new DataSet();

            try
            {
                string filename = @cPubFunc.fileNameSet();
                if (File.Exists(filename))
                {
                    ds.ReadXml(filename);
                    mTimeShutDown = Convert.ToDateTime(ds.Tables[mTblName].Rows[0]["timeOff"].ToString());
                    mIsShutDown = System.Convert.ToBoolean(ds.Tables[mTblName].Rows[0]["chkOff"].ToString());
                    mChkGMT = System.Convert.ToBoolean(ds.Tables[mTblName].Rows[0]["chkGMT"].ToString());
                    mChkDate = System.Convert.ToBoolean(ds.Tables[mTblName].Rows[0]["chkDate"].ToString());
                    mChkDay = System.Convert.ToBoolean(ds.Tables[mTblName].Rows[0]["chkDay"].ToString());
                    mChkMoving = System.Convert.ToBoolean(ds.Tables[mTblName].Rows[0]["chkMoving"].ToString());
                    mChkTransparent = System.Convert.ToBoolean(ds.Tables[mTblName].Rows[0]["chkTransparent"].ToString());
                    mChkAlwaysOnTop = System.Convert.ToBoolean(ds.Tables[mTblName].Rows[0]["chkAlwaysOnTop"].ToString());
                    mChkBorder = System.Convert.ToBoolean(ds.Tables[mTblName].Rows[0]["chkBorder"].ToString());
                    mChkSound = System.Convert.ToBoolean(ds.Tables[mTblName].Rows[0]["chkSound"].ToString());
                    mFrmOpacity = System.Convert.ToDouble(ds.Tables[mTblName].Rows[0]["frmOpacity"].ToString());
                    mDeskX = System.Convert.ToInt32(ds.Tables[mTblName].Rows[0]["deskX"].ToString());
                    mDeskY = System.Convert.ToInt32(ds.Tables[mTblName].Rows[0]["deskY"].ToString());
                    mIntervalRefr = System.Convert.ToInt32(ds.Tables[mTblName].Rows[0]["intervalRefr"].ToString());
                }
                else
                {
                    DataTable table = new DataTable(mTblName);

                    table.Columns.Add("timeOff", typeof(DateTime));
                    table.Columns.Add("chkOff", typeof(bool));
                    table.Columns.Add("chkGMT", typeof(bool));
                    table.Columns.Add("chkDate", typeof(bool));
                    table.Columns.Add("chkDay", typeof(bool));
                    table.Columns.Add("chkMoving", typeof(bool));
                    table.Columns.Add("chkTransparent", typeof(bool));
                    table.Columns.Add("chkAlwaysOnTop", typeof(bool));
                    table.Columns.Add("chkBorder", typeof(bool));
                    table.Columns.Add("chkSound", typeof(bool));
                    table.Columns.Add("frmOpacity", typeof(double));
                    table.Columns.Add("deskX", typeof(int));
                    table.Columns.Add("deskY", typeof(int));
                    table.Columns.Add("intervalRefr", typeof(int));
                    ds.Tables.Add(table);

                    DataRow dr = ds.Tables[mTblName].NewRow();
                    dr["timeOff"] = cPubFunc.chkTime();
                    dr["chkOff"] = false;
                    dr["chkGMT"] = mChkGMT;
                    dr["chkDate"] = mChkDate;
                    dr["chkDay"] = mChkDay;
                    dr["chkMoving"] = mChkMoving;
                    dr["chkAlwaysOnTop"] = mChkAlwaysOnTop;
                    dr["chkTransparent"] = mChkTransparent;
                    dr["chkBorder"] = mChkBorder;
                    dr["chkSound"] = mChkSound;
                    dr["frmOpacity"] = mFrmOpacity;
                    dr["deskX"] = mDeskX;
                    dr["deskY"] = mDeskY;
                    dr["intervalRefr"] = mIntervalRefr;
                    ds.Tables[mTblName].Rows.Add(dr);

                    ds.WriteXml(@cPubFunc.fileNameSet());
                }
            }
            catch
            {
                throw;
            }

            //mCanClose = false;
            this.Opacity = mFrmOpacity;

            mSizeDefault = 140;                 //this.ClientSize.Width;

            mXCenter = this.ClientSize.Width / 2;
            mYCenter = this.ClientSize.Height / 2;

            mCurDateTime = getCurTime(mChkGMT);

            //mColorBlackWhite = cPubFunc.setColor(mChkIsTransparent);

            // Set to 1 second.
            //timer1.Interval = 1000;
            timer1.Interval = mIntervalRefr;
            // Enable timer.
            timer1.Enabled = true;

            int koefTick = 1000 / timer1.Interval;
            if (koefTick > 1)
                mMaxCountTick = 60 * koefTick;
            else
                mMaxCountTick = 60;

            this.DesktopLocation = new Point(this.mDeskX, this.mDeskY);

            this.TopMost = this.mChkAlwaysOnTop;

        }


        private void startPosition(ref int x, ref int y)
        {
            //Позиционирование
            System.Drawing.Rectangle workingRectangle = Screen.PrimaryScreen.WorkingArea;
            x = workingRectangle.Width - (int)(this.Size.Width + this.Size.Width * 0.2);
            y = workingRectangle.Height - (int)(this.Size.Height + this.Size.Height * 0.2);
            Point tempPoint = new Point(x, y);
            // Set the location of the form using the Point object.
            this.DesktopLocation = tempPoint;
        }
        

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FMain));
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.notifyIcon1 = new System.Windows.Forms.NotifyIcon(this.components);
            this.contextMenu1 = new System.Windows.Forms.ContextMenu();
            this.mSetup = new System.Windows.Forms.MenuItem();
            this.mOpen = new System.Windows.Forms.MenuItem();
            this.menuItem1 = new System.Windows.Forms.MenuItem();
            this.mAbout = new System.Windows.Forms.MenuItem();
            this.menuItem9 = new System.Windows.Forms.MenuItem();
            this.mExit = new System.Windows.Forms.MenuItem();
            this.contextMenuFMain = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.cm_Setup = new System.Windows.Forms.ToolStripMenuItem();
            this.cm_hide = new System.Windows.Forms.ToolStripMenuItem();
            this.cm_StartPosition = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.cm_calendar = new System.Windows.Forms.ToolStripMenuItem();
            this.cm_setShutDownPC = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.cm_about = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.cm_exit = new System.Windows.Forms.ToolStripMenuItem();
            this.contextMenuFMain.SuspendLayout();
            this.SuspendLayout();
            // 
            // timer1
            // 
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // notifyIcon1
            // 
            this.notifyIcon1.ContextMenu = this.contextMenu1;
            this.notifyIcon1.Icon = ((System.Drawing.Icon)(resources.GetObject("notifyIcon1.Icon")));
            this.notifyIcon1.Text = "Clock (.NET)";
            this.notifyIcon1.Visible = true;
            this.notifyIcon1.DoubleClick += new System.EventHandler(this.notifyIcon1_DoubleClick);
            // 
            // contextMenu1
            // 
            this.contextMenu1.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.mSetup,
            this.mOpen,
            this.menuItem1,
            this.mAbout,
            this.menuItem9,
            this.mExit});
            // 
            // mSetup
            // 
            this.mSetup.Index = 0;
            this.mSetup.Text = "Setup...";
            this.mSetup.Click += new System.EventHandler(this.mSetup_Click);
            // 
            // mOpen
            // 
            this.mOpen.Index = 1;
            this.mOpen.Text = "Hide";
            this.mOpen.Click += new System.EventHandler(this.mCMView_Click);
            // 
            // menuItem1
            // 
            this.menuItem1.Index = 2;
            this.menuItem1.Text = "-";
            // 
            // mAbout
            // 
            this.mAbout.Index = 3;
            this.mAbout.Text = "About...";
            this.mAbout.Click += new System.EventHandler(this.menuItem10_Click);
            // 
            // menuItem9
            // 
            this.menuItem9.Index = 4;
            this.menuItem9.Text = "-";
            // 
            // mExit
            // 
            this.mExit.Index = 5;
            this.mExit.Text = "Exit";
            this.mExit.Click += new System.EventHandler(this.menuItem8_Click);
            // 
            // contextMenuFMain
            // 
            this.contextMenuFMain.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.contextMenuFMain.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.cm_Setup,
            this.cm_hide,
            this.cm_StartPosition,
            this.toolStripSeparator3,
            this.cm_calendar,
            this.cm_setShutDownPC,
            this.toolStripSeparator1,
            this.cm_about,
            this.toolStripSeparator2,
            this.cm_exit});
            this.contextMenuFMain.Name = "contextMenuFMain";
            this.contextMenuFMain.Size = new System.Drawing.Size(206, 190);
            // 
            // cm_Setup
            // 
            this.cm_Setup.Name = "cm_Setup";
            this.cm_Setup.Size = new System.Drawing.Size(205, 24);
            this.cm_Setup.Text = "Setup...";
            this.cm_Setup.Click += new System.EventHandler(this.cm_Setup_Click);
            // 
            // cm_hide
            // 
            this.cm_hide.Name = "cm_hide";
            this.cm_hide.Size = new System.Drawing.Size(205, 24);
            this.cm_hide.Text = "Hide";
            this.cm_hide.Click += new System.EventHandler(this.cm_hide_Click);
            // 
            // cm_StartPosition
            // 
            this.cm_StartPosition.Name = "cm_StartPosition";
            this.cm_StartPosition.Size = new System.Drawing.Size(205, 24);
            this.cm_StartPosition.Text = "Start position";
            this.cm_StartPosition.Click += new System.EventHandler(this.cm_StartPosition_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(202, 6);
            // 
            // cm_calendar
            // 
            this.cm_calendar.Name = "cm_calendar";
            this.cm_calendar.Size = new System.Drawing.Size(205, 24);
            this.cm_calendar.Text = "Calendar...";
            this.cm_calendar.Click += new System.EventHandler(this.cm_calendar_Click);
            // 
            // cm_setShutDownPC
            // 
            this.cm_setShutDownPC.Name = "cm_setShutDownPC";
            this.cm_setShutDownPC.Size = new System.Drawing.Size(205, 24);
            this.cm_setShutDownPC.Text = "Set Shut Down PC...";
            this.cm_setShutDownPC.Click += new System.EventHandler(this.cm_setShutDownPC_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(202, 6);
            // 
            // cm_about
            // 
            this.cm_about.Name = "cm_about";
            this.cm_about.Size = new System.Drawing.Size(205, 24);
            this.cm_about.Text = "About...";
            this.cm_about.Click += new System.EventHandler(this.cm_about_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(202, 6);
            // 
            // cm_exit
            // 
            this.cm_exit.Name = "cm_exit";
            this.cm_exit.Size = new System.Drawing.Size(205, 24);
            this.cm_exit.Text = "Exit";
            this.cm_exit.Click += new System.EventHandler(this.cm_exit_Click);
            // 
            // FMain
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(6, 15);
            this.BackColor = System.Drawing.Color.OldLace;
            this.ClientSize = new System.Drawing.Size(168, 162);
            this.ContextMenuStrip = this.contextMenuFMain;
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MinimumSize = new System.Drawing.Size(168, 162);
            this.Name = "FMain";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "Clock";
            this.TransparencyKey = System.Drawing.Color.Transparent;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FMain_FormClosing);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.FMain_MouseDown);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.FMain_MouseMove);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.FMain_MouseUp);
            this.contextMenuFMain.ResumeLayout(false);
            this.ResumeLayout(false);

		}
		#endregion


		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			// Добавляем возможность применнения стилей. 
			Application.EnableVisualStyles();
		    FMain fm = new FMain();
            fm.initialization();
            Application.Run(fm);
		}

		private void setShutdown(bool isShutDown, bool isSleep)
		{
            if (isSleep && (mTimeShutDown != cPubFunc.chkTime()) && (DateTime.Now.ToString("hh:mm").Equals(mTimeShutDown.ToString("hh:mm"))))
            {
                cPubFunc.SetSuspendState(false, true, true);
                return;
            }
            else if (isShutDown && (mTimeShutDown != cPubFunc.chkTime()) && (DateTime.Now.ToString("hh:mm").Equals(mTimeShutDown.ToString("hh:mm"))))
            { 	
                int flag = cPubFunc.Poweroff;
                cPubFunc.DoExitWindows(flag); 
			}
		}

		private void setTimeToTray()
		{
            if (DateTime.Now.Second != 1)
                return;

            string str = this.mCurDateTime.DayOfWeek.ToString();
            str += " - ";
            str += this.mCurDateTime.ToShortTimeString();

            if (mChkGMT)
                str += " GMT";

            notifyIcon1.Text = str; 
		}

        private void closeForm()
		{
			this.Visible = true;
			Application.Exit();
		}

        private void mCMViewClick()
        {
            if (this.Visible == true && mTypeActivate == 1)
            {
                mOpen.Text = "Hide";
                cm_hide.Text = "Hide";
                this.Visible = true;
                mTypeActivate = 2;
            }
            else if (this.Visible == true)
            {
                mOpen.Text = "Open";
                cm_hide.Text = "Open";
                this.Visible = false;
            }
            else
            {
                mOpen.Text = "Hide";
                cm_hide.Text = "Hide";
                this.Visible = true;
            }
        }

        private void mCMView_Click(object sender, System.EventArgs e)
        {
            mCMViewClick();
        }
                        

        private void FMain_MouseDown(object sender, MouseEventArgs e)
        {
            if (mChkMoving)
            {
                msDown = true;
                mOldX = e.X;
                mOldY = e.Y;
            }
        }


        private void FMain_MouseMove(object sender, MouseEventArgs e)
        {
            if (mChkMoving && msDown)
            {
                this.Left = this.Left + e.X - mOldX;
                this.Top = this.Top + e.Y - mOldY;
            }
        }


        private void FMain_MouseUp(object sender, MouseEventArgs e)
        {
            msDown = false;
        }
        

        private void cm_hide_Click(object sender, EventArgs e)
        {
            mOpen.Text = "Open";
            this.Visible = false;
        }


        private void cm_calendar_Click(object sender, EventArgs e)
        {
            FCalendar fcld = new FCalendar();
            fcld.ShowDialog(); 
        }


        private void cm_setShutDownPC_Click(object sender, EventArgs e)
        {
            FShutDown fsd = new FShutDown(mTimeShutDown, mIsShutDown, mIsSleep);
            fsd.ShowDialog();
            mIsShutDown = fsd.isShutDown;
            mIsSleep = fsd.isSleep;

            if (mIsShutDown)
            {
                string str = fsd.tm.ToString("dd.MM.yyyy HH:mm:ss");
                mTimeShutDown = fsd.tm;
                this.cm_setShutDownPC.Checked = true;
            }
            else
            {
                this.cm_setShutDownPC.Checked = false;
            }
        }


        private void cm_about_Click(object sender, EventArgs e)
        {
            frmAbout.FAbout fa = new frmAbout.FAbout();
            fa.ShowDialog();
        }


        private void cm_exit_Click(object sender, EventArgs e)
        {
            closeForm();
        }


        private void menuItem8_Click(object sender, EventArgs e)
        {
            cm_exit_Click(sender, e);
        }


        private void menuItem10_Click(object sender, EventArgs e)
        {
            cm_about_Click(sender, e);
        }


        protected override void OnPaint(PaintEventArgs e)
        {
            e.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighQuality;

            mXCenter = this.ClientSize.Width / 2;
            mYCenter = this.ClientSize.Height / 2;

            int x_beg = (clcX(0, 0, mXCenter) - this.ClientSize.Width / 2) + this.ClientSize.Width / 10;
            int y_beg = (clcY(15, 0, mYCenter) - (this.ClientSize.Height / 2 + (this.ClientSize.Width / 2 - this.ClientSize.Height / 2))) + this.ClientSize.Height / 10;
            int x_end = (this.ClientSize.Width) - this.ClientSize.Width / 5;
            int y_end = (this.ClientSize.Width) - this.ClientSize.Height / 5;

            // Создаем объект GraphicsPath.
            System.Drawing.Drawing2D.GraphicsPath gp = new System.Drawing.Drawing2D.GraphicsPath();
            // Прибавляем два круга.

            int delta = 0;
            if (this.mChkBorder)
                delta = 3;

            gp.AddEllipse(x_beg - delta, y_beg - delta, x_end + delta * 2, y_end + delta * 2);

            // Создаем регион на основе экземпляра GraphicsPath.
            Region r = new Region(gp);
            // Присваиваем созданный регион
            // региону нашего окна.
            this.Region = r;

            try
            {
                //// Копирую текущее содержимое области экрана в ту же обласмт на форме...
                //e.Graphics.CopyFromScreen(new Point(5, 5), new Point(5, 5), new Size(new Point(1000, 20)));
                //// рисую поверх полупрозрачным цветом
                //e.Graphics.FillRectangle(new SolidBrush(Color.FromArgb(100, Color.Black)), new Rectangle(new Point(5, 5), new Size(new Point(1000, 20))));

                if (this.mChkTransparent)
                    e.Graphics.CopyFromScreen(new Point(this.Left, this.Top), new Point(0, 0), new Size(new Point(this.ClientSize.Width * 2, this.ClientSize.Height * 2)));

                this.makeFacePain(e);
                this.makeStringDraw(e);
                this.makeHandsPain(e);

                if (this.mChkBorder)
                {
                    // Create a path and add an ellipse.
                    Rectangle myEllipse = new Rectangle(x_beg, y_beg, x_end, y_end);
                    System.Drawing.Drawing2D.GraphicsPath myPath = new System.Drawing.Drawing2D.GraphicsPath();
                    myPath.AddEllipse(myEllipse);

                    // Draw the path to the screen.
                    Pen myPen = new Pen(Color.Black, 6);
                    e.Graphics.DrawPath(myPen, myPath);
                    myPen = new Pen(Color.Gray, 2);
                    e.Graphics.DrawPath(myPen, myPath);
                }
                ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

                base.OnPaint(e);
            }
            catch { }
        }


        public void drawCircleFloat(PaintEventArgs e, ref Pen penCircle, float x, float y, float width, float height)
        {
            float startAngle = 0.0F;
            float sweepAngle = 360.0F;
            e.Graphics.DrawArc(penCircle, x, y, width, height, startAngle, sweepAngle);
        }


        public void drawLineFloat(PaintEventArgs e, ref Pen penLine, float x_beg, float y_beg, float x_end, float y_end)
        {
            e.Graphics.DrawLine(penLine, x_beg, y_beg, x_end, y_end);
        }


        private void drawString(Graphics g, string s, ref Font f, int x, int y, Brush brush)
        {
            g.DrawString(s, f, brush, x, y);
        }


        private int clcSizeRatio(int defaultSize)
        {
            int clc = 0;
            if (this.ClientSize.Width < this.ClientSize.Height)
                clc = this.ClientSize.Width;
            else
                clc = this.ClientSize.Height;


            clc = (clc * defaultSize / mSizeDefault);
            if (clc <= 0)
                clc = 1;

            return clc;
        }


        private int sizeMin()
        {
            if (this.ClientSize.Width < this.ClientSize.Height)
                return (this.ClientSize.Width / 2);
            else
                return (this.ClientSize.Height / 2);
        }


        /// <summary>
        /// Рисование стрелок часов.
        /// </summary>
        /// <param name="e"></param>
        private void makeHandsPain(PaintEventArgs e)
        {
            //Стрелки
            int sz3 = clcSizeRatio(6);
            pHandHr = new Pen(Color.Black, sz3);         
            int sz = clcSizeRatio(5);
            pHandMin = new Pen(Color.Black, sz);        
            sz = clcSizeRatio(2);
            pHhandSec = new Pen(Color.Red, sz);

            Pen pHhandWhite1 = new Pen(this.BackColor, 1);
            
            //Время            
            //Секунды
            int s = this.mCurDateTime.Second;
            int s2 = this.mCurDateTime.Second + 30;
            int secSize = sizeMin() * 7 / 10;
            int secSize2 = sizeMin() * 1 / 6;
            
            //Минуты
            int m = this.mCurDateTime.Minute;
            int m2 = this.mCurDateTime.Minute + 30;
            int minSize = sizeMin() * 3 / 5;
            int minSize2 = sizeMin() * 1 / 8;

            //Часы
            int h = this.mCurDateTime.Hour;
            int h2 = this.mCurDateTime.Hour + 30;
            int horSize = sizeMin() * 2 / 5;
            int horSize2 = sizeMin() * 1 / 9;

            int xs = clcX(s, secSize, mXCenter);
            int ys = clcY(s, secSize, mYCenter);
            int xs2 = clcX(s2, secSize2, mXCenter);
            int ys2 = clcY(s2, secSize2, mYCenter);

            int xm = clcX(m, minSize, mXCenter);
            int ym = clcY(m, minSize, mYCenter);
            int xm2 = clcX(m2, minSize2, mXCenter);
            int ym2 = clcY(m2, minSize2, mYCenter);

            int xh = clcX(h, m, horSize, mXCenter);
            int yh = clcY(h, m, horSize, mYCenter);
            int xh2 = clcX(h2, m, horSize2, mXCenter);
            int yh2 = clcY(h2, m, horSize2, mYCenter);

            drawLineFloat(e, ref pHandHr, mXCenter, mYCenter, xh, yh);
            drawLineFloat(e, ref pHandHr, mXCenter, mYCenter, xh2, yh2);
            drawLineFloat(e, ref pHhandWhite1, mXCenter, mYCenter, xh, yh);
            drawLineFloat(e, ref pHhandWhite1, mXCenter, mYCenter, xh2, yh2);

            drawLineFloat(e, ref pHandMin, mXCenter, mYCenter, xm, ym);
            drawLineFloat(e, ref pHandMin, mXCenter, mYCenter, xm2, ym2);
            drawLineFloat(e, ref pHhandWhite1, mXCenter, mYCenter, xm, ym);
            drawLineFloat(e, ref pHhandWhite1, mXCenter, mYCenter, xm2, ym2);

            drawLineFloat(e, ref pHhandSec, mXCenter, mYCenter, xs, ys);
            drawLineFloat(e, ref pHhandSec, mXCenter, mYCenter, xs2, ys2);

            sz = clcSizeRatio(3);
            pHhandSec = new Pen(Color.Black, sz);
            drawCircleFloat(e, ref pHhandSec, mXCenter - (sz / 2), mYCenter - (sz / 2), sz, sz);

            sz = clcSizeRatio(1);
            pHhandSec = new Pen(Color.OldLace, sz);
            drawCircleFloat(e, ref pHhandSec, mXCenter - (sz / 2), mYCenter - (sz / 2), sz, sz);
        }


        /// <summary>
        /// Рисование циферблата
        /// </summary>
        /// <param name="e"></param>
        private void makeFacePain(PaintEventArgs e)
        {
            for (int i = 0; i < 60; i++)
            {
                if (i == 0 || i % 15 == 0)
                {
                    pHandMin = new Pen(Color.Black);
                    makeFacePain(e, i, 2, 14, 3, 5);
                    pHandMin = new Pen(Color.OldLace);
                    makeFacePain(e, i, 2, 12, 20);
                }
                else if (i % 5 == 0)
                {
                    pHandMin = new Pen(Color.Black);
                    makeFacePain(e, i, 2, 8, 2, 3);
                    pHandMin = new Pen(Color.OldLace);
                    makeFacePain(e, i, 1, 13, 20);

                }
                else
                {
                    pHandMin = new Pen(Color.Black);
                    makeFacePain(e, i, 1, 15, 20);
                }
            }
        }


        private void makeFacePain(PaintEventArgs e, int min, int size, int clc_ch, int clc_zh)
        {
            int clc = sizeMin() * clc_ch / clc_zh;
            int sz = clcSizeRatio(size);
            pHandMin.Width = sz;
            int x = clcX(min, clc, mXCenter);
            int y = clcY(min, clc, mYCenter);
            drawCircleFloat(e, ref pHandMin, x - (sz / 2), y - (sz / 2), sz, sz);
        }


        private void makeFacePain(PaintEventArgs e, int min, int size, int line, int clc_ch, int clc_zh)
        {
            int clc = sizeMin() * clc_ch / clc_zh;
            int sz = clcSizeRatio(size);
            pHandMin.Width = sz;
            int clcLine = clcSizeRatio(line);
            int x_beg = clcX(min, clc, mXCenter);
            int y_beg = clcY(min, clc, mYCenter);
            int x_end = clcX(min, (clc + clcLine), mXCenter);
            int y_end = clcY(min, (clc + clcLine), mYCenter);

            drawLineFloat(e, ref pHandMin, x_beg, y_beg, x_end, y_end);
        }


        private void timer1_Tick(object sender, System.EventArgs e)
        {
            mCurDateTime = getCurTime(mChkGMT);
            
            setTimeToTray();
            
            // Обработка отключения
            setShutdown(this.mIsShutDown, this.mIsSleep);
            
            if (++mClcTick > mMaxCountTick)
            {
                mClcTick = 0;
                GC.Collect();
            }

            this.Refresh();
        }
        

        private void makeStringDraw(PaintEventArgs e)
        {
            int x, y, clc;

            Font f = new Font(Font.FontFamily, clcSizeRatio(1));

            string str = "LN";
            f = new Font(Font.FontFamily, clcSizeRatio(10), FontStyle.Italic | FontStyle.Underline);
            SizeF stringSize = e.Graphics.MeasureString(str, f);
            clc = sizeMin() * 2 / 5;
            x = clcX(0, clc, mXCenter);
            y = clcY(0, clc, mYCenter);
            x -= (int)stringSize.Width / 2;
            drawString(e.Graphics, str, ref f, x, y, Brushes.LightCoral);


            if (mChkDay)
            {
                //День недели
                str = this.mCurDateTime.DayOfWeek.ToString();
                f = new Font(Font.FontFamily, clcSizeRatio(6), FontStyle.Bold);
                stringSize = e.Graphics.MeasureString(str, f);
                clc = sizeMin() * 1 / 10;
                x = clcX(30, clc, mXCenter);
                y = clcY(30, clc, mYCenter);
                x -= (int)stringSize.Width / 2;

                if (this.mCurDateTime.DayOfWeek == System.DayOfWeek.Saturday || this.mCurDateTime.DayOfWeek == System.DayOfWeek.Sunday)
                    drawString(e.Graphics, str, ref f, x, y, Brushes.Red);
                else
                    drawString(e.Graphics, str, ref f, x, y, Brushes.SaddleBrown);  
            }


            if (mChkDate)
            {
                //Дата
                str = this.mCurDateTime.ToShortDateString();
                f = new Font(Font.FontFamily, clcSizeRatio(6), FontStyle.Bold);
                stringSize = e.Graphics.MeasureString(str, f);
                clc = sizeMin() * 5 / 21;
                x = clcX(30, clc, mXCenter);
                y = clcY(30, clc, mYCenter);
                x -= (int)stringSize.Width / 2;
                drawString(e.Graphics, str, ref f, x, y, Brushes.SteelBlue);
            }


            if (mChkGMT)
            {
                str = "GMT";
                f = new Font(Font.FontFamily, clcSizeRatio(6), FontStyle.Bold);
                stringSize = e.Graphics.MeasureString(str, f);
                clc = sizeMin() * 9 / 20;
                x = clcX(30, clc, mXCenter);
                y = clcY(30, clc, mYCenter);
                x = x - (int)stringSize.Width / 2;
                drawString(e.Graphics, str, ref f, x, y, Brushes.Olive);
            }
        }


        private int clcX(int sec, int size, int xCenter)
        {
            return ((int)(Math.Cos(sec * Math.PI / 30 - Math.PI / 2) * size + xCenter));
        }


        private int clcY(int sec, int size, int yCenter)
        {
            return ((int)(Math.Sin(sec * Math.PI / 30 - Math.PI / 2) * size + yCenter));
        }


        private int clcX(int hour, int min, int size, int xCenter)
        {
            return ((int)(Math.Cos((hour * 30 + min / 2) * Math.PI / 180 - Math.PI / 2) * size + xCenter));
        }


        private int clcY(int hour, int min, int size, int yCenter)
        {
            return ((int)(Math.Sin((hour * 30 + min / 2) * Math.PI / 180 - Math.PI / 2) * size + yCenter));
        }

        
        private DateTime getCurTime(bool isGmt)
        {
            if (isGmt)
                return (DateTime.UtcNow);
            else
                return (DateTime.Now);
        }


        private void notifyIcon1_DoubleClick(object sender, EventArgs e)
        {
            mCMViewClick();
        }


        private void cm_SetupClick()
        {
            FSetup fs = new FSetup();
            fs.initialization(mChkGMT, mChkDate, mChkDay, mChkMoving, mChkAlwaysOnTop, mChkTransparent, mChkBorder, mChkSound, Opacity);
            fs.ShowDialog();

            if (fs.mClose <= 0)
                return;

            try
            {
                this.mChkGMT = fs.mChkGMT;
                this.mChkDate = fs.mChkDate;
                this.mChkDay = fs.mChkDay;
                this.mChkMoving = fs.mChkMoving;
                this.mChkAlwaysOnTop = fs.mChkAlwaysOnTop;
                this.mChkTransparent = fs.mChkTransparent;
                this.mChkBorder = fs.mChkBorder;
                this.TopMost = this.mChkAlwaysOnTop;
                this.mChkSound = fs.mChkSound;
                this.Opacity = fs.mValOpacity;

                ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                DataSet ds = new DataSet();
                ds.ReadXml(@cPubFunc.fileNameSet());
                ds.Tables[mTblName].Rows[0]["chkGMT"] = this.mChkGMT;
                ds.Tables[mTblName].Rows[0]["chkDate"] = this.mChkDate;
                ds.Tables[mTblName].Rows[0]["chkDay"] = this.mChkDay;
                ds.Tables[mTblName].Rows[0]["chkMoving"] = this.mChkMoving;
                ds.Tables[mTblName].Rows[0]["chkAlwaysOnTop"] = this.mChkAlwaysOnTop;
                ds.Tables[mTblName].Rows[0]["chkTransparent"] = this.mChkTransparent;
                ds.Tables[mTblName].Rows[0]["chkBorder"] = this.mChkBorder;

                if(cPubFunc.existsTickTackWav())
                    ds.Tables[mTblName].Rows[0]["chkSound"] = false;
                else
                    ds.Tables[mTblName].Rows[0]["chkSound"] = this.mChkSound;
                
                ds.Tables[mTblName].Rows[0]["frmOpacity"] = this.Opacity;
                ds.WriteXml(@cPubFunc.fileNameSet());
                ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            }
            catch { }
        }


        private void cm_Setup_Click(object sender, EventArgs e)
        {
            cm_SetupClick();
        }

        private void cm_StartPosition_Click(object sender, EventArgs e)
        {
            startPosition(ref mDeskX, ref mDeskY);
        }

        private void mSetup_Click(object sender, EventArgs e)
        {
            cm_SetupClick();
        }

        private void FMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
                DataSet ds = new DataSet();
                ds.ReadXml(@cPubFunc.fileNameSet());
                ds.Tables[mTblName].Rows[0]["deskX"] = this.Left;
                ds.Tables[mTblName].Rows[0]["deskY"] = this.Top;
                ds.WriteXml(@cPubFunc.fileNameSet());
            }
            catch { }
        }



	}

}
