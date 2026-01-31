namespace Clock_csc_v2
{
    partial class FAbout
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FAbout));
            groupBox1 = new GroupBox();
            lblAvailablePhysicalMem = new Label();
            lblWinVersion = new Label();
            lblTotalPhysicalMem = new Label();
            label1 = new Label();
            button1 = new Button();
            lblCopyright = new Label();
            pictureBox1 = new PictureBox();
            label2 = new Label();
            groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)pictureBox1).BeginInit();
            SuspendLayout();
            // 
            // groupBox1
            // 
            groupBox1.Controls.Add(lblAvailablePhysicalMem);
            groupBox1.Controls.Add(lblWinVersion);
            groupBox1.Controls.Add(lblTotalPhysicalMem);
            groupBox1.FlatStyle = FlatStyle.System;
            groupBox1.Location = new Point(12, 103);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(437, 98);
            groupBox1.TabIndex = 11;
            groupBox1.TabStop = false;
            // 
            // lblAvailablePhysicalMem
            // 
            lblAvailablePhysicalMem.AutoSize = true;
            lblAvailablePhysicalMem.FlatStyle = FlatStyle.System;
            lblAvailablePhysicalMem.ImeMode = ImeMode.NoControl;
            lblAvailablePhysicalMem.Location = new Point(9, 66);
            lblAvailablePhysicalMem.Name = "lblAvailablePhysicalMem";
            lblAvailablePhysicalMem.Size = new Size(186, 20);
            lblAvailablePhysicalMem.TabIndex = 6;
            lblAvailablePhysicalMem.Text = "Available Physical Memory";
            // 
            // lblWinVersion
            // 
            lblWinVersion.AutoSize = true;
            lblWinVersion.FlatStyle = FlatStyle.System;
            lblWinVersion.ImeMode = ImeMode.NoControl;
            lblWinVersion.Location = new Point(9, 19);
            lblWinVersion.Name = "lblWinVersion";
            lblWinVersion.Size = new Size(122, 20);
            lblWinVersion.TabIndex = 4;
            lblWinVersion.Text = "Windows Version";
            // 
            // lblTotalPhysicalMem
            // 
            lblTotalPhysicalMem.AutoSize = true;
            lblTotalPhysicalMem.FlatStyle = FlatStyle.System;
            lblTotalPhysicalMem.ImeMode = ImeMode.NoControl;
            lblTotalPhysicalMem.Location = new Point(9, 43);
            lblTotalPhysicalMem.Name = "lblTotalPhysicalMem";
            lblTotalPhysicalMem.Size = new Size(157, 20);
            lblTotalPhysicalMem.TabIndex = 5;
            lblTotalPhysicalMem.Text = "Total Physical Memory";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.FlatStyle = FlatStyle.System;
            label1.ImeMode = ImeMode.NoControl;
            label1.Location = new Point(141, 57);
            label1.Name = "label1";
            label1.Size = new Size(57, 20);
            label1.TabIndex = 10;
            label1.Text = "Version";
            label1.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // button1
            // 
            button1.FlatStyle = FlatStyle.System;
            button1.ImeMode = ImeMode.NoControl;
            button1.Location = new Point(376, 12);
            button1.Name = "button1";
            button1.Size = new Size(73, 37);
            button1.TabIndex = 9;
            button1.Text = "&Ok";
            button1.Click += button1_Click;
            // 
            // lblCopyright
            // 
            lblCopyright.AutoSize = true;
            lblCopyright.FlatStyle = FlatStyle.System;
            lblCopyright.ImeMode = ImeMode.NoControl;
            lblCopyright.Location = new Point(140, 83);
            lblCopyright.Name = "lblCopyright";
            lblCopyright.Size = new Size(173, 20);
            lblCopyright.TabIndex = 12;
            lblCopyright.Text = "Copyright (C) 2004-20XX";
            // 
            // pictureBox1
            // 
            pictureBox1.Image = (Image)resources.GetObject("pictureBox1.Image");
            pictureBox1.Location = new Point(12, 12);
            pictureBox1.Name = "pictureBox1";
            pictureBox1.Size = new Size(121, 89);
            pictureBox1.TabIndex = 13;
            pictureBox1.TabStop = false;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(135, 12);
            label2.Name = "label2";
            label2.Size = new Size(27, 20);
            label2.TabIndex = 14;
            label2.Text = "C#";
            label2.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // FAbout
            // 
            AcceptButton = button1;
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(454, 211);
            Controls.Add(label2);
            Controls.Add(pictureBox1);
            Controls.Add(groupBox1);
            Controls.Add(label1);
            Controls.Add(button1);
            Controls.Add(lblCopyright);
            DoubleBuffered = true;
            FormBorderStyle = FormBorderStyle.FixedToolWindow;
            MaximizeBox = false;
            MinimizeBox = false;
            Name = "FAbout";
            Opacity = 0.85D;
            ShowIcon = false;
            ShowInTaskbar = false;
            StartPosition = FormStartPosition.CenterScreen;
            Text = "About";
            Load += FAbout_Load;
            groupBox1.ResumeLayout(false);
            groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)pictureBox1).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion
        private GroupBox groupBox1;
        private Label lblWinVersion;
        private Label lblTotalPhysicalMem;
        private Label label1;
        private Button button1;
        private Label lblCopyright;
        private PictureBox pictureBox1;
        private Label lblAvailablePhysicalMem;
        private Label label2;
    }
}