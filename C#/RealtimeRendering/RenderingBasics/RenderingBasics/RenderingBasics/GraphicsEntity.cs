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
        
        private BoundingBox boundingBox;
        public BoundingBox BoundingBox
        { 
            get
            {
                //return wold space boundingbox
                return new BoundingBox( this.boundingBox.Min + this.Position, this.boundingBox.Max + this.Position );
            } 
            set
            {
                //set model space
                this.boundingBox = value;
            }
        }

        public GraphicsEntity()
        {
        }

    }
}
