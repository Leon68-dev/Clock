using System;
using System.Collections.Generic;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Text;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Clock_csc_v2
{
    public partial class FMain : Form
    {
        // --- Змінні для оптимізації пам'яті ---
        private Bitmap _backBuffer = null;
        private Graphics _gBuffer = null;

        // Кешовані об'єкти малювання
        private Pen _penBlack, _penGray, _penHour, _penQuarter, _penSec;
        private SolidBrush _brushFace, _brushBlack, _brushLN, _brushCS, _brushDate, _brushDayNormal, _brushDayRed, _brushUTC;
        private Font _fontLN, _fontText;
        private StringFormat _sfCenter;

        // --- Змінні стану ---
        private int lastSecond = -1;
        private FWorldMap _frmMap = null;
        private Point mLastMousePos;
        private bool mIsMouseDown = false;
        private const string TBL_NAME = "clock_csc_v2";
        private int mDeskX, mDeskY;

        private DateTime mCurDateTime;
        private DateTime mTimeShutDown;
        private bool mIsShutDown;
        private bool mIsSleep = false;

        // Налаштування
        private bool mChkGMT = false;
        private bool mChkDate = true;
        private bool mChkDay = true;
        private bool mChkMoving = true;
        private bool mChkAlwaysOnTop = false;
        private bool mChkTransparent = false;
        private bool mChkBorder = true;
        private int mFrmOpacity = 80;
        private bool mChkSmooth = true;
        private bool mChkTickTack = false;
        private bool mChk1530 = false;
        private bool mChkHours = false;

        public FMain()
        {
            InitializeComponent();
            this.FormBorderStyle = FormBorderStyle.None;
            this.ShowInTaskbar = false;
            this.StartPosition = FormStartPosition.Manual;
            this.BackColor = Color.Magenta;
            this.TransparencyKey = Color.Empty;

            _sfCenter = new StringFormat 
            { 
                Alignment = StringAlignment.Center, 
                LineAlignment = StringAlignment.Center 
            };
        }

        protected override CreateParams CreateParams
        {
            get
            {
                CreateParams cp = base.CreateParams;
                cp.ExStyle |= 0x80000 | 0x80; // WS_EX_LAYERED | WS_EX_TOOLWINDOW
                return cp;
            }
        }

        public void initialization()
        {
            LoadSettings();

            this.MinimumSize = new Size(0, 0);
            this.Size = new Size(134, 134);

            if (mDeskX == 0 && mDeskY == 0)
                startPosition(ref mDeskX, ref mDeskY);

            this.Location = new Point(mDeskX, mDeskY);
            this.TopMost = mChkAlwaysOnTop;

            // Ініціалізація кешованих ресурсів
            InitResources();

            timer1.Interval = mChkSmooth ? 200 : 1000;
            timer1.Enabled = true;

            mTimeShutDown = cPubFunc.chkTime();
            mCurDateTime = getCurTime(mChkGMT);

            string str = Environment.ExpandEnvironmentVariables("%SystemRoot%");
            cPubFunc.playSound(@str + @"\Media\tada.wav");

            UpdateLayeredClock();
        }

        private void InitResources()
        {
            // Очищення старих ресурсів, якщо вони були
            _penBlack?.Dispose(); 
            _penGray?.Dispose(); 
            _penHour?.Dispose(); 
            _penQuarter?.Dispose(); 
            _penSec?.Dispose();
            _brushFace?.Dispose(); 
            _brushBlack?.Dispose(); 
            _brushLN?.Dispose(); 
            _brushCS?.Dispose();
            _brushDate?.Dispose(); 
            _brushDayNormal?.Dispose(); 
            _brushDayRed?.Dispose(); 
            _brushUTC?.Dispose();
            _fontLN?.Dispose(); 
            _fontText?.Dispose();

            float radius = Math.Min(this.Width, this.Height) / 2.0f;
            float borderThickness = 6.0f;
            float innerRadius = radius - borderThickness - 1.5f;

            // Створення нових ресурсів
            _penBlack = new Pen(Color.Black, borderThickness);
            _penGray = new Pen(Color.Gray, 2.0f);
            _penHour = new Pen(Color.Black, 2.0f);
            _penQuarter = new Pen(Color.Black, 4.0f);
            _penSec = new Pen(Color.Red, 1.5f);

            _brushFace = new SolidBrush(Color.FromArgb(255, 242, 238, 225));
            _brushBlack = new SolidBrush(Color.Black);
            _brushLN = new SolidBrush(Color.Gray);
            _brushCS = new SolidBrush(Color.Gray);
            _brushDate = new SolidBrush(Color.Gray);
            _brushDayNormal = new SolidBrush(Color.Gray);
            _brushDayRed = new SolidBrush(Color.RosyBrown);
            _brushUTC = new SolidBrush(Color.Gray);

            _fontLN = new Font("Arial", innerRadius * 0.2f, FontStyle.Italic | FontStyle.Underline);
            _fontText = new Font("Arial", innerRadius * 0.11f, FontStyle.Bold);

            // Підготовка буфера
            if (_backBuffer == null || _backBuffer.Width != this.Width || _backBuffer.Height != this.Height)
            {
                _backBuffer?.Dispose();
                _gBuffer?.Dispose();
                _backBuffer = new Bitmap(this.Width, this.Height, System.Drawing.Imaging.PixelFormat.Format32bppArgb);
                _gBuffer = Graphics.FromImage(_backBuffer);
                _gBuffer.SmoothingMode = SmoothingMode.HighQuality;
                _gBuffer.PixelOffsetMode = PixelOffsetMode.HighQuality;
                _gBuffer.TextRenderingHint = TextRenderingHint.AntiAlias;
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            mCurDateTime = getCurTime(mChkGMT);
            UpdateLayeredClock();

            if (mCurDateTime.Second != lastSecond)
            {
                lastSecond = mCurDateTime.Second;
                setTimeToTray();
                setShutdown(mIsShutDown, mIsSleep);

                if (mCurDateTime.Minute == 8 && mCurDateTime.Second == 48)
                    GC.Collect();

                bool isLongSoundPlaying = cPubFunc.isPlayingMCI("hours") || cPubFunc.isPlayingMCI("chime");

                if (mChkHours && mCurDateTime.Minute == 0 && mCurDateTime.Second == 0)
                {
                    int count = mCurDateTime.Hour % 12;
                    if (count == 0) 
                        count = 12;

                    Task.Run(() =>
                    {
                        string file = cPubFunc.getFileNameWav("_Boom.wav");
                        for (int i = 0; i < count; i++)
                        {
                            cPubFunc.playMCI(file, "hours");
                            
                            while (cPubFunc.isPlayingMCI("hours")) 
                                Thread.Sleep(50);
                            
                            Thread.Sleep(200);
                        }
                    });
                }

                if (mChk1530 && mCurDateTime.Second == 0)
                {
                    int min = mCurDateTime.Minute;
                    if (min == 15 || min == 45)
                        cPubFunc.playMCI(cPubFunc.getFileNameWav("_15.wav"), "chime");
                    else if (min == 30)
                        cPubFunc.playMCI(cPubFunc.getFileNameWav("_30.wav"), "chime");
                }

                if (mChkTickTack)
                {
                    if (!isLongSoundPlaying && mCurDateTime.Second % 2 == 0)
                        cPubFunc.playMCI(cPubFunc.getFileNameWav("_TickTack.wav"), "tick");
                }
                else
                {
                    cPubFunc.stopMCI("tick");
                }
            }
        }

        private void UpdateLayeredClock()
        {
            if (_backBuffer == null || _gBuffer == null) return;

            _gBuffer.Clear(Color.Transparent);
            DrawClock(_gBuffer);

            IntPtr screenDc = Win32.GetDC(IntPtr.Zero);
            IntPtr memDc = Win32.CreateCompatibleDC(screenDc);
            IntPtr hBitmap = IntPtr.Zero;
            IntPtr oldBitmap = IntPtr.Zero;

            try
            {
                hBitmap = _backBuffer.GetHbitmap(Color.FromArgb(0));
                oldBitmap = Win32.SelectObject(memDc, hBitmap);

                Win32.Size size = new Win32.Size(this.Width, this.Height);
                Win32.Point pointSource = new Win32.Point(0, 0);
                Win32.Point topPos = new Win32.Point(this.Left, this.Top);
                Win32.BLENDFUNCTION blend = new Win32.BLENDFUNCTION
                {
                    BlendOp = Win32.AC_SRC_OVER,
                    BlendFlags = 0,
                    SourceConstantAlpha = (byte)((255 * mFrmOpacity) / 100),
                    AlphaFormat = Win32.AC_SRC_ALPHA
                };

                Win32.UpdateLayeredWindow(this.Handle, screenDc, ref topPos, ref size, memDc, ref pointSource, 0, ref blend, Win32.ULW_ALPHA);
            }
            finally
            {
                Win32.ReleaseDC(IntPtr.Zero, screenDc);
                if (hBitmap != IntPtr.Zero)
                {
                    Win32.SelectObject(memDc, oldBitmap);
                    Win32.DeleteObject(hBitmap);
                }
                Win32.DeleteDC(memDc);
            }
        }

        private void DrawClock(Graphics g)
        {
            float xCenter = this.Width / 2.0f;
            float yCenter = this.Height / 2.0f;
            float radius = Math.Min(this.Width, this.Height) / 2.0f;
            float borderThickness = 6.0f;

            if (!mChkTransparent)
                g.FillEllipse(_brushFace, 0, 0, this.Width, this.Height);

            if (mChkBorder)
            {
                RectangleF penRect = new RectangleF(0, 0, this.Width, this.Height);
                float inset = borderThickness / 2.0f;
                penRect.Inflate(-inset, -inset);
                g.DrawEllipse(_penBlack, penRect);
                g.DrawEllipse(_penGray, penRect);
            }

            float innerRadius = radius - borderThickness - 1.5f;

            // Поділки
            for (int i = 0; i < 60; i++)
            {
                double angle = i * Math.PI / 30.0 - Math.PI / 2.0;
                float cos = (float)Math.Cos(angle);
                float sin = (float)Math.Sin(angle);
                if (i % 5 == 0)
                {
                    float len = /* (i % 15 == 0) ? innerRadius * 0.22f : */ innerRadius * 0.15f;
                    Pen p = (i % 15 == 0) ? _penQuarter : _penHour;
                    g.DrawLine(p, xCenter + cos * (innerRadius - len), yCenter + sin * (innerRadius - len), xCenter + cos * (innerRadius + 3.0f), yCenter + sin * (innerRadius + 3.0f));
                    float markDotR = 1.5f;
                    g.FillEllipse(_brushFace, xCenter + cos * (innerRadius - len) - markDotR, yCenter + sin * (innerRadius - len) - markDotR, markDotR * 2, markDotR * 2);
                }
                else
                {
                    float dotR = 1.3f;
                    g.FillEllipse(_brushBlack, xCenter + cos * (innerRadius + 1.5f) - dotR, yCenter + sin * (innerRadius + 1.5f) - dotR, dotR * 2, dotR * 2);
                }
            }

            // Текст
            g.DrawString("LAN", _fontLN, _brushLN, xCenter, yCenter - innerRadius * 0.52f, _sfCenter);
            g.DrawString("C#", _fontText, _brushCS, xCenter, yCenter + 16.0f - innerRadius * 0.52f, _sfCenter);

            float yDelta = 5.0f;
            if (mChkDay)
            {
                Brush bDay = (mCurDateTime.DayOfWeek == DayOfWeek.Saturday || mCurDateTime.DayOfWeek == DayOfWeek.Sunday) ? _brushDayRed : _brushDayNormal;
                g.DrawString(mCurDateTime.ToString("ddd", System.Globalization.CultureInfo.InvariantCulture).ToUpper(),
                    _fontText, bDay, xCenter, yCenter + yDelta + innerRadius * 0.12f, _sfCenter);
            }

            if (mChkDate)
                g.DrawString(mCurDateTime.ToString("dd-MM-yy"), _fontText, _brushDate, xCenter, yCenter + yDelta + innerRadius * 0.35f, _sfCenter);

            if (mChkGMT)
                g.DrawString("GMT", _fontText, _brushUTC, xCenter, yCenter + yDelta + innerRadius * 0.58f, _sfCenter);

            // СТРІЛКИ
            float fSeconds = mChkSmooth ? (mCurDateTime.Second + mCurDateTime.Millisecond / 1000.0f) : mCurDateTime.Second;
            float fMinutes = mCurDateTime.Minute + fSeconds / 60.0f;
            float fHours = (mCurDateTime.Hour % 12 + fMinutes / 60.0f) * 5.0f;

            DrawHand(g, xCenter, yCenter, fHours, innerRadius * 0.58f, 6.5f, true);
            DrawHand(g, xCenter, yCenter, fMinutes, innerRadius * 0.85f, 4.5f, true);

            float sAngle = (float)(fSeconds * Math.PI / 30.0 - Math.PI / 2.0);
            float cosS = (float)Math.Cos(sAngle);
            float sinS = (float)Math.Sin(sAngle);
            g.DrawLine(_penSec, xCenter - cosS * (innerRadius * 0.15f), yCenter - sinS * (innerRadius * 0.15f), xCenter + cosS * (innerRadius * 0.95f), yCenter + sinS * (innerRadius * 0.95f));

            g.FillEllipse(_brushBlack, xCenter - 4, yCenter - 4, 8, 8);
        }

        private void DrawHand(Graphics g, float xc, float yc, float val, float len, float width, bool whiteLine)
        {
            double angle = val * Math.PI / 30.0 - Math.PI / 2.0;
            float x = xc + (float)Math.Cos(angle) * len;
            float y = yc + (float)Math.Sin(angle) * len;

            using (Pen pBlack = new Pen(Color.Black, width) { StartCap = LineCap.Round, EndCap = LineCap.Round })
                g.DrawLine(pBlack, xc, yc, x, y);

            if (whiteLine)
                using (Pen pWhite = new Pen(Color.White, width / 2.2f) { StartCap = LineCap.Round, EndCap = LineCap.Round })
                    g.DrawLine(pWhite, xc, yc, x, y);
        }

        private void FMain_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left && mChkMoving) 
            { 
                mIsMouseDown = true; 
                mLastMousePos = e.Location; 
            }
            
            if (e.Button == MouseButtons.Right && contextMenuFMain != null) 
                contextMenuFMain.Show(Cursor.Position);
        }

        private void FMain_MouseMove(object sender, MouseEventArgs e)
        {
            if (mIsMouseDown && mChkMoving)
            {
                this.Location = new Point(this.Left + (e.X - mLastMousePos.X), this.Top + (e.Y - mLastMousePos.Y));
                UpdateLayeredClock();
            }
        }

        private void FMain_MouseUp(object sender, MouseEventArgs e)
        {
            mIsMouseDown = false;
            if (mChkMoving) 
            { 
                mDeskX = this.Left; 
                mDeskY = this.Top; 
                SaveSettings(); 
            }
        }

        private void LoadSettings()
        {
            DataSet ds = new DataSet();
            try
            {
                string filename = cPubFunc.fileNameSet();
                if (File.Exists(filename))
                {
                    ds.ReadXml(filename);
                    DataRow dr = ds.Tables[TBL_NAME].Rows[0];
                    if (dr.Table.Columns.Contains("timeOff")) 
                        mTimeShutDown = Convert.ToDateTime(dr["timeOff"]);
                    if (dr.Table.Columns.Contains("chkOff")) 
                        mIsShutDown = Convert.ToBoolean(dr["chkOff"]);
                    if (dr.Table.Columns.Contains("chkGMT")) 
                        mChkGMT = Convert.ToBoolean(dr["chkGMT"]);
                    if (dr.Table.Columns.Contains("chkDate")) 
                        mChkDate = Convert.ToBoolean(dr["chkDate"]);
                    if (dr.Table.Columns.Contains("chkDay")) 
                        mChkDay = Convert.ToBoolean(dr["chkDay"]);
                    if (dr.Table.Columns.Contains("chkMoving")) 
                        mChkMoving = Convert.ToBoolean(dr["chkMoving"]);
                    if (dr.Table.Columns.Contains("chkTransparent")) 
                        mChkTransparent = Convert.ToBoolean(dr["chkTransparent"]);
                    if (dr.Table.Columns.Contains("chkAlwaysOnTop")) 
                        mChkAlwaysOnTop = Convert.ToBoolean(dr["chkAlwaysOnTop"]);
                    if (dr.Table.Columns.Contains("chkBorder")) 
                        mChkBorder = Convert.ToBoolean(dr["chkBorder"]);
                    if (dr.Table.Columns.Contains("frmOpacity")) 
                        mFrmOpacity = Convert.ToInt32(dr["frmOpacity"]);
                    if (dr.Table.Columns.Contains("deskX")) 
                        mDeskX = Convert.ToInt32(dr["deskX"]);
                    if (dr.Table.Columns.Contains("deskY")) 
                        mDeskY = Convert.ToInt32(dr["deskY"]);
                    if (dr.Table.Columns.Contains("chkSmooth")) 
                        mChkSmooth = Convert.ToBoolean(dr["chkSmooth"]);
                    if (dr.Table.Columns.Contains("chkHours")) 
                        mChkHours = Convert.ToBoolean(dr["chkHours"]);
                    if (dr.Table.Columns.Contains("chk1530")) 
                        mChk1530 = Convert.ToBoolean(dr["chk1530"]);
                    if (dr.Table.Columns.Contains("chkTickTack")) 
                        mChkTickTack = Convert.ToBoolean(dr["chkTickTack"]);
                }
                else
                {
                    DataTable table = new DataTable(TBL_NAME);
                    table.Columns.Add("timeOff", typeof(DateTime)); table.Columns.Add("chkOff", typeof(bool));
                    table.Columns.Add("chkGMT", typeof(bool)); table.Columns.Add("chkDate", typeof(bool));
                    table.Columns.Add("chkDay", typeof(bool)); table.Columns.Add("chkMoving", typeof(bool));
                    table.Columns.Add("chkTransparent", typeof(bool)); table.Columns.Add("chkAlwaysOnTop", typeof(bool));
                    table.Columns.Add("chkBorder", typeof(bool)); table.Columns.Add("frmOpacity", typeof(int));
                    table.Columns.Add("deskX", typeof(int)); table.Columns.Add("deskY", typeof(int));
                    table.Columns.Add("chkSmooth", typeof(bool)); table.Columns.Add("chkHours", typeof(bool));
                    table.Columns.Add("chk1530", typeof(bool)); table.Columns.Add("chkTickTack", typeof(bool));
                    ds.Tables.Add(table);
                    
                    DataRow dr = ds.Tables[TBL_NAME].NewRow();
                    dr["timeOff"] = DateTime.Now; 
                    dr["chkOff"] = false; 
                    dr["chkGMT"] = false;
                    dr["chkDate"] = true; 
                    dr["chkDay"] = true; 
                    dr["chkMoving"] = true;
                    dr["chkTransparent"] = false; 
                    dr["chkAlwaysOnTop"] = false; 
                    dr["chkBorder"] = true;
                    dr["frmOpacity"] = 80; 
                    dr["deskX"] = 0; 
                    dr["deskY"] = 0;
                    dr["chkSmooth"] = mChkSmooth; 
                    dr["chkHours"] = false; 
                    dr["chk1530"] = false; 
                    dr["chkTickTack"] = false;
                    ds.Tables[TBL_NAME].Rows.Add(dr);
                    ds.WriteXml(filename);
                }
            }
            catch { }
        }

        private void SaveSettings()
        {
            try
            {
                DataSet ds = new DataSet();
                ds.ReadXml(cPubFunc.fileNameSet());
                DataRow dr = ds.Tables[TBL_NAME].Rows[0];
                dr["chkGMT"] = mChkGMT; 
                dr["chkDate"] = mChkDate; 
                dr["chkDay"] = mChkDay;
                dr["chkMoving"] = mChkMoving; 
                dr["chkAlwaysOnTop"] = mChkAlwaysOnTop;
                dr["chkTransparent"] = mChkTransparent; 
                dr["chkBorder"] = mChkBorder;
                dr["frmOpacity"] = mFrmOpacity; 
                dr["deskX"] = this.Left; 
                dr["deskY"] = this.Top;
                dr["chkSmooth"] = this.mChkSmooth; 
                dr["chkHours"] = mChkHours;
                dr["chk1530"] = mChk1530; 
                dr["chkTickTack"] = mChkTickTack;
                ds.WriteXml(cPubFunc.fileNameSet());
            }
            catch { }
        }

        private DateTime getCurTime(bool isGmt) => isGmt ? DateTime.UtcNow : DateTime.Now;

        private void startPosition(ref int x, ref int y)
        {
            Rectangle wa = Screen.PrimaryScreen.WorkingArea;
            x = wa.Width - (int)(this.Width * 1.2);
            y = wa.Height - (int)(this.Height * 1.2);
        }

        private void setTimeToTray()
        {
            string str = mCurDateTime.DayOfWeek.ToString() + " - " + mCurDateTime.ToShortTimeString();
            if (mChkGMT) 
                str += " GMT";
            notifyIcon1.Text = str;
        }

        private void setShutdown(bool isShutDown, bool isSleep)
        {
            if ((isSleep || isShutDown) && DateTime.Now.ToString("HH:mm") == mTimeShutDown.ToString("HH:mm"))
            {
                if (isSleep) 
                    cPubFunc.SetSuspendState(false, true, true);
                else 
                    cPubFunc.DoExitWindows(cPubFunc.Poweroff);
            }
        }

        private void cm_SetupClick()
        {
            FSetup fs = new FSetup();
            fs.initialization(mChkGMT, mChkDate, mChkDay, mChkMoving, mChkAlwaysOnTop, mChkTransparent,
                mChkBorder, mFrmOpacity, mChkSmooth, mChkTickTack, mChk1530, mChkHours);
            fs.ShowDialog();
            
            if (fs.mClose <= 0) 
                return;
            
            mChkGMT = fs.mChkGMT; 
            mChkDate = fs.mChkDate; 
            mChkDay = fs.mChkDay; 
            mChkMoving = fs.mChkMoving;
            mChkAlwaysOnTop = fs.mChkAlwaysOnTop; 
            mChkTransparent = fs.mChkTransparent; 
            mChkBorder = fs.mChkBorder;
            mFrmOpacity = fs.mValOpacity; 
            this.TopMost = mChkAlwaysOnTop;
            mChkSmooth = fs.mChkSmooth; 
            mChkTickTack = fs.mChkTickTak; 
            mChk1530 = fs.mChk1530; 
            mChkHours = fs.mChkHours;
            timer1.Interval = mChkSmooth ? 200 : 1000;
            InitResources(); // Оновлюємо кеш при зміні налаштувань
            UpdateLayeredClock(); 
            SaveSettings();
        }

        private void cm_Setup_Click(object sender, EventArgs e) => cm_SetupClick();
        private void cm_StartPosition_Click(object sender, EventArgs e) 
        { 
            startPosition(ref mDeskX, ref mDeskY); 
            this.Location = new Point(mDeskX, mDeskY); 
            UpdateLayeredClock(); 
        }
        private void cm_hide_Click(object sender, EventArgs e) => this.Visible = false;
        private void cm_calendar_Click(object sender, EventArgs e) => new FCalendar().ShowDialog();
        private void cm_setShutDownPC_Click(object sender, EventArgs e)
        {
            FShutDown fsd = new FShutDown(mTimeShutDown, mIsShutDown, mIsSleep);
            if (fsd.ShowDialog() == DialogResult.OK) 
            { 
                mIsShutDown = fsd.isShutDown; 
                mIsSleep = fsd.isSleep; 
                mTimeShutDown = fsd.tm; 
                cm_setShutDownPC.Checked = mIsShutDown; 
            }
        }
        private void cm_about_Click(object sender, EventArgs e) => new FAbout().ShowDialog();
        private void cm_exit_Click(object sender, EventArgs e) 
        { 
            SaveSettings(); 
            Application.Exit(); 
        }
        private void mCMViewClick() 
        { 
            if (this.Visible) 
                this.Visible = false; 
            else 
            { 
                this.Visible = true; 
                this.Activate(); 
            } 
        }
        private void notifyIcon1_DoubleClick(object sender, EventArgs e) => mCMViewClick();
        private void m_Open_Click(object sender, EventArgs e) => mCMViewClick();
        private void m_Setup_Click(object sender, EventArgs e) => cm_SetupClick();
        private void m_About_Click(object sender, EventArgs e) => cm_about_Click(sender, e);
        private void m_Exit_Click(object sender, EventArgs e) => cm_exit_Click(sender, e);
        
        private void FMain_FormClosing(object sender, FormClosingEventArgs e) 
        { 
            SaveSettings(); 
            _backBuffer?.Dispose(); 
            _gBuffer?.Dispose(); 
        }

        private void cm_world_map_Click(object sender, EventArgs e)
        {
            if (_frmMap == null || _frmMap.IsDisposed) 
            { 
                _frmMap = new FWorldMap(); 
                _frmMap.Show(); 
            }
            else 
            { 
                _frmMap.Activate(); 
                if (_frmMap.WindowState == FormWindowState.Minimized) 
                    _frmMap.WindowState = FormWindowState.Normal; 
            }
        }
    }

    internal static class Win32
    {
        public const int ULW_ALPHA = 0x00000002;
        public const byte AC_SRC_OVER = 0x00;
        public const byte AC_SRC_ALPHA = 0x01;
        [StructLayout(LayoutKind.Sequential)] 
        public struct Point { public int x; public int y; public Point(int x, int y) { this.x = x; this.y = y; } }
        [StructLayout(LayoutKind.Sequential)] 
        public struct Size { public int cx; public int cy; public Size(int cx, int cy) { this.cx = cx; this.cy = cy; } }
        [StructLayout(LayoutKind.Sequential)] 
        public struct BLENDFUNCTION { public byte BlendOp; public byte BlendFlags; public byte SourceConstantAlpha; public byte AlphaFormat; }
        [DllImport("user32.dll")] 
        public static extern bool UpdateLayeredWindow(IntPtr hwnd, IntPtr hdcDst, ref Point pptDst, ref Size psize, IntPtr hdcSrc, ref Point pptSrc, int crKey, ref BLENDFUNCTION pblend, int dwFlags);
        [DllImport("user32.dll")] 
        public static extern IntPtr GetDC(IntPtr hWnd);
        [DllImport("user32.dll")] 
        public static extern int ReleaseDC(IntPtr hWnd, IntPtr hDC);
        [DllImport("gdi32.dll")] 
        public static extern IntPtr CreateCompatibleDC(IntPtr hDC);
        [DllImport("gdi32.dll")] 
        public static extern bool DeleteDC(IntPtr hdc);
        [DllImport("gdi32.dll")] 
        public static extern IntPtr SelectObject(IntPtr hDC, IntPtr hObject);
        [DllImport("gdi32.dll")] 
        public static extern bool DeleteObject(IntPtr hObject);
    }
}