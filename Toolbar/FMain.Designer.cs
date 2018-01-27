namespace toolbar
{
    partial class FMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
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
            this.contMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.mExit = new System.Windows.Forms.ToolStripMenuItem();
            this.tmr = new System.Windows.Forms.Timer(this.components);
            this.grpTime = new System.Windows.Forms.GroupBox();
            this.lblTime = new System.Windows.Forms.Label();
            this.grpPrev = new System.Windows.Forms.GroupBox();
            this.mCalPrev = new System.Windows.Forms.MonthCalendar();
            this.grpCurr = new System.Windows.Forms.GroupBox();
            this.mCalCurr = new System.Windows.Forms.MonthCalendar();
            this.grpNext = new System.Windows.Forms.GroupBox();
            this.mCalNext = new System.Windows.Forms.MonthCalendar();
            this.ntfIcon = new System.Windows.Forms.NotifyIcon(this.components);
            this.contMenu.SuspendLayout();
            this.grpTime.SuspendLayout();
            this.grpPrev.SuspendLayout();
            this.grpCurr.SuspendLayout();
            this.grpNext.SuspendLayout();
            this.SuspendLayout();
            // 
            // contMenu
            // 
            this.contMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mExit});
            this.contMenu.Name = "contMenu";
            this.contMenu.Size = new System.Drawing.Size(109, 26);
            // 
            // mExit
            // 
            this.mExit.Name = "mExit";
            this.mExit.Size = new System.Drawing.Size(108, 22);
            this.mExit.Text = "Выход";
            this.mExit.Click += new System.EventHandler(this.mExit_Click);
            // 
            // tmr
            // 
            this.tmr.Enabled = true;
            this.tmr.Interval = 1000;
            this.tmr.Tick += new System.EventHandler(this.tmr_Tick);
            // 
            // grpTime
            // 
            this.grpTime.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.grpTime.Controls.Add(this.lblTime);
            this.grpTime.Location = new System.Drawing.Point(4, 4);
            this.grpTime.Name = "grpTime";
            this.grpTime.Size = new System.Drawing.Size(201, 55);
            this.grpTime.TabIndex = 1;
            this.grpTime.TabStop = false;
            // 
            // lblTime
            // 
            this.lblTime.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lblTime.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblTime.Location = new System.Drawing.Point(12, 12);
            this.lblTime.Name = "lblTime";
            this.lblTime.Size = new System.Drawing.Size(184, 36);
            this.lblTime.TabIndex = 2;
            this.lblTime.Text = "08:08:08";
            this.lblTime.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lblTime.DoubleClick += new System.EventHandler(this.lblTime_DoubleClick);
            // 
            // grpPrev
            // 
            this.grpPrev.Controls.Add(this.mCalPrev);
            this.grpPrev.Location = new System.Drawing.Point(284, 81);
            this.grpPrev.Name = "grpPrev";
            this.grpPrev.Size = new System.Drawing.Size(193, 176);
            this.grpPrev.TabIndex = 2;
            this.grpPrev.TabStop = false;
            this.grpPrev.Text = "Предыдущий";
            // 
            // mCalPrev
            // 
            this.mCalPrev.BackColor = System.Drawing.SystemColors.Window;
            this.mCalPrev.FirstDayOfWeek = System.Windows.Forms.Day.Monday;
            this.mCalPrev.Location = new System.Drawing.Point(4, 16);
            this.mCalPrev.MaxSelectionCount = 1;
            this.mCalPrev.Name = "mCalPrev";
            this.mCalPrev.ShowToday = false;
            this.mCalPrev.ShowTodayCircle = false;
            this.mCalPrev.ShowWeekNumbers = true;
            this.mCalPrev.TabIndex = 3;
            // 
            // grpCurr
            // 
            this.grpCurr.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.grpCurr.Controls.Add(this.mCalCurr);
            this.grpCurr.Location = new System.Drawing.Point(4, 65);
            this.grpCurr.Name = "grpCurr";
            this.grpCurr.Size = new System.Drawing.Size(201, 183);
            this.grpCurr.TabIndex = 4;
            this.grpCurr.TabStop = false;
            this.grpCurr.Text = "КАЛЕНДАРЬ";
            // 
            // mCalCurr
            // 
            this.mCalCurr.FirstDayOfWeek = System.Windows.Forms.Day.Monday;
            this.mCalCurr.Location = new System.Drawing.Point(7, 16);
            this.mCalCurr.MaxSelectionCount = 1;
            this.mCalCurr.Name = "mCalCurr";
            this.mCalCurr.ShowWeekNumbers = true;
            this.mCalCurr.TabIndex = 3;
            this.mCalCurr.TodayDate = new System.DateTime(2009, 1, 11, 0, 0, 0, 0);
            this.mCalCurr.DateChanged += new System.Windows.Forms.DateRangeEventHandler(this.mCalCurr_DateChanged);
            // 
            // grpNext
            // 
            this.grpNext.Controls.Add(this.mCalNext);
            this.grpNext.Location = new System.Drawing.Point(284, 271);
            this.grpNext.Name = "grpNext";
            this.grpNext.Size = new System.Drawing.Size(193, 176);
            this.grpNext.TabIndex = 4;
            this.grpNext.TabStop = false;
            this.grpNext.Text = "Следующий";
            // 
            // mCalNext
            // 
            this.mCalNext.FirstDayOfWeek = System.Windows.Forms.Day.Monday;
            this.mCalNext.Location = new System.Drawing.Point(4, 16);
            this.mCalNext.MaxSelectionCount = 1;
            this.mCalNext.Name = "mCalNext";
            this.mCalNext.ShowToday = false;
            this.mCalNext.ShowTodayCircle = false;
            this.mCalNext.ShowWeekNumbers = true;
            this.mCalNext.TabIndex = 3;
            // 
            // ntfIcon
            // 
            this.ntfIcon.ContextMenuStrip = this.contMenu;
            this.ntfIcon.Icon = ((System.Drawing.Icon)(resources.GetObject("ntfIcon.Icon")));
            this.ntfIcon.Text = "Календари";
            this.ntfIcon.Visible = true;
            this.ntfIcon.DoubleClick += new System.EventHandler(this.ntfIcon_DoubleClick);
            // 
            // FMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(210, 269);
            this.ContextMenuStrip = this.contMenu;
            this.ControlBox = false;
            this.Controls.Add(this.grpPrev);
            this.Controls.Add(this.grpNext);
            this.Controls.Add(this.grpCurr);
            this.Controls.Add(this.grpTime);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "FMain";
            this.Opacity = 0.85D;
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "FMain";
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.FMain_MouseDown);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.FMain_MouseMove);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.FMain_MouseUp);
            this.contMenu.ResumeLayout(false);
            this.grpTime.ResumeLayout(false);
            this.grpPrev.ResumeLayout(false);
            this.grpCurr.ResumeLayout(false);
            this.grpNext.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ContextMenuStrip contMenu;
        private System.Windows.Forms.ToolStripMenuItem mExit;
        private System.Windows.Forms.Timer tmr;
        private System.Windows.Forms.GroupBox grpTime;
        private System.Windows.Forms.Label lblTime;
        private System.Windows.Forms.GroupBox grpPrev;
        private System.Windows.Forms.MonthCalendar mCalPrev;
        private System.Windows.Forms.GroupBox grpCurr;
        private System.Windows.Forms.GroupBox grpNext;
        private System.Windows.Forms.MonthCalendar mCalNext;
        private System.Windows.Forms.NotifyIcon ntfIcon;
        private System.Windows.Forms.MonthCalendar mCalCurr;
    }
}

