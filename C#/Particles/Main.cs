using System.Diagnostics;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;
using Particles.ParticleEngine;
using SlimDX;

namespace Particles
{
  public partial class Main : Form
  {
    #region Fields (private)

    private bool quit;

    #endregion

    #region Fields (private static / readonly)

    private readonly ParticleSystem system;
    private readonly Graphics graphics;
    private readonly Stopwatch timer = new Stopwatch();

    #endregion

    #region Constructors (public)

    public Main()
    {
      this.InitializeComponent();

      this.system = new ParticleSystem(10000);

      this.system.Add(new FireworksEmitter(new Vector3(this.Width / 2, this.Height / 2,0), 30, 1));

      this.graphics = this.CreateGraphics();
    }

    #endregion

    #region Methods (private)

    private void Main_FormClosing(object sender, FormClosingEventArgs e)
    {
      this.quit = true;
    }

    #endregion

    #region Methods (public)

    public void Run()
    {
      this.Show();

      float elapsed = 0.0f;

      timer.Start();

      while(!this.quit)
      {
        timer.Reset();
        timer.Restart();

        this.system.Update(elapsed);

        this.system.Render(this.graphics);

        Thread.Sleep(1);

        elapsed = 10;

        this.graphics.FillRectangle(new SolidBrush(Color.White), 0, 0, this.Width, this.Height );

        Application.DoEvents();
      }

      Application.Exit();
    }

    #endregion

    private void Main_Load(object sender, System.EventArgs e)
    {

    }
  }
}