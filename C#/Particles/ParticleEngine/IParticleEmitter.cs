using System.Collections.Generic;
using SlimDX;

namespace Particles.ParticleEngine
{
  public interface IParticleEmitter
  {
    /// <summary>
    /// The position.
    /// </summary>
    Vector3 Position { get; set; }

    /// <summary>
    /// The maximum number of particles used.
    /// </summary>
    int MaxParticles { get; }

    /// <summary>
    /// The spawn-rate per second.
    /// </summary>
    int SpawnRate { get; }

    /// <summary>
    /// Spawns the specified list of particles.
    /// </summary>
    /// <param name="particles">A list of particles than can be spawned.</param>
    void Spawn(IEnumerator<Particle> particles);

    /// <summary>
    /// Indicates whether spawning is possible.
    /// </summary>
    /// <param name="time">The frame time in millis-seconds.</param>
    /// <returns>True if spawning is possible, else false.</returns>
    bool CanSpawn(float time);
  }
}
