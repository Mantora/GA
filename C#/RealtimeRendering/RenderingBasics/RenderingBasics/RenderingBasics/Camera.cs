using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace RenderingBasics
{
    public class Camera
    {
        public float AspectRatio { get; set; }
        public Vector3 Position { get; set; }
        public Vector3 ViewDirection { get; set; }
        public Vector3 UpVector { get; set; }

        public float NearClipDistance { get; set; }
        public float FarClipDistance { get; set; }
        public float FieldOfViewDegree { get; set; }

        public Vector3 LookAtPosition 
        {
            get
            {
                return this.Position + this.ViewDirection;
            }
        }

        public Matrix ViewMatrix
        {
            get
            {
                return Matrix.CreateLookAt(this.Position, this.LookAtPosition, this.UpVector);
            }
        }

        public Matrix ProjectionMatrix
        {
            get
            {
                return Matrix.CreatePerspectiveFieldOfView(MathHelper.ToRadians(this.FieldOfViewDegree), this.AspectRatio, this.NearClipDistance, this.FarClipDistance);
            }
        }
    }
}
