using System;
using System.Collections.Generic;
using System.Drawing;
using SlimDX;

namespace Particles.ParticleEngine
{
  public sealed class FireworksEmitter : ParticleEmitterBase
  {
    #region Constructors (public)

    /// <summary>
    /// Creates an instance of FireworksEmitter.
    /// </summary>
    /// <param name="position">The emitter initial position.</param>
    /// <param name="spawnRate">The emitter spawn-rate per second.</param>
    /// <param name="numParticles">The maximum number of particles this emitter spawns per second.</param>
    public FireworksEmitter(Vector3 position, int spawnRate, int numParticles)
      :base (position, spawnRate, numParticles)
    {
    }

    #endregion

    /// <summary>
    /// Spawns the specified list of particles.
    /// </summary>
    /// <param name="particles">A list of particles than can be spawned.</param>
    public override void Spawn(IEnumerator<Particle> particles)
    {
      Random rnd = new Random();

      while(particles.MoveNext())
      {
        int i1 = rnd.Next(0, 2);
        int i2 = rnd.Next(0, 2);

        float dx = i1 == 0 ? -1 : 1;
        float dy = i2 == 0 ? -1 : 1;

        particles.Current.Direction = Vector3.Normalize(new Vector3((float)rnd.NextDouble() * dx, (float)rnd.NextDouble() * dy, 0));
        particles.Current.Position = this.position;
        particles.Current.LifeTime = rnd.Next(1000, 3000);
        particles.Current.Velocity = 0.5f;
        particles.Current.Color = Color.Red;
      }
    }
  }
}