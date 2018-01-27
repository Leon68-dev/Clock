namespace readRSS
{
    partial class FSet
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FSet));
            this.tbCtrlSetting = new System.Windows.Forms.TabControl();
            this.tbSetting = new System.Windows.Forms.TabPage();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.txtPassword = new System.Windows.Forms.TextBox();
            this.txtUserName = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.txtProxyPort = new System.Windows.Forms.TextBox();
            this.txtProxyName = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.btnApply = new System.Windows.Forms.Button();
            this.btnOK = new System.Windows.Forms.Button();
            this.tbCtrlSetting.SuspendLayout();
            this.tbSetting.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tbCtrlSetting
            // 
            this.tbCtrlSetting.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tbCtrlSetting.Appearance = System.Windows.Forms.TabAppearance.Buttons;
            this.tbCtrlSetting.Controls.Add(this.tbSetting);
            this.tbCtrlSetting.Location = new System.Drawing.Point(4, 4);
            this.tbCtrlSetting.Name = "tbCtrlSetting";
            this.tbCtrlSetting.SelectedIndex = 0;
            this.tbCtrlSetting.Size = new System.Drawing.Size(274, 134);
            this.tbCtrlSetting.TabIndex = 6;
            // 
            // tbSetting
            // 
            this.tbSetting.BackColor = System.Drawing.SystemColors.Control;
            this.tbSetting.Controls.Add(this.groupBox1);
            this.tbSetting.Controls.Add(this.txtProxyPort);
            this.tbSetting.Controls.Add(this.txtProxyName);
            this.tbSetting.Controls.Add(this.label2);
            this.tbSetting.Controls.Add(this.label1);
            this.tbSetting.Location = new System.Drawing.Point(4, 25);
            this.tbSetting.Name = "tbSetting";
            this.tbSetting.Padding = new System.Windows.Forms.Padding(3);
            this.tbSetting.Size = new System.Drawing.Size(266, 105);
            this.tbSetting.TabIndex = 0;
            this.tbSetting.Text = "Прокси";
            this.tbSetting.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.txtPassword);
            this.groupBox1.Controls.Add(this.txtUserName);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.groupBox1.Location = new System.Drawing.Point(8, 32);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(252, 68);
            this.groupBox1.TabIndex = 18;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Пароль";
            // 
            // txtPassword
            // 
            this.txtPassword.Location = new System.Drawing.Point(120, 40);
            this.txtPassword.Name = "txtPassword";
            this.txtPassword.PasswordChar = '*';
            this.txtPassword.Size = new System.Drawing.Size(116, 20);
            this.txtPassword.TabIndex = 19;
            // 
            // txtUserName
            // 
            this.txtUserName.Location = new System.Drawing.Point(120, 16);
            this.txtUserName.Name = "txtUserName";
            this.txtUserName.Size = new System.Drawing.Size(116, 20);
            this.txtUserName.TabIndex = 18;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.label3.Location = new System.Drawing.Point(16, 40);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(45, 13);
            this.label3.TabIndex = 21;
            this.label3.Text = "Пароль";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.label4.Location = new System.Drawing.Point(16, 20);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(103, 13);
            this.label4.TabIndex = 20;
            this.label4.Text = "Имя пользователя";
            // 
            // txtProxyPort
            // 
            this.txtProxyPort.Location = new System.Drawing.Point(204, 8);
            this.txtProxyPort.Name = "txtProxyPort";
            this.txtProxyPort.Size = new System.Drawing.Size(52, 20);
            this.txtProxyPort.TabIndex = 7;
            // 
            // txtProxyName
            // 
            this.txtProxyName.Location = new System.Drawing.Point(52, 8);
            this.txtProxyName.Name = "txtProxyName";
            this.txtProxyName.Size = new System.Drawing.Size(116, 20);
            this.txtProxyName.TabIndex = 6;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.label2.Location = new System.Drawing.Point(172, 12);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 13);
            this.label2.TabIndex = 9;
            this.label2.Text = "Порт:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.label1.Location = new System.Drawing.Point(8, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(47, 13);
            this.label1.TabIndex = 8;
            this.label1.Text = "Адресс:";
            // 
            // btnApply
            // 
            this.btnApply.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnApply.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.btnApply.Location = new System.Drawing.Point(198, 142);
            this.btnApply.Name = "btnApply";
            this.btnApply.Size = new System.Drawing.Size(75, 23);
            this.btnApply.TabIndex = 10;
            this.btnApply.Text = "Применить";
            this.btnApply.UseVisualStyleBackColor = true;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // btnOK
            // 
            this.btnOK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.btnOK.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.btnOK.Location = new System.Drawing.Point(114, 142);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(75, 23);
            this.btnOK.TabIndex = 11;
            this.btnOK.Text = "OK";
            this.btnOK.UseVisualStyleBackColor = true;
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // FSet
            // 
            this.AcceptButton = this.btnOK;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(282, 173);
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.btnApply);
            this.Controls.Add(this.tbCtrlSetting);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MinimizeBox = false;
            this.Name = "FSet";
            this.Opacity = 0.78;
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Настройки";
            this.Load += new System.EventHandler(this.FSet_Load);
            this.tbCtrlSetting.ResumeLayout(false);
            this.tbSetting.ResumeLayout(false);
            this.tbSetting.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tbCtrlSetting;
        private System.Windows.Forms.TabPage tbSetting;
        private System.Windows.Forms.TextBox txtProxyPort;
        private System.Windows.Forms.TextBox txtProxyName;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnApply;
        private System.Windows.Forms.Button btnOK;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox txtPassword;
        private System.Windows.Forms.TextBox txtUserName;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;

    }
}