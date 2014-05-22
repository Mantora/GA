using System.Collections.Generic;
using SlimDX;

namespace Particles.ParticleEngine
{
  public abstract class ParticleEmitterBase : IParticleEmitter
  {
    #region Fields (private)

    /// <summary>
    /// The time.
    /// </summary>
    private float time;

    /// <summary>
    /// The spawn-rate per second.
    /// </summary>
    private int spawnRate;

    #endregion

    #region Fields (protected)

    /// <summary>
    /// The position.
    /// </summary>
    protected Vector3 position;

    #endregion

    #region Fields (private static / readonly)

    /// <summary>
    /// The maximum number of particles this emitter spawns per second.
    /// </summary>
    private readonly int maxParticles;

    #endregion

    #region Properties (public)

    /// <summary>
    /// The position.
    /// </summary>
    public Vector3 Position { get { return this.position; } set { this.position = value; } }

    /// <summary>
    /// The maximum number of particles used.
    /// </summary>
    public int MaxParticles { get { return this.maxParticles; } }

    /// <summary>
    /// The spawn-rate per second.
    /// </summary>
    public int SpawnRate { get { return this.spawnRate; } set { this.spawnRate = value; } }

    #endregion

    #region Constructors (public)

    /// <summary>
    /// Creates an instance of ParticleEmitterBase.
    /// </summary>
    /// <param name="position">The emitter initial position.</param>
    /// <param name="spawnRate">The emitter spawn-rate per second.</param>
    /// <param name="numParticles">The maximum number of particles this emitter spawns per second.</param>
    protected ParticleEmitterBase(Vector3 position, int spawnRate, int numParticles)
    {
      this.position = position;
      this.spawnRate = spawnRate;
      this.maxParticles = numParticles;
    }

    #endregion

    #region Methods (public)

    /// <summary>
    /// Spawns the specified list of particles.
    /// </summary>
    /// <param name="particles">A list of particles than can be spawned.</param>
    public abstract void Spawn(IEnumerator<Particle> particles);

    /// <summary>
    /// Indicates whether spawning is possible.
    /// </summary>
    /// <param name="time">The frame time in millis-seconds.</param>
    /// <returns>True if spawning is possible, else false.</returns>
    public bool CanSpawn(float time)
    {
      this.time += time;

      float value = 1000.0f / this.spawnRate;

      if(this.time >= value)
      {
        this.time = -value;
        return true;
      }

      return false;
    }

    #endregion
  }
}