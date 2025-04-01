namespace Clock_csc_v2
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
            chkIsSleep = new CheckBox();
            chkIsWork = new CheckBox();
            tmShutDown = new DateTimePicker();
            label1 = new Label();
            groupBox1 = new GroupBox();
            btnCancel = new Button();
            btnOK = new Button();
            SuspendLayout();
            // 
            // chkIsSleep
            // 
            chkIsSleep.FlatStyle = FlatStyle.System;
            chkIsSleep.ImeMode = ImeMode.NoControl;
            chkIsSleep.Location = new Point(50, 87);
            chkIsSleep.Name = "chkIsSleep";
            chkIsSleep.Size = new Size(184, 30);
            chkIsSleep.TabIndex = 14;
            chkIsSleep.Text = "Sleep";
            chkIsSleep.CheckedChanged += chkIsSleep_CheckedChanged;
            // 
            // chkIsWork
            // 
            chkIsWork.FlatStyle = FlatStyle.System;
            chkIsWork.ImeMode = ImeMode.NoControl;
            chkIsWork.Location = new Point(50, 43);
            chkIsWork.Name = "chkIsWork";
            chkIsWork.Size = new Size(184, 30);
            chkIsWork.TabIndex = 13;
            chkIsWork.Text = "checkBox1";
            chkIsWork.CheckedChanged += chkIsWork_CheckedChanged;
            // 
            // tmShutDown
            // 
            tmShutDown.CustomFormat = "HH:mm";
            tmShutDown.Format = DateTimePickerFormat.Custom;
            tmShutDown.Location = new Point(146, 7);
            tmShutDown.Name = "tmShutDown";
            tmShutDown.ShowUpDown = true;
            tmShutDown.Size = new Size(100, 27);
            tmShutDown.TabIndex = 12;
            tmShutDown.Value = new DateTime(2005, 7, 20, 10, 21, 0, 0);
            // 
            // label1
            // 
            label1.FlatStyle = FlatStyle.System;
            label1.ImeMode = ImeMode.NoControl;
            label1.Location = new Point(22, 12);
            label1.Name = "label1";
            label1.Size = new Size(118, 25);
            label1.TabIndex = 11;
            label1.Text = "Time shut down";
            // 
            // groupBox1
            // 
            groupBox1.FlatStyle = FlatStyle.System;
            groupBox1.Location = new Point(0, 73);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(252, 6);
            groupBox1.TabIndex = 10;
            groupBox1.TabStop = false;
            // 
            // btnCancel
            // 
            btnCancel.FlatStyle = FlatStyle.System;
            btnCancel.ImeMode = ImeMode.NoControl;
            btnCancel.Location = new Point(134, 140);
            btnCancel.Name = "btnCancel";
            btnCancel.Size = new Size(105, 35);
            btnCancel.TabIndex = 9;
            btnCancel.Text = "Cancel";
            btnCancel.Click += btnCancel_Click;
            // 
            // btnOK
            // 
            btnOK.FlatStyle = FlatStyle.System;
            btnOK.ImeMode = ImeMode.NoControl;
            btnOK.Location = new Point(16, 140);
            btnOK.Name = "btnOK";
            btnOK.Size = new Size(105, 35);
            btnOK.TabIndex = 8;
            btnOK.Text = "OK";
            btnOK.Click += btnOK_Click;
            // 
            // FShutDown
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(259, 188);
            Controls.Add(chkIsSleep);
            Controls.Add(chkIsWork);
            Controls.Add(tmShutDown);
            Controls.Add(label1);
            Controls.Add(groupBox1);
            Controls.Add(btnCancel);
            Controls.Add(btnOK);
            DoubleBuffered = true;
            FormBorderStyle = FormBorderStyle.FixedToolWindow;
            MaximizeBox = false;
            MinimizeBox = false;
            Name = "FShutDown";
            Opacity = 0.85D;
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Shut down";
            ResumeLayout(false);
        }

        #endregion

        private CheckBox chkIsSleep;
        private CheckBox chkIsWork;
        private DateTimePicker tmShutDown;
        private Label label1;
        private GroupBox groupBox1;
        private Button btnCancel;
        private Button btnOK;
    }
}