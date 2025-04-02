namespace Clock_cs_v2
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
            this.cm_Setup.Size = new System.Drawing.Size(210, 24);
            this.cm_Setup.Text = "Setup...";
            this.cm_Setup.Click += new System.EventHandler(this.cm_Setup_Click);
            // 
            // cm_hide
            // 
            this.cm_hide.Name = "cm_hide";
            this.cm_hide.Size = new System.Drawing.Size(210, 24);
            this.cm_hide.Text = "Hide";
            this.cm_hide.Click += new System.EventHandler(this.cm_hide_Click);
            // 
            // cm_StartPosition
            // 
            this.cm_StartPosition.Name = "cm_StartPosition";
            this.cm_StartPosition.Size = new System.Drawing.Size(210, 24);
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
            this.cm_calendar.Size = new System.Drawing.Size(210, 24);
            this.cm_calendar.Text = "Calendar...";
            this.cm_calendar.Click += new System.EventHandler(this.cm_calendar_Click);
            // 
            // cm_setShutDownPC
            // 
            this.cm_setShutDownPC.Name = "cm_setShutDownPC";
            this.cm_setShutDownPC.Size = new System.Drawing.Size(210, 24);
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
            this.cm_about.Size = new System.Drawing.Size(210, 24);
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
            this.cm_exit.Size = new System.Drawing.Size(210, 24);
            this.cm_exit.Text = "Exit";
            this.cm_exit.Click += new System.EventHandler(this.cm_exit_Click);
            // 
            // FMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.OldLace;
            this.ClientSize = new System.Drawing.Size(175, 175);
            this.ContextMenuStrip = this.contextMenuFMain;
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.MinimumSize = new System.Drawing.Size(175, 175);
            this.Name = "FMain";
            this.ShowIcon = false;
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

        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.NotifyIcon notifyIcon1;
        private System.Windows.Forms.ContextMenu contextMenu1;
        private System.Windows.Forms.MenuItem mSetup;
        private System.Windows.Forms.MenuItem mOpen;
        private System.Windows.Forms.MenuItem menuItem1;
        private System.Windows.Forms.MenuItem mAbout;
        private System.Windows.Forms.MenuItem menuItem9;
        private System.Windows.Forms.MenuItem mExit;
        private System.Windows.Forms.ContextMenuStrip contextMenuFMain;
        private System.Windows.Forms.ToolStripMenuItem cm_Setup;
        private System.Windows.Forms.ToolStripMenuItem cm_hide;
        private System.Windows.Forms.ToolStripMenuItem cm_StartPosition;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripMenuItem cm_calendar;
        private System.Windows.Forms.ToolStripMenuItem cm_setShutDownPC;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem cm_about;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem cm_exit;
    }
}

