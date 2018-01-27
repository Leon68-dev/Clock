namespace ClockAndToolbar
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
            this.btnRef = new System.Windows.Forms.Button();
            this.btnIE = new System.Windows.Forms.Button();
            this.btnSet = new System.Windows.Forms.Button();
            this.ntfIcon = new System.Windows.Forms.NotifyIcon(this.components);
            this.cmsWeather = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.cmsWeather_Hide = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.cmsWeather_Refr = new System.Windows.Forms.ToolStripMenuItem();
            this.cmsWeather_IE = new System.Windows.Forms.ToolStripMenuItem();
            this.cmsWeather_Set = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.cmsWeather_Exit = new System.Windows.Forms.ToolStripMenuItem();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.lstBoxState = new System.Windows.Forms.ListBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.rtbDescription = new System.Windows.Forms.RichTextBox();
            this.grpCurr = new System.Windows.Forms.GroupBox();
            this.mCalCurr = new System.Windows.Forms.MonthCalendar();
            this.grpTime = new System.Windows.Forms.GroupBox();
            this.lblTime = new System.Windows.Forms.Label();
            this.tmr = new System.Windows.Forms.Timer(this.components);
            this.cmsWeather.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.grpCurr.SuspendLayout();
            this.grpTime.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnRef
            // 
            this.btnRef.Enabled = false;
            this.btnRef.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btnRef.Location = new System.Drawing.Point(20, 16);
            this.btnRef.Name = "btnRef";
            this.btnRef.Size = new System.Drawing.Size(75, 23);
            this.btnRef.TabIndex = 0;
            this.btnRef.TabStop = false;
            this.btnRef.Text = "Обновить";
            this.btnRef.UseVisualStyleBackColor = true;
            this.btnRef.Visible = false;
            this.btnRef.Click += new System.EventHandler(this.btnRef_Click);
            // 
            // btnIE
            // 
            this.btnIE.Enabled = false;
            this.btnIE.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btnIE.Location = new System.Drawing.Point(68, 32);
            this.btnIE.Name = "btnIE";
            this.btnIE.Size = new System.Drawing.Size(75, 23);
            this.btnIE.TabIndex = 4;
            this.btnIE.TabStop = false;
            this.btnIE.Text = "IE";
            this.btnIE.UseVisualStyleBackColor = true;
            this.btnIE.Visible = false;
            this.btnIE.Click += new System.EventHandler(this.btnIE_Click);
            // 
            // btnSet
            // 
            this.btnSet.Enabled = false;
            this.btnSet.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btnSet.Location = new System.Drawing.Point(96, 44);
            this.btnSet.Name = "btnSet";
            this.btnSet.Size = new System.Drawing.Size(75, 23);
            this.btnSet.TabIndex = 5;
            this.btnSet.TabStop = false;
            this.btnSet.Text = "Настройки";
            this.btnSet.UseVisualStyleBackColor = true;
            this.btnSet.Visible = false;
            this.btnSet.Click += new System.EventHandler(this.btnSet_Click);
            // 
            // ntfIcon
            // 
            this.ntfIcon.ContextMenuStrip = this.cmsWeather;
            this.ntfIcon.Icon = ((System.Drawing.Icon)(resources.GetObject("ntfIcon.Icon")));
            this.ntfIcon.Text = "Погода";
            this.ntfIcon.Visible = true;
            this.ntfIcon.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.ntfIcon_MouseDoubleClick);
            // 
            // cmsWeather
            // 
            this.cmsWeather.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.cmsWeather_Hide,
            this.toolStripSeparator2,
            this.cmsWeather_Refr,
            this.cmsWeather_IE,
            this.cmsWeather_Set,
            this.toolStripSeparator1,
            this.cmsWeather_Exit});
            this.cmsWeather.Name = "cmsWeather";
            this.cmsWeather.Size = new System.Drawing.Size(135, 126);
            // 
            // cmsWeather_Hide
            // 
            this.cmsWeather_Hide.Name = "cmsWeather_Hide";
            this.cmsWeather_Hide.Size = new System.Drawing.Size(134, 22);
            this.cmsWeather_Hide.Text = "Скрыть";
            this.cmsWeather_Hide.Click += new System.EventHandler(this.cmsWeather_Hide_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(131, 6);
            // 
            // cmsWeather_Refr
            // 
            this.cmsWeather_Refr.Name = "cmsWeather_Refr";
            this.cmsWeather_Refr.Size = new System.Drawing.Size(134, 22);
            this.cmsWeather_Refr.Text = "Обновить";
            this.cmsWeather_Refr.Click += new System.EventHandler(this.cmsWeather_Refr_Click);
            // 
            // cmsWeather_IE
            // 
            this.cmsWeather_IE.Name = "cmsWeather_IE";
            this.cmsWeather_IE.Size = new System.Drawing.Size(134, 22);
            this.cmsWeather_IE.Text = "IE";
            this.cmsWeather_IE.Click += new System.EventHandler(this.cmsWeather_IE_Click);
            // 
            // cmsWeather_Set
            // 
            this.cmsWeather_Set.Name = "cmsWeather_Set";
            this.cmsWeather_Set.Size = new System.Drawing.Size(134, 22);
            this.cmsWeather_Set.Text = "Настройки";
            this.cmsWeather_Set.Click += new System.EventHandler(this.cmsWeather_Set_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(131, 6);
            // 
            // cmsWeather_Exit
            // 
            this.cmsWeather_Exit.Name = "cmsWeather_Exit";
            this.cmsWeather_Exit.Size = new System.Drawing.Size(134, 22);
            this.cmsWeather_Exit.Text = "Выход";
            this.cmsWeather_Exit.Click += new System.EventHandler(this.cmsWeather_Exit_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.lstBoxState);
            this.groupBox2.Controls.Add(this.groupBox1);
            this.groupBox2.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.groupBox2.Location = new System.Drawing.Point(5, 258);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(264, 162);
            this.groupBox2.TabIndex = 6;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Прогноз";
            // 
            // lstBoxState
            // 
            this.lstBoxState.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lstBoxState.FormattingEnabled = true;
            this.lstBoxState.Location = new System.Drawing.Point(7, 19);
            this.lstBoxState.Name = "lstBoxState";
            this.lstBoxState.Size = new System.Drawing.Size(247, 69);
            this.lstBoxState.TabIndex = 0;
            this.lstBoxState.SelectedIndexChanged += new System.EventHandler(this.lstBoxState_SelectedIndexChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox1.Controls.Add(this.rtbDescription);
            this.groupBox1.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.groupBox1.Location = new System.Drawing.Point(7, 89);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(250, 67);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Описание";
            // 
            // rtbDescription
            // 
            this.rtbDescription.BackColor = System.Drawing.SystemColors.Control;
            this.rtbDescription.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.rtbDescription.Dock = System.Windows.Forms.DockStyle.Fill;
            this.rtbDescription.Location = new System.Drawing.Point(3, 16);
            this.rtbDescription.Name = "rtbDescription";
            this.rtbDescription.ReadOnly = true;
            this.rtbDescription.Size = new System.Drawing.Size(244, 48);
            this.rtbDescription.TabIndex = 0;
            this.rtbDescription.TabStop = false;
            this.rtbDescription.Text = "";
            // 
            // grpCurr
            // 
            this.grpCurr.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.grpCurr.Controls.Add(this.mCalCurr);
            this.grpCurr.Location = new System.Drawing.Point(5, 71);
            this.grpCurr.Name = "grpCurr";
            this.grpCurr.Size = new System.Drawing.Size(264, 185);
            this.grpCurr.TabIndex = 8;
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
            // 
            // grpTime
            // 
            this.grpTime.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.grpTime.Controls.Add(this.lblTime);
            this.grpTime.Location = new System.Drawing.Point(5, 12);
            this.grpTime.Name = "grpTime";
            this.grpTime.Size = new System.Drawing.Size(264, 55);
            this.grpTime.TabIndex = 7;
            this.grpTime.TabStop = false;
            // 
            // lblTime
            // 
            this.lblTime.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lblTime.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblTime.Location = new System.Drawing.Point(12, 12);
            this.lblTime.Name = "lblTime";
            this.lblTime.Size = new System.Drawing.Size(247, 36);
            this.lblTime.TabIndex = 2;
            this.lblTime.Text = "08:08:08";
            this.lblTime.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // tmr
            // 
            this.tmr.Enabled = true;
            this.tmr.Interval = 1000;
            this.tmr.Tick += new System.EventHandler(this.tmr_Tick);
            // 
            // FMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(273, 436);
            this.ContextMenuStrip = this.cmsWeather;
            this.Controls.Add(this.grpCurr);
            this.Controls.Add(this.grpTime);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.btnSet);
            this.Controls.Add(this.btnIE);
            this.Controls.Add(this.btnRef);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FMain";
            this.Opacity = 0.8D;
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "Часы...";
            this.Load += new System.EventHandler(this.FMain_Load);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.FMain_MouseDown);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.FMain_MouseMove);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.FMain_MouseUp);
            this.cmsWeather.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.grpCurr.ResumeLayout(false);
            this.grpTime.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnRef;
        private System.Windows.Forms.Button btnIE;
        private System.Windows.Forms.Button btnSet;
        private System.Windows.Forms.NotifyIcon ntfIcon;
        private System.Windows.Forms.ContextMenuStrip cmsWeather;
        private System.Windows.Forms.ToolStripMenuItem cmsWeather_Refr;
        private System.Windows.Forms.ToolStripMenuItem cmsWeather_IE;
        private System.Windows.Forms.ToolStripMenuItem cmsWeather_Set;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem cmsWeather_Exit;
        private System.Windows.Forms.ToolStripMenuItem cmsWeather_Hide;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RichTextBox rtbDescription;
        private System.Windows.Forms.ListBox lstBoxState;
        private System.Windows.Forms.GroupBox grpCurr;
        private System.Windows.Forms.MonthCalendar mCalCurr;
        private System.Windows.Forms.GroupBox grpTime;
        private System.Windows.Forms.Label lblTime;
        private System.Windows.Forms.Timer tmr;
    }
}

