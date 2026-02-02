namespace Clock_csc_v2
{
    partial class FSetup
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
            components = new System.ComponentModel.Container();
            groupBox2 = new GroupBox();
            trckBarOpacity = new TrackBar();
            groupBox1 = new GroupBox();
            chkSmooth = new CheckBox();
            chkBorder = new CheckBox();
            chkAlwaysOnTop = new CheckBox();
            chkTransparent = new CheckBox();
            chkMoving = new CheckBox();
            chkDate = new CheckBox();
            chkDay = new CheckBox();
            chkGMT = new CheckBox();
            btnOk = new Button();
            toolTip1 = new ToolTip(components);
            chkTickTack = new CheckBox();
            chkHours = new CheckBox();
            chk1530 = new CheckBox();
            groupBox3 = new GroupBox();
            groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)trckBarOpacity).BeginInit();
            groupBox1.SuspendLayout();
            groupBox3.SuspendLayout();
            SuspendLayout();
            // 
            // groupBox2
            // 
            groupBox2.Controls.Add(trckBarOpacity);
            groupBox2.FlatStyle = FlatStyle.System;
            groupBox2.Location = new Point(6, 126);
            groupBox2.Margin = new Padding(4, 5, 4, 5);
            groupBox2.Name = "groupBox2";
            groupBox2.Padding = new Padding(4, 5, 4, 5);
            groupBox2.Size = new Size(320, 72);
            groupBox2.TabIndex = 16;
            groupBox2.TabStop = false;
            groupBox2.Text = "Opacity";
            // 
            // trckBarOpacity
            // 
            trckBarOpacity.AutoSize = false;
            trckBarOpacity.LargeChange = 20;
            trckBarOpacity.Location = new Point(5, 22);
            trckBarOpacity.Margin = new Padding(4, 5, 4, 5);
            trckBarOpacity.Maximum = 100;
            trckBarOpacity.Name = "trckBarOpacity";
            trckBarOpacity.Size = new Size(308, 38);
            trckBarOpacity.SmallChange = 5;
            trckBarOpacity.TabIndex = 0;
            trckBarOpacity.TickFrequency = 5;
            trckBarOpacity.Value = 85;
            trckBarOpacity.ValueChanged += trckBarOpacity_ValueChanged;
            // 
            // groupBox1
            // 
            groupBox1.Controls.Add(chkSmooth);
            groupBox1.Controls.Add(chkBorder);
            groupBox1.Controls.Add(chkAlwaysOnTop);
            groupBox1.Controls.Add(chkTransparent);
            groupBox1.Controls.Add(chkMoving);
            groupBox1.Controls.Add(chkDate);
            groupBox1.Controls.Add(chkDay);
            groupBox1.Controls.Add(chkGMT);
            groupBox1.FlatStyle = FlatStyle.System;
            groupBox1.Location = new Point(6, 6);
            groupBox1.Margin = new Padding(4, 5, 4, 5);
            groupBox1.Name = "groupBox1";
            groupBox1.Padding = new Padding(4, 5, 4, 5);
            groupBox1.Size = new Size(320, 118);
            groupBox1.TabIndex = 15;
            groupBox1.TabStop = false;
            groupBox1.Text = "UI";
            // 
            // chkSmooth
            // 
            chkSmooth.FlatStyle = FlatStyle.System;
            chkSmooth.Location = new Point(85, 80);
            chkSmooth.Margin = new Padding(4, 5, 4, 5);
            chkSmooth.Name = "chkSmooth";
            chkSmooth.Size = new Size(111, 31);
            chkSmooth.TabIndex = 13;
            chkSmooth.Text = "Smooth";
            chkSmooth.UseVisualStyleBackColor = true;
            // 
            // chkBorder
            // 
            chkBorder.FlatStyle = FlatStyle.System;
            chkBorder.Location = new Point(197, 50);
            chkBorder.Margin = new Padding(4, 5, 4, 5);
            chkBorder.Name = "chkBorder";
            chkBorder.Size = new Size(80, 28);
            chkBorder.TabIndex = 12;
            chkBorder.Text = "Border";
            chkBorder.UseVisualStyleBackColor = true;
            // 
            // chkAlwaysOnTop
            // 
            chkAlwaysOnTop.FlatStyle = FlatStyle.System;
            chkAlwaysOnTop.Location = new Point(197, 20);
            chkAlwaysOnTop.Margin = new Padding(4, 5, 4, 5);
            chkAlwaysOnTop.Name = "chkAlwaysOnTop";
            chkAlwaysOnTop.Size = new Size(117, 28);
            chkAlwaysOnTop.TabIndex = 10;
            chkAlwaysOnTop.Text = "Always on top";
            chkAlwaysOnTop.UseVisualStyleBackColor = true;
            // 
            // chkTransparent
            // 
            chkTransparent.FlatStyle = FlatStyle.System;
            chkTransparent.Location = new Point(85, 50);
            chkTransparent.Margin = new Padding(4, 5, 4, 5);
            chkTransparent.Name = "chkTransparent";
            chkTransparent.Size = new Size(111, 31);
            chkTransparent.TabIndex = 11;
            chkTransparent.Text = "Transparent";
            chkTransparent.UseVisualStyleBackColor = true;
            // 
            // chkMoving
            // 
            chkMoving.AutoSize = true;
            chkMoving.FlatStyle = FlatStyle.System;
            chkMoving.Location = new Point(86, 22);
            chkMoving.Margin = new Padding(4, 5, 4, 5);
            chkMoving.Name = "chkMoving";
            chkMoving.Size = new Size(90, 25);
            chkMoving.TabIndex = 9;
            chkMoving.Text = "Moving";
            chkMoving.UseVisualStyleBackColor = true;
            // 
            // chkDate
            // 
            chkDate.AutoSize = true;
            chkDate.FlatStyle = FlatStyle.System;
            chkDate.Location = new Point(12, 83);
            chkDate.Margin = new Padding(4, 5, 4, 5);
            chkDate.Name = "chkDate";
            chkDate.Size = new Size(72, 25);
            chkDate.TabIndex = 5;
            chkDate.Text = "Date";
            chkDate.UseVisualStyleBackColor = true;
            // 
            // chkDay
            // 
            chkDay.AutoSize = true;
            chkDay.FlatStyle = FlatStyle.System;
            chkDay.Location = new Point(12, 52);
            chkDay.Margin = new Padding(4, 5, 4, 5);
            chkDay.Name = "chkDay";
            chkDay.Size = new Size(66, 25);
            chkDay.TabIndex = 6;
            chkDay.Text = "Day";
            chkDay.UseVisualStyleBackColor = true;
            // 
            // chkGMT
            // 
            chkGMT.AutoSize = true;
            chkGMT.FlatStyle = FlatStyle.System;
            chkGMT.Location = new Point(12, 22);
            chkGMT.Margin = new Padding(4, 5, 4, 5);
            chkGMT.Name = "chkGMT";
            chkGMT.Size = new Size(71, 25);
            chkGMT.TabIndex = 4;
            chkGMT.Text = "GMT";
            chkGMT.UseVisualStyleBackColor = true;
            // 
            // btnOk
            // 
            btnOk.FlatStyle = FlatStyle.System;
            btnOk.Location = new Point(341, 163);
            btnOk.Margin = new Padding(4, 5, 4, 5);
            btnOk.Name = "btnOk";
            btnOk.Size = new Size(99, 35);
            btnOk.TabIndex = 14;
            btnOk.Text = "Ok";
            btnOk.UseVisualStyleBackColor = true;
            btnOk.Click += btnOk_Click;
            // 
            // chkTickTack
            // 
            chkTickTack.FlatStyle = FlatStyle.System;
            chkTickTack.Location = new Point(12, 26);
            chkTickTack.Margin = new Padding(4, 5, 4, 5);
            chkTickTack.Name = "chkTickTack";
            chkTickTack.Size = new Size(82, 25);
            chkTickTack.TabIndex = 18;
            chkTickTack.Text = "Tick-Tack";
            chkTickTack.UseVisualStyleBackColor = true;
            // 
            // chkHours
            // 
            chkHours.FlatStyle = FlatStyle.System;
            chkHours.Location = new Point(12, 86);
            chkHours.Margin = new Padding(4, 5, 4, 5);
            chkHours.Name = "chkHours";
            chkHours.Size = new Size(63, 25);
            chkHours.TabIndex = 19;
            chkHours.Text = "Hours";
            chkHours.UseVisualStyleBackColor = true;
            // 
            // chk1530
            // 
            chk1530.FlatStyle = FlatStyle.System;
            chk1530.Location = new Point(12, 55);
            chk1530.Margin = new Padding(4, 5, 4, 5);
            chk1530.Name = "chk1530";
            chk1530.Size = new Size(61, 25);
            chk1530.TabIndex = 20;
            chk1530.Text = "15-30";
            chk1530.UseVisualStyleBackColor = true;
            // 
            // groupBox3
            // 
            groupBox3.Controls.Add(chk1530);
            groupBox3.Controls.Add(chkTickTack);
            groupBox3.Controls.Add(chkHours);
            groupBox3.Location = new Point(334, 6);
            groupBox3.Name = "groupBox3";
            groupBox3.Size = new Size(105, 118);
            groupBox3.TabIndex = 21;
            groupBox3.TabStop = false;
            groupBox3.Text = "Sounds";
            // 
            // FSetup
            // 
            AcceptButton = btnOk;
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(446, 207);
            Controls.Add(groupBox3);
            Controls.Add(groupBox2);
            Controls.Add(groupBox1);
            Controls.Add(btnOk);
            DoubleBuffered = true;
            FormBorderStyle = FormBorderStyle.FixedToolWindow;
            Name = "FSetup";
            Opacity = 0.85D;
            ShowIcon = false;
            ShowInTaskbar = false;
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Setup";
            groupBox2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)trckBarOpacity).EndInit();
            groupBox1.ResumeLayout(false);
            groupBox1.PerformLayout();
            groupBox3.ResumeLayout(false);
            ResumeLayout(false);
        }

        #endregion

        private GroupBox groupBox2;
        private TrackBar trckBarOpacity;
        private GroupBox groupBox1;
        private CheckBox chkBorder;
        private CheckBox chkAlwaysOnTop;
        private CheckBox chkTransparent;
        private CheckBox chkMoving;
        private CheckBox chkDate;
        private CheckBox chkDay;
        private CheckBox chkGMT;
        private Button btnOk;
        private ToolTip toolTip1;
        private CheckBox chkSmooth;
        private CheckBox chkTickTack;
        private CheckBox chkHours;
        private CheckBox chk1530;
        private GroupBox groupBox3;
    }
}