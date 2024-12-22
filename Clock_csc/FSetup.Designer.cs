namespace Clock_csc
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
            trckBarOpacity = new System.Windows.Forms.TrackBar();
            btnOk = new System.Windows.Forms.Button();
            toolTip1 = new System.Windows.Forms.ToolTip(components);
            chkDay = new System.Windows.Forms.CheckBox();
            chkDate = new System.Windows.Forms.CheckBox();
            chkGMT = new System.Windows.Forms.CheckBox();
            groupBox1 = new System.Windows.Forms.GroupBox();
            groupBox3 = new System.Windows.Forms.GroupBox();
            chkBorder = new System.Windows.Forms.CheckBox();
            chkAlwaysOnTop = new System.Windows.Forms.CheckBox();
            chkTransparent = new System.Windows.Forms.CheckBox();
            chkMoving = new System.Windows.Forms.CheckBox();
            groupBox2 = new System.Windows.Forms.GroupBox();
            chkSound = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)trckBarOpacity).BeginInit();
            groupBox1.SuspendLayout();
            groupBox2.SuspendLayout();
            SuspendLayout();
            // 
            // trckBarOpacity
            // 
            trckBarOpacity.AutoSize = false;
            trckBarOpacity.LargeChange = 20;
            trckBarOpacity.Location = new System.Drawing.Point(5, 22);
            trckBarOpacity.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            trckBarOpacity.Maximum = 100;
            trckBarOpacity.Name = "trckBarOpacity";
            trckBarOpacity.Size = new System.Drawing.Size(480, 55);
            trckBarOpacity.SmallChange = 5;
            trckBarOpacity.TabIndex = 0;
            trckBarOpacity.TickFrequency = 5;
            trckBarOpacity.Value = 85;
            trckBarOpacity.ValueChanged += trckBarOpacity_ValueChanged;
            // 
            // btnOk
            // 
            btnOk.FlatStyle = System.Windows.Forms.FlatStyle.System;
            btnOk.Location = new System.Drawing.Point(400, 166);
            btnOk.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            btnOk.Name = "btnOk";
            btnOk.Size = new System.Drawing.Size(100, 35);
            btnOk.TabIndex = 2;
            btnOk.Text = "Ok";
            btnOk.UseVisualStyleBackColor = true;
            btnOk.Click += btnOk_Click;
            // 
            // chkDay
            // 
            chkDay.AutoSize = true;
            chkDay.FlatStyle = System.Windows.Forms.FlatStyle.System;
            chkDay.Location = new System.Drawing.Point(11, 55);
            chkDay.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            chkDay.Name = "chkDay";
            chkDay.Size = new System.Drawing.Size(66, 25);
            chkDay.TabIndex = 6;
            chkDay.Text = "Day";
            chkDay.UseVisualStyleBackColor = true;
            // 
            // chkDate
            // 
            chkDate.AutoSize = true;
            chkDate.FlatStyle = System.Windows.Forms.FlatStyle.System;
            chkDate.Location = new System.Drawing.Point(11, 86);
            chkDate.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            chkDate.Name = "chkDate";
            chkDate.Size = new System.Drawing.Size(72, 25);
            chkDate.TabIndex = 5;
            chkDate.Text = "Date";
            chkDate.UseVisualStyleBackColor = true;
            // 
            // chkGMT
            // 
            chkGMT.AutoSize = true;
            chkGMT.FlatStyle = System.Windows.Forms.FlatStyle.System;
            chkGMT.Location = new System.Drawing.Point(11, 25);
            chkGMT.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            chkGMT.Name = "chkGMT";
            chkGMT.Size = new System.Drawing.Size(71, 25);
            chkGMT.TabIndex = 4;
            chkGMT.Text = "GMT";
            chkGMT.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            groupBox1.Controls.Add(groupBox3);
            groupBox1.Controls.Add(chkBorder);
            groupBox1.Controls.Add(chkAlwaysOnTop);
            groupBox1.Controls.Add(chkTransparent);
            groupBox1.Controls.Add(chkMoving);
            groupBox1.Controls.Add(chkDate);
            groupBox1.Controls.Add(chkDay);
            groupBox1.Controls.Add(chkGMT);
            groupBox1.FlatStyle = System.Windows.Forms.FlatStyle.System;
            groupBox1.Location = new System.Drawing.Point(5, 86);
            groupBox1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            groupBox1.Name = "groupBox1";
            groupBox1.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            groupBox1.Size = new System.Drawing.Size(320, 118);
            groupBox1.TabIndex = 7;
            groupBox1.TabStop = false;
            groupBox1.Text = "Dial";
            // 
            // groupBox3
            // 
            groupBox3.FlatStyle = System.Windows.Forms.FlatStyle.System;
            groupBox3.Location = new System.Drawing.Point(75, 0);
            groupBox3.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            groupBox3.Name = "groupBox3";
            groupBox3.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            groupBox3.Size = new System.Drawing.Size(3, 118);
            groupBox3.TabIndex = 9;
            groupBox3.TabStop = false;
            // 
            // chkBorder
            // 
            chkBorder.FlatStyle = System.Windows.Forms.FlatStyle.System;
            chkBorder.Location = new System.Drawing.Point(197, 55);
            chkBorder.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            chkBorder.Name = "chkBorder";
            chkBorder.Size = new System.Drawing.Size(80, 28);
            chkBorder.TabIndex = 12;
            chkBorder.Text = "Border";
            chkBorder.UseVisualStyleBackColor = true;
            // 
            // chkAlwaysOnTop
            // 
            chkAlwaysOnTop.FlatStyle = System.Windows.Forms.FlatStyle.System;
            chkAlwaysOnTop.Location = new System.Drawing.Point(197, 25);
            chkAlwaysOnTop.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            chkAlwaysOnTop.Name = "chkAlwaysOnTop";
            chkAlwaysOnTop.Size = new System.Drawing.Size(117, 28);
            chkAlwaysOnTop.TabIndex = 10;
            chkAlwaysOnTop.Text = "Always on top";
            chkAlwaysOnTop.UseVisualStyleBackColor = true;
            // 
            // chkTransparent
            // 
            chkTransparent.FlatStyle = System.Windows.Forms.FlatStyle.System;
            chkTransparent.Location = new System.Drawing.Point(85, 55);
            chkTransparent.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            chkTransparent.Name = "chkTransparent";
            chkTransparent.Size = new System.Drawing.Size(111, 31);
            chkTransparent.TabIndex = 11;
            chkTransparent.Text = "Transparent";
            chkTransparent.UseVisualStyleBackColor = true;
            // 
            // chkMoving
            // 
            chkMoving.AutoSize = true;
            chkMoving.FlatStyle = System.Windows.Forms.FlatStyle.System;
            chkMoving.Location = new System.Drawing.Point(85, 25);
            chkMoving.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            chkMoving.Name = "chkMoving";
            chkMoving.Size = new System.Drawing.Size(90, 25);
            chkMoving.TabIndex = 9;
            chkMoving.Text = "Moving";
            chkMoving.UseVisualStyleBackColor = true;
            // 
            // groupBox2
            // 
            groupBox2.Controls.Add(trckBarOpacity);
            groupBox2.FlatStyle = System.Windows.Forms.FlatStyle.System;
            groupBox2.Location = new System.Drawing.Point(5, 0);
            groupBox2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            groupBox2.Name = "groupBox2";
            groupBox2.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            groupBox2.Size = new System.Drawing.Size(496, 81);
            groupBox2.TabIndex = 8;
            groupBox2.TabStop = false;
            groupBox2.Text = "Opacity";
            // 
            // chkSound
            // 
            chkSound.AutoSize = true;
            chkSound.FlatStyle = System.Windows.Forms.FlatStyle.System;
            chkSound.Location = new System.Drawing.Point(336, 111);
            chkSound.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            chkSound.Name = "chkSound";
            chkSound.Size = new System.Drawing.Size(82, 25);
            chkSound.TabIndex = 13;
            chkSound.Text = "Sound";
            chkSound.UseVisualStyleBackColor = true;
            // 
            // FSetup
            // 
            AcceptButton = btnOk;
            AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            ClientSize = new System.Drawing.Size(508, 212);
            Controls.Add(chkSound);
            Controls.Add(groupBox2);
            Controls.Add(groupBox1);
            Controls.Add(btnOk);
            DoubleBuffered = true;
            FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            Name = "FSetup";
            Opacity = 0.85D;
            ShowIcon = false;
            ShowInTaskbar = false;
            StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            Text = "Setup";
            ((System.ComponentModel.ISupportInitialize)trckBarOpacity).EndInit();
            groupBox1.ResumeLayout(false);
            groupBox1.PerformLayout();
            groupBox2.ResumeLayout(false);
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private System.Windows.Forms.TrackBar trckBarOpacity;
        private System.Windows.Forms.Button btnOk;
        private System.Windows.Forms.ToolTip toolTip1;
        private System.Windows.Forms.CheckBox chkDay;
        private System.Windows.Forms.CheckBox chkDate;
        private System.Windows.Forms.CheckBox chkGMT;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.CheckBox chkMoving;
        private System.Windows.Forms.CheckBox chkAlwaysOnTop;
        private System.Windows.Forms.CheckBox chkTransparent;
        private System.Windows.Forms.CheckBox chkBorder;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.CheckBox chkSound;
    }
}