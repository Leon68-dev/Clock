using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Clock_csc_v2
{
    public partial class FCalendar : Form
    {
        public FCalendar()
        {
            InitializeComponent();
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

        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void FCalendar_Load(object sender, EventArgs e)
        {
            setCalendar();
        }
    }
}
