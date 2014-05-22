using System;
using System.Collections.Generic;
using System.Drawing;

namespace Particles.ParticleEngine
{
  public sealed class ParticleSystem
  {
    #region Fields (private)

    /// <summary>
    /// The number of total required particles depending on current emitters.
    /// </summary>
    private int numRequiredParticles;

    #endregion

    #region Fields (private static / readonly)

    /// <summary>
    /// A list of particle emitters.
    /// </summary>
    private readonly List<IParticleEmitter> emitters;

    /// <summary>
    /// A list of available particles.
    /// </summary>
    private readonly List<Particle> particlesPool;

    /// <summary>
    /// A list of active particles.
    /// </summary>
    private readonly List<Particle> particlesActive;

    /// <summary>
    /// A list of dead particles.
    /// </summary>
    private readonly List<Particle> particlesDead;

    #endregion

    #region Constructors (public)

    /// <summary>
    /// Creates an instance of ParticleSystem.
    /// </summary>
    /// <param name="poolSize">The initial particle pool size.</param>
    public ParticleSystem(int poolSize)
    {
      this.emitters = new List<IParticleEmitter>();
      this.particlesPool = new List<Particle>(poolSize);
      this.particlesActive = new List<Particle>(poolSize);
      this.particlesDead = new List<Particle>(poolSize);

      for(int i = 0; i < poolSize; i++)
        this.particlesPool.Add(new Particle());
    }

    #endregion

    #region Methods (public)

    /// <summary>
    /// Adds a particle emitter to this system.
    /// </summary>
    /// <param name="emitter">A particle emitter.</param>
    public void Add(IParticleEmitter emitter)
    {
      if(this.emitters.Contains(emitter))
        return;

      this.emitters.Add(emitter);
      this.numRequiredParticles += emitter.MaxParticles;
    }

    /// <summary>
    /// Removes a particle emitter from this system.
    /// </summary>
    /// <param name="emitter">The particle emitter to remove.</param>
    public void Remove(IParticleEmitter emitter)
    {
      if(!this.emitters.Contains(emitter))
        return;

      this.emitters.Remove(emitter);
      this.numRequiredParticles -= emitter.MaxParticles;
    }

    /// <summary>
    /// Updates the particle system.
    /// </summary>
    /// <param name="time">The elapsed frame time.</param>
    public void Update(float time)
    {
      foreach(Particle particle in this.particlesDead)
      {
        this.particlesPool.Add(particle);
        this.particlesActive.Remove(particle);
      }

      this.particlesDead.Clear();

      float particlePercentagePerEmitter = this.particlesPool.Count / (float)this.numRequiredParticles;

      if(particlePercentagePerEmitter > 1.0f)
        particlePercentagePerEmitter = 1.0f;

      foreach(IParticleEmitter emitter in this.emitters)
      {
        if(!emitter.CanSpawn(time))
          continue;

        int particleCount = (int)Math.Floor(emitter.MaxParticles * particlePercentagePerEmitter);

        List<Particle> particles = this.particlesPool.GetRange(0, particleCount);

        emitter.Spawn(particles.GetEnumerator());

        this.particlesActive.AddRange(particles);

        this.particlesPool.RemoveRange(0, particleCount);
      }

      foreach(Particle num in this.particlesActive)
      {
        num.Position += num.Direction * num.Velocity;
        num.Velocity *= 0.995f;

        num.LifeTime -= time;

        if(num.LifeTime <= 0.0f)
          this.particlesDead.Add(num);
      }
    }

    /// <summary>
    /// Renders the particle system.
    /// </summary>
    public void Render(Graphics graphics)
    {
      foreach(Particle num in this.particlesActive)
      {
        graphics.DrawRectangle(new Pen(num.Color), num.Position.X, num.Position.Y, 1, 1);
      }
    }

    #endregion
  }
}