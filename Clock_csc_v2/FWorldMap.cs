using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

namespace Clock_csc_v2
{
    public partial class FWorldMap : Form
    {
        private Bitmap mapImage;

        public FWorldMap()
        {
            this.Text = "World Day/Night Map";
            this.ClientSize = new Size(1000, 500); // Співвідношення 2:1
            this.DoubleBuffered = true;
            this.StartPosition = FormStartPosition.CenterScreen;
            this.FormBorderStyle = FormBorderStyle.FixedSingle;
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.MinimizeBox = false;
            this.MaximizeBox = false;

            // Завантаження карти з ресурсів
            mapImage = Clock_csc_v2.Properties.Resources.world_map;

            var timer = new System.Windows.Forms.Timer { Interval = 60000 }; // Оновлення раз на хвилину
            timer.Tick += (s, e) => this.Invalidate();
            timer.Start();
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            g.SmoothingMode = SmoothingMode.AntiAlias;

            float w = this.ClientSize.Width;
            float h = this.ClientSize.Height;

            // 1. Малюємо карту
            g.DrawImage(mapImage, 0, 0, w, h);

            // 2. Розрахунок позиції Сонця
            DateTime now = DateTime.UtcNow;
            double dayOfYear = now.DayOfYear;

            // Схилення Сонця (широта в градусах)
            double sunLat = 23.44 * Math.Sin(2 * Math.PI * (dayOfYear - 81) / 365.25);
            // Довгота Сонця (Гринвіч 0 по центру)
            double sunLon = (12.0 - (now.Hour + now.Minute / 60.0 + now.Second / 3600.0)) * 15.0;

            // 3. Побудова лінії термінатора
            GraphicsPath nightPath = new GraphicsPath();
            List<PointF> points = new List<PointF>();

            for (float x = 0; x <= w; x += 2)
            {
                double lon = (x / w) * 360.0 - 180.0;
                // Формула термінатора
                double latRad = Math.Atan(-Math.Cos((lon - sunLon) * Math.PI / 180.0) / Math.Tan(sunLat * Math.PI / 180.0));
                double lat = latRad * 180.0 / Math.PI;

                float y = (float)((90.0 - lat) / 180.0 * h);
                points.Add(new PointF(x, y));
            }

            // Замикаємо полігон для нічної зони
            if (sunLat > 0)
            {
                points.Add(new PointF(w, h));
                points.Add(new PointF(0, h));
            }
            else
            {
                points.Add(new PointF(w, 0));
                points.Add(new PointF(0, 0));
            }

            nightPath.AddPolygon(points.ToArray());

            // 4. Малюємо напівпрозору тінь
            using (SolidBrush shadowBrush = new SolidBrush(Color.FromArgb(210, 5, 5, 20)))
            {
                g.FillPath(shadowBrush, nightPath);
            }

            // 5. Малюємо Сонце (маленька точка)
            float sunX = (float)((sunLon + 180.0) / 360.0 * w);
            float sunY = (float)((90.0 - sunLat) / 180.0 * h);
            g.FillEllipse(Brushes.Yellow, sunX - 4, sunY - 4, 8, 8);
        }
    }
}
