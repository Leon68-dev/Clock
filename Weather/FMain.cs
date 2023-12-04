using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using System.Net;

namespace readRSS
{
    public partial class FMain : Form
    {
        DataSet rssDS = new DataSet();
        private string m_ProxyName = null;
        private string m_ProxyPort = null;
        private string m_UserName = null;
        private string m_Password = null;
        private bool msDown;
        private int mOldX;
        private int mOldY;


        public FMain()
        {
            InitializeComponent();
            this.TopMost = false;
        }


        private void viewWeather()
        {
            try
            {
                //string strURL = @"http://k.img.com.ua/rss/ru/world.xml";
                //string strURL = @"http://k.img.com.ua/rss/ru/news.xml";

                //Не работают
                //string strURL = @"http://www.f-1.ru/rss/f1.xml");
                //string strURL = @"http://www.f1news.ru/export/news.xml";

                //string strURL = @"http://www.wunderground.com/auto/rss_full/global/stations/33837.xml";
                //string strURL = @"http://informer.gismeteo.ru/rss/33837.xml";
                //string strURL = @"http://www.yandex.ru/redir?dtype=stred&pid=7&cid=1228&url=http://weather.yandex.ru/index.xml?city=33837";
                //string strURL = @"http://xml.weather.yahoo.com/forecastrss?p=UPXX0021&u=c";

                //string strURL = @"http://www.rbc.ua/include/dynamic/rus/fp/topnews.xml";

                //string strURL = @"http://weather.yahooapis.com/forecastrss?p=33770";
                    
                //string strURL = @"http://k.img.com.ua/rss/ru/news.xml";


                //string strURL = @"http://informer.gismeteo.ru/rss/33345.xml";   //Kyiv  
                ////string strURL = @"http://informer.gismeteo.ru/rss/33837.xml"; //Odessa

                ////HttpWebRequest rssFeed = (HttpWebRequest)WebRequest.Create(strURL);

                ////rssDS = new DataSet();
                ////rssDS.ReadXml(rssFeed.GetResponse().GetResponseStream());
                ////rssFeed = null;

                System.Configuration.AppSettingsReader cas = new System.Configuration.AppSettingsReader();
                string strURL = cas.GetValue("rssChannel", typeof(string)).ToString();


                //string strURL = @"http://informer.gismeteo.ru/rss/33837.xml"; //Odessa
                //System.Net.WebRequest rssFeed = (System.Net.WebRequest)System.Net.WebRequest.Create(strURL);
                //System.Net.WebProxy prx = new WebProxy(@"http:\\172.21.44.23:8080");
                //rssFeed.Proxy = prx;


                HttpWebRequest rssFeed = (HttpWebRequest)WebRequest.Create(strURL);
                string tempHTTP = @"http://" + m_ProxyName + ":" + m_ProxyPort + "/";
                
                //WebProxy prx = new WebProxy(@"http://172.21.44.27:8080/");
                //WebProxy prx = new WebProxy(@"https://172.21.44.27:443/");

                WebProxy prx = null;

                if(string.IsNullOrEmpty(m_ProxyName) == false)
                    prx = new WebProxy(tempHTTP);

                if(prx != null)
                {
                    if (string.IsNullOrEmpty(m_UserName) == false)
                    {
                        NetworkCredential nc = new NetworkCredential(m_UserName, m_Password);
                        prx.Credentials = nc;
                        rssFeed.PreAuthenticate = true;
                    }

                    rssFeed.Proxy = prx;
                }

                rssDS = new DataSet();
                rssDS.ReadXml(rssFeed.GetResponse().GetResponseStream());
                //rssDS.WriteXml(@"test.xml");
                rssFeed = null;

                //object[] channelItems = rssDS.Tables[1].Rows[0].ItemArray;
                //int titleColumn = rssDS.Tables[1].Columns["title"].Ordinal;
            }
            catch (Exception e)
            {
                System.Windows.Forms.MessageBox.Show(e.Message, "RSS", MessageBoxButtons.OK, MessageBoxIcon.Error);
                if (openFSet() < 0)
                    return;

                viewWeather();
                return;
            }


            //rssDS = new DataSet();
            //rssDS.ReadXml(@"test.xml");


            this.lstBoxState.DataSource = rssDS.Tables["item"].DefaultView;
            this.lstBoxState.DisplayMember = "title";
            
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////            
            //this.grd.DataSource = rssDS;
            //this.grd.DataMember = "item";

            //DataGridTableStyle ts = new DataGridTableStyle();
            //ts.MappingName = grd.DataMember;
            //grd.TableStyles.Clear();
            //grd.TableStyles.Add(ts);

            //rssDS.Tables[1].Columns["link"].ColumnMapping = MappingType.Hidden; ???
            
            //grd.TableStyles[0].AllowSorting = false;
            //grd.TableStyles[0].RowHeadersVisible = false;
            
            //for (int i = 0; i < grd.TableStyles[0].DataGrid.VisibleColumnCount; i++)
            //for (int i = 0; i < rssDS.Tables[0].Columns.Count; i++)
            //{
            //    string str = grd.TableStyles[0].GridColumnStyles[i].HeaderText;         //dataSet.Tables["item"].Columns[i].ColumnName;

            //    if (str == "title")
            //    {
            //        grd.TableStyles[0].GridColumnStyles[i].Width = grd.Width - 10; //(this.Width - 80);
            //        //grd.TableStyles[0].GridColumnStyles[i].HeaderText = "Краткое содержание";
            //        grd.TableStyles[0].GridColumnStyles[i].ReadOnly = true;
            //        grd.ColumnHeadersVisible = false;
            //        m_IndexColTitle = i;
            //    }

            //    if (str != "title")  //&& str != "link") 
            //        grd.TableStyles[0].GridColumnStyles[i].Width = 0;

            //    if (str == "description")
            //        m_IndexColDescription = i;

            //    if (str == "link")
            //        m_IndexColLink = i;
            //}
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            getTextDescription(0);

            return;
        }


        private void startPosition(ref int x, ref int y)
        {
            //Позиционирование
            System.Drawing.Rectangle workingRectangle = Screen.PrimaryScreen.WorkingArea;
            x = workingRectangle.Width - (int)(this.Size.Width + this.Size.Width * 0.2);
            y = workingRectangle.Height - (int)(this.Size.Height + this.Size.Height * 0.2);
            Point tempPoint = new Point(x, y);
            // Set the location of the form using the Point object.
            this.DesktopLocation = tempPoint;
        }


        private void getTextDescription(int index)
        {
            try
            {
                this.rtbDescription.Text = rssDS.Tables["item"].Rows[index]["description"].ToString();

                string strNtfIcon = rssDS.Tables["item"].Rows[index]["title"].ToString();           //(string)grd[0, m_IndexColTitle];
                int len = strNtfIcon.IndexOf(":");
                strNtfIcon = strNtfIcon.Substring(0, ++len);
                strNtfIcon += " ";

                strNtfIcon += rssDS.Tables["item"].Rows[index]["description"].ToString();
                if (strNtfIcon.Length > 64)
                {
                    len = strNtfIcon.IndexOf("С");
                    strNtfIcon = strNtfIcon.Substring(0, ++len);
                }
                strNtfIcon += " ...";

                ntfIcon.Text = strNtfIcon;

                return;
            }
            catch
            {
                this.rtbDescription.Text = "";
                ntfIcon.Text = "Прогноз погоды";
            }
        }
   

        private void btnRef_Click(object sender, EventArgs e)
        {
            viewWeather();
        }


        private void btnIE_Click(object sender, EventArgs e)
        {
            try
            {
                string strURL = rssDS.Tables["item"].Rows[getListIndex()]["link"].ToString();
                System.Windows.Forms.Cursor.Current = System.Windows.Forms.Cursors.Default;
                System.Diagnostics.Process.Start("iexplore", @strURL);
            }
            catch (Exception q)
            {
                System.Windows.Forms.MessageBox.Show(q.Message, "RSS", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
        }


        private int getListIndex()
        {
            return lstBoxState.SelectedIndex;
        }


        private void FMain_Load(object sender, EventArgs e)
        {
            viewWeather();
            
            int x = 0;
            int y = 0;
            startPosition(ref x, ref y);
        }


        private void FMain_MouseDown(object sender, MouseEventArgs e)
        {
            //if (Control.ModifierKeys ==  || )
            //if ((ModifierKeys == (Keys.Alt & Keys.Control)) != 0)

            //if (e.Button == MouseButtons.Right && (Control.ModifierKeys == (Keys.Alt || Keys.Control)))

            //if ((e.Button == MouseButtons.Right) && (Control.ModifierKeys == Keys.Control))
            //        MessageBox.Show(e.Button.ToString());

            msDown = true;
            mOldX = e.X;
            mOldY = e.Y;
        }


        private void btnSet_Click(object sender, EventArgs e)
        {
            if (openFSet() < 0)
                return;

            viewWeather();
        }


        private int openFSet()
        {
            FSet fs = new FSet();
            if (fs.ShowDialog() == DialogResult.OK)
            {
                m_ProxyName = fs.proxyName;
                m_ProxyPort = fs.proxyPort;
                m_UserName = fs.userName;
                m_Password = fs.password;
                return 0;
            }

            return -1;
        }


        private void cmsWeather_Exit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }


        private void cmsWeather_Refr_Click(object sender, EventArgs e)
        {
            viewWeather();
        }


        private void cmsWeather_IE_Click(object sender, EventArgs e)
        {
            btnIE_Click(sender, e);
        }


        private void cmsWeather_Set_Click(object sender, EventArgs e)
        {
            btnSet_Click(sender, e);
        }


        private void cmsWeather_Hide_Click(object sender, EventArgs e)
        {
            if (this.Visible)
            {
                this.Visible = false;
                cmsWeather_Hide.Text = "Показать";
            }
            else
            {
                this.Visible = true;
                cmsWeather_Hide.Text = "Скрыть";
            }

            this.TopMost = this.Visible;
        }


        private void FMain_MouseMove(object sender, MouseEventArgs e)
        {
            if (msDown)
            {
                this.Left = this.Left + e.X - mOldX;
                this.Top = this.Top + e.Y - mOldY;
            }
        }

        private void FMain_MouseUp(object sender, MouseEventArgs e)
        {
            msDown = false;
        }

        private void lstBoxState_SelectedIndexChanged(object sender, EventArgs e)
        {
            getTextDescription(getListIndex());
        }

        private void ntfIcon_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            cmsWeather_Hide_Click(sender, e);
        }

    }
}