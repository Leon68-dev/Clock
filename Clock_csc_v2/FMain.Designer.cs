namespace Clock_csc_v2
{
    partial class FMain
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FMain));
            timer1 = new System.Windows.Forms.Timer(components);
            notifyIcon1 = new NotifyIcon(components);
            contextMenu1 = new ContextMenuStrip(components);
            m_Setup = new ToolStripMenuItem();
            m_Open = new ToolStripMenuItem();
            toolStripSeparator4 = new ToolStripSeparator();
            m_About = new ToolStripMenuItem();
            toolStripSeparator5 = new ToolStripSeparator();
            m_Exit = new ToolStripMenuItem();
            contextMenuFMain = new ContextMenuStrip(components);
            cm_Setup = new ToolStripMenuItem();
            cm_hide = new ToolStripMenuItem();
            cm_StartPosition = new ToolStripMenuItem();
            toolStripSeparator3 = new ToolStripSeparator();
            cm_calendar = new ToolStripMenuItem();
            cm_setShutDownPC = new ToolStripMenuItem();
            toolStripSeparator1 = new ToolStripSeparator();
            cm_about = new ToolStripMenuItem();
            toolStripSeparator2 = new ToolStripSeparator();
            cm_exit = new ToolStripMenuItem();
            cm_world_map = new ToolStripMenuItem();
            contextMenu1.SuspendLayout();
            contextMenuFMain.SuspendLayout();
            SuspendLayout();
            // 
            // timer1
            // 
            timer1.Interval = 1000;
            timer1.Tick += timer1_Tick;
            // 
            // notifyIcon1
            // 
            notifyIcon1.ContextMenuStrip = contextMenu1;
            notifyIcon1.Icon = (Icon)resources.GetObject("notifyIcon1.Icon");
            notifyIcon1.Text = "Clock (.NET)";
            notifyIcon1.Visible = true;
            notifyIcon1.DoubleClick += notifyIcon1_DoubleClick;
            // 
            // contextMenu1
            // 
            contextMenu1.ImageScalingSize = new Size(20, 20);
            contextMenu1.Items.AddRange(new ToolStripItem[] { m_Setup, m_Open, toolStripSeparator4, m_About, toolStripSeparator5, m_Exit });
            contextMenu1.Name = "contextMenu1";
            contextMenu1.Size = new Size(129, 112);
            // 
            // m_Setup
            // 
            m_Setup.Name = "m_Setup";
            m_Setup.Size = new Size(128, 24);
            m_Setup.Text = "Setup...";
            m_Setup.Click += m_Setup_Click;
            // 
            // m_Open
            // 
            m_Open.Name = "m_Open";
            m_Open.Size = new Size(128, 24);
            m_Open.Text = "Hide";
            m_Open.Click += m_Open_Click;
            // 
            // toolStripSeparator4
            // 
            toolStripSeparator4.Name = "toolStripSeparator4";
            toolStripSeparator4.Size = new Size(125, 6);
            // 
            // m_About
            // 
            m_About.Name = "m_About";
            m_About.Size = new Size(128, 24);
            m_About.Text = "About...";
            m_About.Click += m_About_Click;
            // 
            // toolStripSeparator5
            // 
            toolStripSeparator5.Name = "toolStripSeparator5";
            toolStripSeparator5.Size = new Size(125, 6);
            // 
            // m_Exit
            // 
            m_Exit.Name = "m_Exit";
            m_Exit.Size = new Size(128, 24);
            m_Exit.Text = "Exit";
            m_Exit.Click += m_Exit_Click;
            // 
            // contextMenuFMain
            // 
            contextMenuFMain.ImageScalingSize = new Size(20, 20);
            contextMenuFMain.Items.AddRange(new ToolStripItem[] { cm_Setup, cm_hide, cm_StartPosition, toolStripSeparator3, cm_calendar, cm_setShutDownPC, cm_world_map, toolStripSeparator1, cm_about, toolStripSeparator2, cm_exit });
            contextMenuFMain.Name = "contextMenuFMain";
            contextMenuFMain.Size = new Size(211, 242);
            // 
            // cm_Setup
            // 
            cm_Setup.Name = "cm_Setup";
            cm_Setup.Size = new Size(211, 24);
            cm_Setup.Text = "Setup...";
            cm_Setup.Click += cm_Setup_Click;
            // 
            // cm_hide
            // 
            cm_hide.Name = "cm_hide";
            cm_hide.Size = new Size(211, 24);
            cm_hide.Text = "Hide";
            cm_hide.Click += cm_hide_Click;
            // 
            // cm_StartPosition
            // 
            cm_StartPosition.Name = "cm_StartPosition";
            cm_StartPosition.Size = new Size(211, 24);
            cm_StartPosition.Text = "Start position";
            cm_StartPosition.Click += cm_StartPosition_Click;
            // 
            // toolStripSeparator3
            // 
            toolStripSeparator3.Name = "toolStripSeparator3";
            toolStripSeparator3.Size = new Size(208, 6);
            // 
            // cm_calendar
            // 
            cm_calendar.Name = "cm_calendar";
            cm_calendar.Size = new Size(211, 24);
            cm_calendar.Text = "Calendar...";
            cm_calendar.Click += cm_calendar_Click;
            // 
            // cm_setShutDownPC
            // 
            cm_setShutDownPC.Name = "cm_setShutDownPC";
            cm_setShutDownPC.Size = new Size(211, 24);
            cm_setShutDownPC.Text = "Set Shut Down PC...";
            cm_setShutDownPC.Click += cm_setShutDownPC_Click;
            // 
            // toolStripSeparator1
            // 
            toolStripSeparator1.Name = "toolStripSeparator1";
            toolStripSeparator1.Size = new Size(208, 6);
            // 
            // cm_about
            // 
            cm_about.Name = "cm_about";
            cm_about.Size = new Size(211, 24);
            cm_about.Text = "About...";
            cm_about.Click += cm_about_Click;
            // 
            // toolStripSeparator2
            // 
            toolStripSeparator2.Name = "toolStripSeparator2";
            toolStripSeparator2.Size = new Size(208, 6);
            // 
            // cm_exit
            // 
            cm_exit.Name = "cm_exit";
            cm_exit.Size = new Size(211, 24);
            cm_exit.Text = "Exit";
            cm_exit.Click += cm_exit_Click;
            // 
            // cm_world_map
            // 
            cm_world_map.Name = "cm_world_map";
            cm_world_map.Size = new Size(210, 24);
            cm_world_map.Text = "World Map...";
            cm_world_map.Click += cm_world_map_Click;
            // 
            // FMain
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.OldLace;
            ClientSize = new Size(160, 160);
            ContextMenuStrip = contextMenuFMain;
            DoubleBuffered = true;
            FormBorderStyle = FormBorderStyle.None;
            Icon = (Icon)resources.GetObject("$this.Icon");
            MinimumSize = new Size(160, 160);
            Name = "FMain";
            ShowInTaskbar = false;
            StartPosition = FormStartPosition.Manual;
            Text = "Clock";
            TransparencyKey = Color.Transparent;
            FormClosing += FMain_FormClosing;
            MouseDown += FMain_MouseDown;
            MouseMove += FMain_MouseMove;
            MouseUp += FMain_MouseUp;
            contextMenu1.ResumeLayout(false);
            contextMenuFMain.ResumeLayout(false);
            ResumeLayout(false);
        }

        #endregion

        private System.Windows.Forms.Timer timer1;
        private NotifyIcon notifyIcon1;
        private ContextMenuStrip contextMenu1;
        private ToolStripMenuItem m_Setup;
        private ToolStripMenuItem m_Open;
        private ToolStripSeparator toolStripSeparator4;
        private ToolStripMenuItem m_About;
        private ToolStripSeparator toolStripSeparator5;
        private ToolStripMenuItem m_Exit;
        private ContextMenuStrip contextMenuFMain;
        private ToolStripMenuItem cm_Setup;
        private ToolStripMenuItem cm_hide;
        private ToolStripMenuItem cm_StartPosition;
        private ToolStripSeparator toolStripSeparator3;
        private ToolStripMenuItem cm_calendar;
        private ToolStripMenuItem cm_setShutDownPC;
        private ToolStripSeparator toolStripSeparator1;
        private ToolStripMenuItem cm_about;
        private ToolStripSeparator toolStripSeparator2;
        private ToolStripMenuItem cm_exit;
        private ToolStripMenuItem cm_world_map;
    }
}
