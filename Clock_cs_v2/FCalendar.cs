using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Clock_cs_v2
{
    public partial class FCalendar : Form
    {
        public FCalendar()
        {
            InitializeComponent();
        }

        private void Form2_Load(object sender, System.EventArgs e)
        {
            setCalendar();
        }
        private void setCalendar()
        {
            int dday = DateTime.Now.Day;
            int mmonth = DateTime.Now.Month;
            int yyear = DateTime.Now.Year;

            DateTime bBeg = new DateTime(yyear, mmonth, dday);
            DateTime eEnd = new DateTime(yyear, mmonth, dday);

            monthCalendar1.SelectionRange = new SelectionRange(bBeg, eEnd);
            monthCalendar1.TodayDate = bBeg;
        }

        private void button1_Click(object sender, System.EventArgs e)
        {
            this.Close();
        }

    }
}
