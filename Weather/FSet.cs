using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace readRSS
{
    public partial class FSet : Form
    {
        public int typeClose;

        private DataSet m_ds;
        public static string m_SetTblName = "SetTblName";

        private string m_ProxyName;
        private string m_ProxyPort;
        private string m_User = null;
        private static string m_Pass = null;


        public FSet()
        {
            InitializeComponent();
            initialization();
        }


        public void initialization()
        {
            m_ds = new DataSet();
            
            if (System.IO.File.Exists(@cPubFunc.fileNameSet()))
                readDS(ref m_ds);
            else
                setSetupDSDefault(ref m_ds);
            
            m_ProxyName = m_ds.Tables[m_SetTblName].Rows[0]["proxyName"].ToString();
            m_ProxyPort = m_ds.Tables[m_SetTblName].Rows[0]["proxyPort"].ToString();
            m_User = m_ds.Tables[m_SetTblName].Rows[0]["user"].ToString();
        }


        private void btnSet_Click(object sender, EventArgs e)
        {
            if(this.txtProxyName.Text != "")
                m_ProxyName = this.txtProxyName.Text;
            else
                m_ProxyName = null;

            if (this.txtProxyPort.Text != "")
                m_ProxyPort = this.txtProxyPort.Text;
            else
                m_ProxyPort = null;

            if (this.txtUserName.Text != "")
                m_User = this.txtUserName.Text;
            else
                m_User = null;

            if (this.txtPassword.Text != "")
                m_Pass = this.txtPassword.Text;
            else
                m_Pass = null;
        }


        public string userName
        {
            set { m_User = value; }
            get { return m_User; }
        }

        public string password
        {
            set { m_Pass = value; }
            get { return m_Pass; }
        }


        public string proxyName
        {
            set { m_ProxyName = value; }
            get { return m_ProxyName; }
        }


        public string proxyPort
        {
            set { m_ProxyPort = value; }
            get { return m_ProxyPort; }
        }


        public static void setSetupDSDefault(ref DataSet ds)
        {
            try
            {
                DataTable tbl = new DataTable(m_SetTblName);
                tbl.Columns.Add("proxyName", typeof(string));
                tbl.Columns.Add("proxyPort", typeof(string));
                tbl.Columns.Add("user", typeof(string));
                ds.Tables.Add(tbl);
                DataRow dr = ds.Tables[m_SetTblName].NewRow();
                dr["proxyName"] = "";
                dr["proxyPort"] = "";
                dr["user"] = "";
                ds.Tables[m_SetTblName].Rows.Add(dr);
                ds.WriteXml(@cPubFunc.fileNameSet());
            }
            catch { }
        }


        public static int readDS(ref DataSet ds)
        {
            try
            {
                ds.ReadXml(@cPubFunc.fileNameSet());
                return ds.Tables[m_SetTblName].Rows.Count;
            }
            catch
            {
                return 0;
            }
        }


        private void btnApply_Click(object sender, EventArgs e)
        {
            //Tab PROXY
            m_ProxyName = this.txtProxyName.Text;
            m_ProxyPort = this.txtProxyPort.Text;
            m_User = this.txtUserName.Text;
            m_Pass = this.txtPassword.Text;

            DataSet ds = new DataSet();
            ds.ReadXml(@cPubFunc.fileNameSet());
            ds.Tables[m_SetTblName].Rows[0]["proxyName"] = m_ProxyName;
            ds.Tables[m_SetTblName].Rows[0]["proxyPort"] = m_ProxyPort;
            ds.Tables[m_SetTblName].Rows[0]["user"] = m_User;
            ds.WriteXml(@cPubFunc.fileNameSet());
        }


        private void btnOK_Click(object sender, EventArgs e)
        {
            btnApply_Click(sender, e);
            this.Close();
        }

        private void FSet_Load(object sender, EventArgs e)
        {
            this.txtUserName.Text = m_User;
            this.txtPassword.Text = m_Pass;
            this.txtProxyName.Text = m_ProxyName;
            this.txtProxyPort.Text = m_ProxyPort;
        }

    }
}