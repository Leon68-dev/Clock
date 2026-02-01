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
            chkSound = new CheckBox();
            groupBox2 = new GroupBox();
            trckBarOpacity = new TrackBar();
            groupBox1 = new GroupBox();
            groupBox3 = new GroupBox();
            chkBorder = new CheckBox();
            chkAlwaysOnTop = new CheckBox();
            chkTransparent = new CheckBox();
            chkMoving = new CheckBox();
            chkDate = new CheckBox();
            chkDay = new CheckBox();
            chkGMT = new CheckBox();
            btnOk = new Button();
            toolTip1 = new ToolTip(components);
            chkSmooth = new CheckBox();
            groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)trckBarOpacity).BeginInit();
            groupBox1.SuspendLayout();
            SuspendLayout();
            // 
            // chkSound
            // 
            chkSound.AutoSize = true;
            chkSound.FlatStyle = FlatStyle.System;
            chkSound.Location = new Point(336, 114);
            chkSound.Margin = new Padding(4, 5, 4, 5);
            chkSound.Name = "chkSound";
            chkSound.Size = new Size(82, 25);
            chkSound.TabIndex = 17;
            chkSound.Text = "Sound";
            chkSound.UseVisualStyleBackColor = true;
            // 
            // groupBox2
            // 
            groupBox2.Controls.Add(trckBarOpacity);
            groupBox2.FlatStyle = FlatStyle.System;
            groupBox2.Location = new Point(5, 3);
            groupBox2.Margin = new Padding(4, 5, 4, 5);
            groupBox2.Name = "groupBox2";
            groupBox2.Padding = new Padding(4, 5, 4, 5);
            groupBox2.Size = new Size(496, 81);
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
            trckBarOpacity.Size = new Size(480, 55);
            trckBarOpacity.SmallChange = 5;
            trckBarOpacity.TabIndex = 0;
            trckBarOpacity.TickFrequency = 5;
            trckBarOpacity.Value = 85;
            trckBarOpacity.ValueChanged += trckBarOpacity_ValueChanged;
            // 
            // groupBox1
            // 
            groupBox1.Controls.Add(chkSmooth);
            groupBox1.Controls.Add(groupBox3);
            groupBox1.Controls.Add(chkBorder);
            groupBox1.Controls.Add(chkAlwaysOnTop);
            groupBox1.Controls.Add(chkTransparent);
            groupBox1.Controls.Add(chkMoving);
            groupBox1.Controls.Add(chkDate);
            groupBox1.Controls.Add(chkDay);
            groupBox1.Controls.Add(chkGMT);
            groupBox1.FlatStyle = FlatStyle.System;
            groupBox1.Location = new Point(5, 89);
            groupBox1.Margin = new Padding(4, 5, 4, 5);
            groupBox1.Name = "groupBox1";
            groupBox1.Padding = new Padding(4, 5, 4, 5);
            groupBox1.Size = new Size(320, 118);
            groupBox1.TabIndex = 15;
            groupBox1.TabStop = false;
            groupBox1.Text = "Dial";
            // 
            // groupBox3
            // 
            groupBox3.FlatStyle = FlatStyle.System;
            groupBox3.Location = new Point(75, 0);
            groupBox3.Margin = new Padding(4, 5, 4, 5);
            groupBox3.Name = "groupBox3";
            groupBox3.Padding = new Padding(4, 5, 4, 5);
            groupBox3.Size = new Size(3, 118);
            groupBox3.TabIndex = 9;
            groupBox3.TabStop = false;
            // 
            // chkBorder
            // 
            chkBorder.FlatStyle = FlatStyle.System;
            chkBorder.Location = new Point(197, 55);
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
            chkAlwaysOnTop.Location = new Point(197, 25);
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
            chkTransparent.Location = new Point(85, 55);
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
            chkMoving.Location = new Point(86, 27);
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
            chkDate.Location = new Point(12, 88);
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
            chkDay.Location = new Point(12, 57);
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
            chkGMT.Location = new Point(12, 27);
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
            btnOk.Location = new Point(400, 169);
            btnOk.Margin = new Padding(4, 5, 4, 5);
            btnOk.Name = "btnOk";
            btnOk.Size = new Size(100, 35);
            btnOk.TabIndex = 14;
            btnOk.Text = "Ok";
            btnOk.UseVisualStyleBackColor = true;
            btnOk.Click += btnOk_Click;
            // 
            // chkSmooth
            // 
            chkSmooth.FlatStyle = FlatStyle.System;
            chkSmooth.Location = new Point(85, 85);
            chkSmooth.Margin = new Padding(4, 5, 4, 5);
            chkSmooth.Name = "chkSmooth";
            chkSmooth.Size = new Size(111, 31);
            chkSmooth.TabIndex = 13;
            chkSmooth.Text = "Smooth";
            chkSmooth.UseVisualStyleBackColor = true;
            // 
            // FSetup
            // 
            AcceptButton = btnOk;
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(508, 212);
            Controls.Add(chkSound);
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
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private CheckBox chkSound;
        private GroupBox groupBox2;
        private TrackBar trckBarOpacity;
        private GroupBox groupBox1;
        private GroupBox groupBox3;
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
    }
}