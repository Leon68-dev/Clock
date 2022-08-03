namespace Clock
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
            this.components = new System.ComponentModel.Container();
            this.trckBarOpacity = new System.Windows.Forms.TrackBar();
            this.btnOk = new System.Windows.Forms.Button();
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.chkDay = new System.Windows.Forms.CheckBox();
            this.chkDate = new System.Windows.Forms.CheckBox();
            this.chkGMT = new System.Windows.Forms.CheckBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.chkBorder = new System.Windows.Forms.CheckBox();
            this.chkAlwaysOnTop = new System.Windows.Forms.CheckBox();
            this.chkTransparent = new System.Windows.Forms.CheckBox();
            this.chkMoving = new System.Windows.Forms.CheckBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.chkSound = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.trckBarOpacity)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // trckBarOpacity
            // 
            this.trckBarOpacity.AutoSize = false;
            this.trckBarOpacity.LargeChange = 20;
            this.trckBarOpacity.Location = new System.Drawing.Point(5, 22);
            this.trckBarOpacity.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.trckBarOpacity.Maximum = 100;
            this.trckBarOpacity.Name = "trckBarOpacity";
            this.trckBarOpacity.Size = new System.Drawing.Size(480, 55);
            this.trckBarOpacity.SmallChange = 5;
            this.trckBarOpacity.TabIndex = 0;
            this.trckBarOpacity.TickFrequency = 5;
            this.trckBarOpacity.Value = 85;
            this.trckBarOpacity.ValueChanged += new System.EventHandler(this.trckBarOpacity_ValueChanged);
            // 
            // btnOk
            // 
            this.btnOk.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.btnOk.Location = new System.Drawing.Point(400, 166);
            this.btnOk.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.btnOk.Name = "btnOk";
            this.btnOk.Size = new System.Drawing.Size(100, 35);
            this.btnOk.TabIndex = 2;
            this.btnOk.Text = "Ok";
            this.btnOk.UseVisualStyleBackColor = true;
            this.btnOk.Click += new System.EventHandler(this.btnOk_Click);
            // 
            // chkDay
            // 
            this.chkDay.AutoSize = true;
            this.chkDay.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.chkDay.Location = new System.Drawing.Point(11, 55);
            this.chkDay.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.chkDay.Name = "chkDay";
            this.chkDay.Size = new System.Drawing.Size(66, 25);
            this.chkDay.TabIndex = 6;
            this.chkDay.Text = "Day";
            this.chkDay.UseVisualStyleBackColor = true;
            // 
            // chkDate
            // 
            this.chkDate.AutoSize = true;
            this.chkDate.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.chkDate.Location = new System.Drawing.Point(11, 86);
            this.chkDate.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.chkDate.Name = "chkDate";
            this.chkDate.Size = new System.Drawing.Size(72, 25);
            this.chkDate.TabIndex = 5;
            this.chkDate.Text = "Date";
            this.chkDate.UseVisualStyleBackColor = true;
            // 
            // chkGMT
            // 
            this.chkGMT.AutoSize = true;
            this.chkGMT.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.chkGMT.Location = new System.Drawing.Point(11, 25);
            this.chkGMT.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.chkGMT.Name = "chkGMT";
            this.chkGMT.Size = new System.Drawing.Size(71, 25);
            this.chkGMT.TabIndex = 4;
            this.chkGMT.Text = "GMT";
            this.chkGMT.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.groupBox3);
            this.groupBox1.Controls.Add(this.chkBorder);
            this.groupBox1.Controls.Add(this.chkAlwaysOnTop);
            this.groupBox1.Controls.Add(this.chkTransparent);
            this.groupBox1.Controls.Add(this.chkMoving);
            this.groupBox1.Controls.Add(this.chkDate);
            this.groupBox1.Controls.Add(this.chkDay);
            this.groupBox1.Controls.Add(this.chkGMT);
            this.groupBox1.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.groupBox1.Location = new System.Drawing.Point(5, 86);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox1.Size = new System.Drawing.Size(320, 118);
            this.groupBox1.TabIndex = 7;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Dial";
            // 
            // groupBox3
            // 
            this.groupBox3.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.groupBox3.Location = new System.Drawing.Point(75, 0);
            this.groupBox3.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox3.Size = new System.Drawing.Size(3, 118);
            this.groupBox3.TabIndex = 9;
            this.groupBox3.TabStop = false;
            // 
            // chkBorder
            // 
            this.chkBorder.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.chkBorder.Location = new System.Drawing.Point(197, 55);
            this.chkBorder.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.chkBorder.Name = "chkBorder";
            this.chkBorder.Size = new System.Drawing.Size(80, 28);
            this.chkBorder.TabIndex = 12;
            this.chkBorder.Text = "Border";
            this.chkBorder.UseVisualStyleBackColor = true;
            // 
            // chkAlwaysOnTop
            // 
            this.chkAlwaysOnTop.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.chkAlwaysOnTop.Location = new System.Drawing.Point(197, 25);
            this.chkAlwaysOnTop.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.chkAlwaysOnTop.Name = "chkAlwaysOnTop";
            this.chkAlwaysOnTop.Size = new System.Drawing.Size(117, 28);
            this.chkAlwaysOnTop.TabIndex = 10;
            this.chkAlwaysOnTop.Text = "Always on top";
            this.chkAlwaysOnTop.UseVisualStyleBackColor = true;
            // 
            // chkTransparent
            // 
            this.chkTransparent.Enabled = false;
            this.chkTransparent.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.chkTransparent.Location = new System.Drawing.Point(85, 55);
            this.chkTransparent.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.chkTransparent.Name = "chkTransparent";
            this.chkTransparent.Size = new System.Drawing.Size(111, 31);
            this.chkTransparent.TabIndex = 11;
            this.chkTransparent.Text = "Transparent";
            this.chkTransparent.UseVisualStyleBackColor = true;
            // 
            // chkMoving
            // 
            this.chkMoving.AutoSize = true;
            this.chkMoving.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.chkMoving.Location = new System.Drawing.Point(85, 25);
            this.chkMoving.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.chkMoving.Name = "chkMoving";
            this.chkMoving.Size = new System.Drawing.Size(90, 25);
            this.chkMoving.TabIndex = 9;
            this.chkMoving.Text = "Moving";
            this.chkMoving.UseVisualStyleBackColor = true;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.trckBarOpacity);
            this.groupBox2.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.groupBox2.Location = new System.Drawing.Point(5, 0);
            this.groupBox2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox2.Size = new System.Drawing.Size(496, 81);
            this.groupBox2.TabIndex = 8;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Opacity";
            // 
            // chkSound
            // 
            this.chkSound.AutoSize = true;
            this.chkSound.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.chkSound.Location = new System.Drawing.Point(336, 111);
            this.chkSound.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.chkSound.Name = "chkSound";
            this.chkSound.Size = new System.Drawing.Size(82, 25);
            this.chkSound.TabIndex = 13;
            this.chkSound.Text = "Sound";
            this.chkSound.UseVisualStyleBackColor = true;
            // 
            // FSetup
            // 
            this.AcceptButton = this.btnOk;
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(508, 212);
            this.Controls.Add(this.chkSound);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.btnOk);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Name = "FSetup";
            this.Opacity = 0.85D;
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Setup";
            ((System.ComponentModel.ISupportInitialize)(this.trckBarOpacity)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

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