using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;

namespace RenderingBasics
{
    public class GraphicsEntity
    {
        public Model Model { get; set; }
        public Vector3 Position { get; set; }

        public Texture2D Texture { get; set; }

        public GraphicsEntity()
        {
        }
    }
}
