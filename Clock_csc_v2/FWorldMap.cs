using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
using Timer = System.Windows.Forms.Timer;

namespace Clock_csc_v2
{
    public partial class FWorldMap : Form
    {
        private Bitmap _mapImage;
        private Timer _updateTimer;

        public FWorldMap()
        {
            InitializeComponent();

            // --- Налаштування вікна ---
            this.Text = "World Day/Night Map";
            this.ClientSize = new Size(1000, 500); // Фіксований розмір 2:1
            this.FormBorderStyle = FormBorderStyle.FixedSingle; // Блокуємо ресайз
            this.MaximizeBox = false; // Вимикаємо кнопку розгортання
            this.DoubleBuffered = true; // Щоб не було мерехтіння
            this.StartPosition = FormStartPosition.CenterScreen;
            this.ShowInTaskbar = false;
            this.MinimizeBox = false;
            this.ShowIcon = false;

            // Завантаження карти з ресурсів (переконайтеся, що назва збігається)
            // Якщо назвали файл інакше, змініть Properties.Resources.world_map
            try
            {
                _mapImage = Properties.Resources.world_map;
            }
            catch
            {
                MessageBox.Show("Не вдалося завантажити карту з ресурсів!");
            }

            // Таймер оновлення (раз на хвилину)
            _updateTimer = new Timer { Interval = 60000 };
            _updateTimer.Tick += (s, e) => this.Invalidate();
            _updateTimer.Start();
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            if (_mapImage == null) return;

            Graphics g = e.Graphics;

            // Налаштування для якісного стиснення великої карти (5400 -> 800)
            g.InterpolationMode = InterpolationMode.HighQualityBicubic;
            g.SmoothingMode = SmoothingMode.AntiAlias;
            g.PixelOffsetMode = PixelOffsetMode.HighQuality;

            float w = this.ClientSize.Width;
            float h = this.ClientSize.Height;

            // 1. Малюємо карту світу
            g.DrawImage(_mapImage, 0, 0, w, h);

            // 2. Розрахунок позиції Сонця (UTC)
            DateTime now = DateTime.UtcNow;
            double dayOfYear = now.DayOfYear;

            // Схилення Сонця (широта в градусах)
            double sunLat = 23.44 * Math.Sin(2 * Math.PI * (dayOfYear - 81) / 365.25);

            // Довгота Сонця (Гринвіч 0 по центру карти)
            // UTC 12:00 = Сонце на 0 меридіані
            double sunLon = (12.0 - (now.Hour + now.Minute / 60.0 + now.Second / 3600.0)) * 15.0;

            // 3. Побудова лінії термінатора (межа дня і ночі)
            GraphicsPath nightPath = new GraphicsPath();
            List<PointF> points = new List<PointF>();

            // Прораховуємо криву по всій ширині карти
            for (float x = 0; x <= w; x += 1)
            {
                double lon = (x / w) * 360.0 - 180.0;

                // Математична формула термінатора
                double latRad = Math.Atan(-Math.Cos((lon - sunLon) * Math.PI / 180.0) / Math.Tan(sunLat * Math.PI / 180.0));
                double lat = latRad * 180.0 / Math.PI;

                float y = (float)((90.0 - lat) / 180.0 * h);
                points.Add(new PointF(x, y));
            }

            // 4. Замикаємо область тіні залежно від пори року (сонцестояння)
            if (sunLat > 0)
            {
                // Влітку (північна півкуля) тінь зміщена до півдня
                points.Add(new PointF(w, h));
                points.Add(new PointF(0, h));
            }
            else
            {
                // Взимку тінь зміщена до півночі
                points.Add(new PointF(w, 0));
                points.Add(new PointF(0, 0));
            }

            nightPath.AddPolygon(points.ToArray());

            // 5. Малюємо ДУЖЕ ТЕМНУ тінь (Alpha = 215)
            // Колір: 5, 5, 20 (глибокий нічний синій)
            using (SolidBrush shadowBrush = new SolidBrush(Color.FromArgb(215, 5, 5, 20)))
            {
                g.FillPath(shadowBrush, nightPath);
            }

            // 6. Малюємо Сонце (жовта точка)
            float sunX = (float)((sunLon + 180.0) / 360.0 * w);
            float sunY = (float)((90.0 - sunLat) / 180.0 * h);

            g.FillEllipse(Brushes.Yellow, sunX - 4, sunY - 4, 8, 8);

            // Опціонально: маленька обводка для сонця, щоб його було краще видно
            g.DrawEllipse(Pens.Orange, sunX - 4, sunY - 4, 8, 8);
        }

        // Очищення ресурсів при закритті
        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            _updateTimer?.Stop();
            base.OnFormClosing(e);
        }
    }
}