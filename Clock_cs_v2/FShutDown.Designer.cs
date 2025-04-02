namespace Clock_cs_v2
{
    partial class FShutDown
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
            this.chkIsSleep = new System.Windows.Forms.CheckBox();
            this.chkIsWork = new System.Windows.Forms.CheckBox();
            this.tmShutDown = new System.Windows.Forms.DateTimePicker();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnOK = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // chkIsSleep
            // 
            this.chkIsSleep.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.chkIsSleep.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.chkIsSleep.Location = new System.Drawing.Point(56, 69);
            this.chkIsSleep.Name = "chkIsSleep";
            this.chkIsSleep.Size = new System.Drawing.Size(158, 23);
            this.chkIsSleep.TabIndex = 14;
            this.chkIsSleep.Text = "Sleep";
            this.chkIsSleep.CheckedChanged += new System.EventHandler(this.chkIsSleep_CheckedChanged);
            // 
            // chkIsWork
            // 
            this.chkIsWork.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.chkIsWork.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.chkIsWork.Location = new System.Drawing.Point(56, 36);
            this.chkIsWork.Name = "chkIsWork";
            this.chkIsWork.Size = new System.Drawing.Size(158, 23);
            this.chkIsWork.TabIndex = 13;
            this.chkIsWork.Text = "checkBox1";
            this.chkIsWork.CheckedChanged += new System.EventHandler(this.chkIsWork_CheckedChanged);
            // 
            // tmShutDown
            // 
            this.tmShutDown.CustomFormat = "HH:mm";
            this.tmShutDown.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
            this.tmShutDown.Location = new System.Drawing.Point(138, 9);
            this.tmShutDown.Name = "tmShutDown";
            this.tmShutDown.ShowUpDown = true;
            this.tmShutDown.Size = new System.Drawing.Size(86, 22);
            this.tmShutDown.TabIndex = 12;
            this.tmShutDown.Value = new System.DateTime(2005, 7, 20, 10, 21, 0, 0);
            // 
            // label1
            // 
            this.label1.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.label1.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.label1.Location = new System.Drawing.Point(32, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(101, 19);
            this.label1.TabIndex = 11;
            this.label1.Text = "Time shut down";
            // 
            // groupBox1
            // 
            this.groupBox1.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.groupBox1.Location = new System.Drawing.Point(13, 59);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(216, 4);
            this.groupBox1.TabIndex = 10;
            this.groupBox1.TabStop = false;
            // 
            // btnCancel
            // 
            this.btnCancel.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.btnCancel.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.btnCancel.Location = new System.Drawing.Point(128, 109);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(90, 26);
            this.btnCancel.TabIndex = 9;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnOK
            // 
            this.btnOK.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.btnOK.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.btnOK.Location = new System.Drawing.Point(27, 109);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(90, 26);
            this.btnOK.TabIndex = 8;
            this.btnOK.Text = "OK";
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // FShutDown
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(242, 149);
            this.Controls.Add(this.chkIsSleep);
            this.Controls.Add(this.chkIsWork);
            this.Controls.Add(this.tmShutDown);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnOK);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FShutDown";
            this.Opacity = 0.85D;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Shut Down";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.CheckBox chkIsSleep;
        private System.Windows.Forms.CheckBox chkIsWork;
        private System.Windows.Forms.DateTimePicker tmShutDown;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnOK;
    }
}