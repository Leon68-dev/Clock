using System;
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
        // --- Змінні ---
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
        private bool mChkSound = false;
        private int mFrmOpacity = 80;
        private int mIntervalRefr = 1000;

        private CancellationTokenSource cts = new CancellationTokenSource();
        private bool _isRuning = false;

        public FMain()
        {
            InitializeComponent();

            // Важливі налаштування вікна
            this.FormBorderStyle = FormBorderStyle.None;
            this.ShowInTaskbar = false;
            this.StartPosition = FormStartPosition.Manual;
            this.BackColor = Color.Magenta; // Колір для відладки (не має бути видно)
            this.TransparencyKey = Color.Empty; // Вимикаємо стандартну прозорість
        }

        // Вмикаємо Layered Window
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
            this.MinimumSize = new Size(0, 0);
            this.Size = new Size(134, 134);

            startPosition(ref mDeskX, ref mDeskY);
            mTimeShutDown = cPubFunc.chkTime();

            string str = Environment.ExpandEnvironmentVariables("%SystemRoot%");
            cPubFunc.playSound(@str + @"\Media\tada.wav");

            LoadSettings();

            mCurDateTime = getCurTime(mChkGMT);
            timer1.Interval = mIntervalRefr;
            timer1.Enabled = true;

            this.Location = new Point(mDeskX, mDeskY);
            this.TopMost = mChkAlwaysOnTop;

            UpdateLayeredClock();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            mCurDateTime = getCurTime(mChkGMT);
            UpdateLayeredClock();
            setTimeToTray();
            setShutdown(mIsShutDown, mIsSleep);

            if (mCurDateTime.Minute == 8 && mCurDateTime.Second == 48) GC.Collect();

            if (mChkSound)
            {
                if (mCurDateTime.Minute == 0 && mCurDateTime.Second == 0)
                {
                    int hours = mCurDateTime.Hour;
                    if (hours > 12) hours -= 12;
                    if (hours == 0) hours = 12;
                    for (int i = 0; i < hours; i++) playSound(cPubFunc.getFileNameWav("_Boom.wav"));
                }
                else if ((mCurDateTime.Minute == 15 || mCurDateTime.Minute == 45) && mCurDateTime.Second == 0)
                    playSound(cPubFunc.getFileNameWav("_15.wav"));
                else if (mCurDateTime.Minute == 30 && mCurDateTime.Second == 0)
                    playSound(cPubFunc.getFileNameWav("_30.wav"));
                else if (mCurDateTime.Second % 2 == 0)
                    playSoundTickTack(cPubFunc.getFileNameWav("_TickTack.wav"));
            }
            else stopSound();
        }

        // --- ГРАФІКА ---
        private void UpdateLayeredClock()
        {
            // Створюємо бітмап. Важливо: PixelFormat.Format32bppArgb для альфа-каналу
            using (Bitmap bitmap = new Bitmap(this.Width, this.Height, System.Drawing.Imaging.PixelFormat.Format32bppArgb))
            {
                using (Graphics g = Graphics.FromImage(bitmap))
                {
                    DrawClock(g);

                    IntPtr screenDc = Win32.GetDC(IntPtr.Zero);
                    IntPtr memDc = Win32.CreateCompatibleDC(screenDc);
                    IntPtr hBitmap = IntPtr.Zero;
                    IntPtr oldBitmap = IntPtr.Zero;

                    try
                    {
                        // Отримуємо HBITMAP з альфа-каналом (Color.Empty або 0)
                        hBitmap = bitmap.GetHbitmap(Color.FromArgb(0));
                        oldBitmap = Win32.SelectObject(memDc, hBitmap);

                        Win32.Size size = new Win32.Size(this.Width, this.Height);
                        Win32.Point pointSource = new Win32.Point(0, 0);
                        Win32.Point topPos = new Win32.Point(this.Left, this.Top);
                        Win32.BLENDFUNCTION blend = new Win32.BLENDFUNCTION();
                        blend.BlendOp = Win32.AC_SRC_OVER;
                        blend.BlendFlags = 0;
                        blend.SourceConstantAlpha = (byte)((255 * mFrmOpacity) / 100);
                        blend.AlphaFormat = Win32.AC_SRC_ALPHA;

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
            }
        }

        private void DrawClock(Graphics g)
        {
            g.SmoothingMode = SmoothingMode.HighQuality;
            g.PixelOffsetMode = PixelOffsetMode.HighQuality;
            g.TextRenderingHint = TextRenderingHint.AntiAlias;

            int w = this.Width;
            int h = this.Height;

            // 1. Очищаємо фон у повну прозорість
            g.Clear(Color.Transparent);

            // Центр вікна (для 134х134 це 67, 67)
            float xCenter = w / 2.0f;
            float yCenter = h / 2.0f;

            // Товщина кільця
            float borderThickness = 6.0f;

            // МАКСИМАЛЬНИЙ РАДІУС для малювання
            // Встановлюємо радіус рівно в половину ширини (67.0f)
            float radius = Math.Min(w, h) / 2.0f;

            // 2. Фон циферблата
            if (!mChkTransparent)
            {
                using (SolidBrush faceBrush = new SolidBrush(Color.FromArgb(255, 242, 238, 225)))
                {
                    // Малюємо фон на весь розмір кола
                    g.FillEllipse(faceBrush, 0, 0, w, h);
                }
            }

            // 3. БОРДЕР (Кільце впритул до краю)
            if (mChkBorder)
            {
                // Створюємо прямокутник на все вікно
                RectangleF penRect = new RectangleF(0, 0, w, h);

                // Щоб 6-піксельне перо не виходило за межі, звужуємо шлях на половину товщини пера (3px)
                float inset = borderThickness / 2.0f;
                penRect.Inflate(-inset, -inset);

                using (Pen pBlack = new Pen(Color.Black, borderThickness))
                using (Pen pGray = new Pen(Color.Gray, 2.0f))
                {
                    g.DrawEllipse(pBlack, penRect);
                    g.DrawEllipse(pGray, penRect);
                }
            }

            // ВНУТРІШНІЙ РАДІУС для крапок та рисок
            // Відступаємо від краю на товщину бордера + невеликий запас (1-2 пікселі)
            float innerRadius = radius - borderThickness - 1.5f;

            // 4. Поділки
            using (Pen pHour = new Pen(Color.Black, 2.0f))
            using (Pen pQuarter = new Pen(Color.Black, 4.0f))
            using (SolidBrush bBlack = new SolidBrush(Color.Black))
            using (SolidBrush bFace = new SolidBrush(Color.FromArgb(255, 242, 238, 225)))
            {
                for (int i = 0; i < 60; i++)
                {
                    double angle = i * Math.PI / 30.0 - Math.PI / 2.0;
                    float cos = (float)Math.Cos(angle);
                    float sin = (float)Math.Sin(angle);

                    if (i % 5 == 0)
                    {
                        float len = (i % 15 == 0) ? innerRadius * 0.22f : innerRadius * 0.15f;
                        Pen p = (i % 15 == 0) ? pQuarter : pHour;

                        // Малюємо риску так, щоб вона торкалася внутрішньої межі бордера (+3.0f)
                        g.DrawLine(p,
                            xCenter + cos * (innerRadius - len),
                            yCenter + sin * (innerRadius - len),
                            xCenter + cos * (innerRadius + 3.0f),
                            yCenter + sin * (innerRadius + 3.0f));

                        // Крапки на рисках
                        float markDotR = 1.5f;
                        float mx = xCenter + cos * (innerRadius - len);
                        float my = yCenter + sin * (innerRadius - len);
                        g.FillEllipse(bFace, mx - markDotR, my - markDotR, markDotR * 2, markDotR * 2);
                    }
                    else
                    {
                        // Хвилинні крапки (зміщуємо ближче до кільця)
                        float dotR = 1.3f;
                        float px = xCenter + cos * (innerRadius + 1.5f);
                        float py = yCenter + sin * (innerRadius + 1.5f);
                        g.FillEllipse(bBlack, px - dotR, py - dotR, dotR * 2, dotR * 2);
                    }
                }
            }

            // 5. Текст та стрілки (використовують оновлений innerRadius)
            DateTime dtNow = mChkGMT ? DateTime.UtcNow : DateTime.Now;
            using (Font fontLN = new Font("Arial", innerRadius * 0.2f, FontStyle.Italic | FontStyle.Underline))
            using (Font fontText = new Font("Arial", innerRadius * 0.11f, FontStyle.Bold))
            using (SolidBrush bLN = new SolidBrush(Color.FromArgb(255, 240, 128, 128)))
            using (SolidBrush bDate = new SolidBrush(Color.SteelBlue))
            using (SolidBrush bDayNormal = new SolidBrush(Color.SaddleBrown))
            using (SolidBrush bDayRed = new SolidBrush(Color.Red))
            using (SolidBrush bUTC = new SolidBrush(Color.Olive))
            {
                StringFormat sf = new StringFormat();
                sf.Alignment = StringAlignment.Center;
                sf.LineAlignment = StringAlignment.Center;

                g.DrawString("LN", fontLN, bLN, xCenter, yCenter - innerRadius * 0.52f, sf);

                if (mChkDay)
                {
                    string strDay = dtNow.DayOfWeek.ToString();
                    Brush bDay = (dtNow.DayOfWeek == DayOfWeek.Saturday || dtNow.DayOfWeek == DayOfWeek.Sunday) ? bDayRed : bDayNormal;
                    g.DrawString(strDay, fontText, bDay, xCenter, yCenter + innerRadius * 0.12f, sf);
                }

                if (mChkDate)
                {
                    g.DrawString(dtNow.ToString("dd.MM.yyyy"), fontText, bDate, xCenter, yCenter + innerRadius * 0.35f, sf);
                }

                if (mChkGMT)
                {
                    g.DrawString("GMT", fontText, bUTC, xCenter, yCenter + innerRadius * 0.58f, sf);
                }
            }

            // 6. Стрілки
            DrawHand(g, xCenter, yCenter, (dtNow.Hour % 12 + dtNow.Minute / 60.0f) * 5.0f, innerRadius * 0.58f, 6.5f, true);
            DrawHand(g, xCenter, yCenter, dtNow.Minute + dtNow.Second / 60.0f, innerRadius * 0.85f, 4.5f, true);

            float sAngle = (float)(dtNow.Second * Math.PI / 30.0 - Math.PI / 2.0);
            using (Pen pSec = new Pen(Color.Red, 1.5f))
            {
                float cos = (float)Math.Cos(sAngle);
                float sin = (float)Math.Sin(sAngle);
                g.DrawLine(pSec,
                    xCenter - cos * (innerRadius * 0.15f),
                    yCenter - sin * (innerRadius * 0.15f),
                    xCenter + cos * (innerRadius * 0.95f),
                    yCenter + sin * (innerRadius * 0.95f));
            }

            using (SolidBrush bCenter = new SolidBrush(Color.Black))
            {
                g.FillEllipse(bCenter, xCenter - 4, yCenter - 4, 8, 8);
            }
        }

        private void DrawHand(Graphics g, float xc, float yc, float val, float len, float width, bool whiteLine)
        {
            double angle = val * Math.PI / 30.0 - Math.PI / 2.0;
            float x = xc + (float)Math.Cos(angle) * len;
            float y = yc + (float)Math.Sin(angle) * len;

            using (Pen pBlack = new Pen(Color.Black, width))
            {
                pBlack.StartCap = LineCap.Round;
                pBlack.EndCap = LineCap.Round;
                g.DrawLine(pBlack, xc, yc, x, y);
            }

            if (whiteLine)
            {
                using (Pen pWhite = new Pen(Color.White, width / 2.2f))
                {
                    pWhite.StartCap = LineCap.Round;
                    pWhite.EndCap = LineCap.Round;
                    g.DrawLine(pWhite, xc, yc, x, y);
                }
            }
        }

        // --- ПОДІЇ МИШІ ---
        private void FMain_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left && mChkMoving)
            {
                mIsMouseDown = true;
                mLastMousePos = e.Location;
            }
            if (e.Button == MouseButtons.Right)
            {
                if (contextMenuFMain != null) contextMenuFMain.Show(Cursor.Position);
            }
        }

        private void FMain_MouseMove(object sender, MouseEventArgs e)
        {
            if (mIsMouseDown && mChkMoving)
            {
                int dx = e.X - mLastMousePos.X;
                int dy = e.Y - mLastMousePos.Y;
                this.Location = new Point(this.Left + dx, this.Top + dy);
                UpdateLayeredClock();
            }
        }

        private void FMain_MouseUp(object sender, MouseEventArgs e)
        {
            mIsMouseDown = false;
            if (mChkMoving) { mDeskX = this.Left; mDeskY = this.Top; SaveSettings(); }
        }

        // --- ІНШІ МЕТОДИ ---
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
                    mTimeShutDown = Convert.ToDateTime(dr["timeOff"]);
                    mIsShutDown = Convert.ToBoolean(dr["chkOff"]);
                    mChkGMT = Convert.ToBoolean(dr["chkGMT"]);
                    mChkDate = Convert.ToBoolean(dr["chkDate"]);
                    mChkDay = Convert.ToBoolean(dr["chkDay"]);
                    mChkMoving = Convert.ToBoolean(dr["chkMoving"]);
                    mChkTransparent = Convert.ToBoolean(dr["chkTransparent"]);
                    mChkAlwaysOnTop = Convert.ToBoolean(dr["chkAlwaysOnTop"]);
                    mChkBorder = Convert.ToBoolean(dr["chkBorder"]);
                    mChkSound = Convert.ToBoolean(dr["chkSound"]);
                    mFrmOpacity = Convert.ToInt32(dr["frmOpacity"]);
                    mDeskX = Convert.ToInt32(dr["deskX"]);
                    mDeskY = Convert.ToInt32(dr["deskY"]);
                    mIntervalRefr = Convert.ToInt32(dr["intervalRefr"]);
                }
                else
                {
                    DataTable table = new DataTable(TBL_NAME);
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
                    table.Columns.Add("frmOpacity", typeof(int));
                    table.Columns.Add("deskX", typeof(int));
                    table.Columns.Add("deskY", typeof(int));
                    table.Columns.Add("intervalRefr", typeof(int));
                    ds.Tables.Add(table);
                    DataRow dr = ds.Tables[TBL_NAME].NewRow();
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
                    ds.Tables[TBL_NAME].Rows.Add(dr);
                    ds.WriteXml(cPubFunc.fileNameSet());
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
                dr["chkSound"] = mChkSound;
                dr["frmOpacity"] = mFrmOpacity;
                dr["deskX"] = this.Left;
                dr["deskY"] = this.Top;
                ds.WriteXml(cPubFunc.fileNameSet());
            }
            catch { }
        }

        private DateTime getCurTime(bool isGmt) { return isGmt ? DateTime.UtcNow : DateTime.Now; }
        private void startPosition(ref int x, ref int y)
        {
            Rectangle workingRectangle = Screen.PrimaryScreen.WorkingArea;
            x = workingRectangle.Width - (int)(this.Size.Width + this.Size.Width * 0.2);
            y = workingRectangle.Height - (int)(this.Size.Height + this.Size.Height * 0.2);
        }
        private void setTimeToTray()
        {
            if (DateTime.Now.Second != 1) return;
            string str = mCurDateTime.DayOfWeek.ToString() + " - " + mCurDateTime.ToShortTimeString();
            if (mChkGMT) str += " GMT";
            notifyIcon1.Text = str;
        }
        private void setShutdown(bool isShutDown, bool isSleep)
        {
            if (isSleep && (mTimeShutDown != cPubFunc.chkTime()) && (DateTime.Now.ToString("hh:mm").Equals(mTimeShutDown.ToString("hh:mm"))))
                cPubFunc.SetSuspendState(false, true, true);
            else if (isShutDown && (mTimeShutDown != cPubFunc.chkTime()) && (DateTime.Now.ToString("hh:mm").Equals(mTimeShutDown.ToString("hh:mm"))))
                cPubFunc.DoExitWindows(cPubFunc.Poweroff);
        }
        private void playSoundTickTack(string filename)
        {
            if (string.IsNullOrEmpty(filename)) return;
            if (!_isRuning && mChkSound)
            {
                _isRuning = true;
                cts = new CancellationTokenSource();
                Task.Run(() => { if (!cts.Token.IsCancellationRequested) cPubFunc.playSound(filename); _isRuning = false; }, cts.Token);
            }
        }
        private void playSound(string filename)
        {
            if (string.IsNullOrEmpty(filename)) return;
            cts = new CancellationTokenSource();
            Task.Run(() => { if (!cts.Token.IsCancellationRequested) cPubFunc.playSound(filename); }, cts.Token);
        }
        private void stopSound() { cts.Cancel(); }
        private void closeForm() { this.Visible = true; Application.Exit(); }

        private void cm_SetupClick()
        {
            FSetup fs = new FSetup();
            fs.initialization(mChkGMT, mChkDate, mChkDay, mChkMoving, mChkAlwaysOnTop, mChkTransparent, mChkBorder, mChkSound, mFrmOpacity);
            fs.ShowDialog();
            if (fs.mClose <= 0) return;
            mChkGMT = fs.mChkGMT; mChkDate = fs.mChkDate; mChkDay = fs.mChkDay; mChkMoving = fs.mChkMoving;
            mChkAlwaysOnTop = fs.mChkAlwaysOnTop; mChkTransparent = fs.mChkTransparent; mChkBorder = fs.mChkBorder;
            mChkSound = fs.mChkSound; mFrmOpacity = fs.mValOpacity;
            this.TopMost = mChkAlwaysOnTop;
            UpdateLayeredClock();
            SaveSettings();
        }

        private void cm_Setup_Click(object sender, EventArgs e) { cm_SetupClick(); }
        private void cm_StartPosition_Click(object sender, EventArgs e) { startPosition(ref mDeskX, ref mDeskY); this.Location = new Point(mDeskX, mDeskY); UpdateLayeredClock(); }
        private void cm_hide_Click(object sender, EventArgs e) { this.Visible = false; }
        private void cm_calendar_Click(object sender, EventArgs e) { new FCalendar().ShowDialog(); }
        private void cm_setShutDownPC_Click(object sender, EventArgs e)
        {
            FShutDown fsd = new FShutDown(mTimeShutDown, mIsShutDown, mIsSleep);
            fsd.ShowDialog();
            mIsShutDown = fsd.isShutDown; mIsSleep = fsd.isSleep;
            if (mIsShutDown) { mTimeShutDown = fsd.tm; cm_setShutDownPC.Checked = true; } else { cm_setShutDownPC.Checked = false; }
        }
        private void cm_about_Click(object sender, EventArgs e) { new FAbout().ShowDialog(); }
        private void cm_exit_Click(object sender, EventArgs e) { closeForm(); }
        private void mCMViewClick() { if (this.Visible) this.Visible = false; else { this.Visible = true; this.Activate(); } }
        private void notifyIcon1_DoubleClick(object sender, EventArgs e) { mCMViewClick(); }
        private void m_Open_Click(object sender, EventArgs e) { mCMViewClick(); }
        private void m_Setup_Click(object sender, EventArgs e) { cm_SetupClick(); }
        private void m_About_Click(object sender, EventArgs e) { cm_about_Click(sender, e); }
        private void m_Exit_Click(object sender, EventArgs e) { cm_exit_Click(sender, e); }
        private void FMain_FormClosing(object sender, FormClosingEventArgs e) { SaveSettings(); }
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

        [DllImport("user32.dll", ExactSpelling = true, SetLastError = true)]
        public static extern bool UpdateLayeredWindow(IntPtr hwnd, IntPtr hdcDst, ref Point pptDst, ref Size psize, IntPtr hdcSrc, ref Point pptSrc, int crKey, ref BLENDFUNCTION pblend, int dwFlags);

        [DllImport("user32.dll", ExactSpelling = true, SetLastError = true)]
        public static extern IntPtr GetDC(IntPtr hWnd);

        [DllImport("user32.dll", ExactSpelling = true)]
        public static extern int ReleaseDC(IntPtr hWnd, IntPtr hDC);

        [DllImport("gdi32.dll", ExactSpelling = true, SetLastError = true)]
        public static extern IntPtr CreateCompatibleDC(IntPtr hDC);

        [DllImport("gdi32.dll", ExactSpelling = true, SetLastError = true)]
        public static extern bool DeleteDC(IntPtr hdc);

        [DllImport("gdi32.dll", ExactSpelling = true)]
        public static extern IntPtr SelectObject(IntPtr hDC, IntPtr hObject);

        [DllImport("gdi32.dll", ExactSpelling = true, SetLastError = true)]
        public static extern bool DeleteObject(IntPtr hObject);
    }
}