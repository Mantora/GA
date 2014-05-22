using System.Drawing;
using SlimDX;

namespace Particles.ParticleEngine
{
  public class Particle
  {
    #region Fields (private)

    /// <summary>
    /// The direction.
    /// </summary>
    protected Vector3 direction;

    /// <summary>
    /// The velocity.
    /// </summary>
    protected float velocity;

    /// <summary>
    /// The position.
    /// </summary>
    protected Vector3 position;

    /// <summary>
    /// The life-time in ms (could be in a component).
    /// </summary>
    protected float lifeTime;

    /// <summary>
    /// The color.
    /// </summary>
    protected Color color;

    #endregion

    #region Properties (public)

    /// <summary>
    /// The direction.
    /// </summary>
    public Vector3 Direction { get { return this.direction; } set { this.direction = value; } }

    /// <summary>
    /// The velocity.
    /// </summary>
    public float Velocity { get { return this.velocity; } set { this.velocity = value; } }

    /// <summary>
    /// The position.
    /// </summary>
    public Vector3 Position { get { return this.position; } set { this.position = value; } }

    /// <summary>
    /// The life-time in ms (could be in a component).
    /// </summary>
    public float LifeTime { get { return this.lifeTime; } set { this.lifeTime = value; } }

    /// <summary>
    /// The color.
    /// </summary>
    public Color Color { get { return this.color; } set { this.color = value; } }

    #endregion
  }
}