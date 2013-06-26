using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;

namespace RenderingBasics
{
    /// <summary>
    /// This is the main type for your game
    /// </summary>
    public class Game1 : Microsoft.Xna.Framework.Game
    {
        private GraphicsDeviceManager graphics;
        private Camera camera;
         
        private SpriteBatch spriteBatch;
        private SpriteFont font;
         
        private float minX = -15.0f;
        private float maxX = 15.0f;
        private float minY = -10.0f;
        private float maxY = 10.0f;
        private float minZ = -20.0f;
        private float maxZ = 20.0f;
         
        private Random rand = new Random();
         
        private int numSpheres = 10000;
        private List<GraphicsEntity> spheres;
         
        private int framesLastSecond = 0;
        private int frameCounter = 0;
        private double frameTimer = 0;
         
        private BSP bsp;

        //ToDelet: 4 dev
        private int direktion;
        private float currentX;

        public Game1()
        {
            this.bsp = new BSP( new Vector3( minX-1, minY-1, minZ-1), new Vector3( maxX+1, maxY+1, maxZ+1) );
            this.currentX = 0;
            this.direktion = 1;
            this.graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
        }

        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>
        protected override void Initialize()
        {
            base.Initialize();

            this.camera = new Camera();
            this.camera.AspectRatio = graphics.GraphicsDevice.Viewport.AspectRatio;
            this.camera.NearClipDistance = 1.0f;
            this.camera.FarClipDistance = 10000.0f;
            this.camera.FieldOfViewDegree = 45.0f;
            this.camera.UpVector = Vector3.Up;
            this.camera.Position = Vector3.Zero;
            this.camera.ViewDirection = Vector3.Forward;

            this.spriteBatch = new SpriteBatch(graphics.GraphicsDevice);
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {
            Model shipmodel = Content.Load<Model>("Models//sphere");

            Texture2D[] textures = new Texture2D[3];
            textures[0] = Content.Load<Texture2D>("Textures/checker1");
            textures[1] = Content.Load<Texture2D>("Textures/checker2");
            textures[2] = Content.Load<Texture2D>("Textures/checker3");

            this.spheres = new List<GraphicsEntity>();
            for (int i = 0; i < numSpheres; ++i)
            {
                GraphicsEntity newShip = new GraphicsEntity();
                newShip.Position = new Vector3(this.randomFloat(minX, maxX), this.randomFloat(minY, maxY), this.randomFloat(minZ, maxZ));
                newShip.Model = shipmodel;
                newShip.BoundingBox = new BoundingBox( new Vector3(-0.4f, -0.4f, -0.4f), new Vector3(0.4f,0.4f,0.4f) );
                newShip.Texture = textures[this.rand.Next(0, 3)];

               //this.spheres.Add(newShip);
                this.bsp.addObject( newShip );
            }

            this.font = Content.Load<SpriteFont>("Fonts//SpriteFont1");
        }

        /// <summary>
        /// UnloadContent will be called once per game and is the place to unload all content.
        /// </summary>
        protected override void UnloadContent()
        {
            // TODO: Unload any non ContentManager content here
        }

        /// <summary>
        /// Allows the game to run logic such as updating the world,
        /// checking for collisions, gathering input, and playing audio.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Update(GameTime gameTime)
        {
            // Allows the game to exit
            if (Keyboard.GetState().IsKeyDown(Keys.Escape))
                this.Exit();

            Vector3 tempCamPos = this.camera.Position;
            if (Keyboard.GetState().IsKeyDown(Keys.S)
                || Keyboard.GetState().IsKeyDown(Keys.Down))
            {
                tempCamPos += (float)gameTime.ElapsedGameTime.TotalSeconds * Vector3.Backward;
            }

            if (Keyboard.GetState().IsKeyDown(Keys.W)
            || Keyboard.GetState().IsKeyDown(Keys.Up))
            {
                tempCamPos += (float)gameTime.ElapsedGameTime.TotalSeconds * Vector3.Forward;
            }

            if (Keyboard.GetState().IsKeyDown(Keys.A)
            || Keyboard.GetState().IsKeyDown(Keys.Left))
            {
                tempCamPos += (float)gameTime.ElapsedGameTime.TotalSeconds * Vector3.Left;
            }

            if (Keyboard.GetState().IsKeyDown(Keys.D)
            || Keyboard.GetState().IsKeyDown(Keys.Right))
            {
                tempCamPos += (float)gameTime.ElapsedGameTime.TotalSeconds * Vector3.Right;
            }

            this.camera.Position = tempCamPos;

            base.Update(gameTime);
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.CornflowerBlue);
            GraphicsDevice.BlendState = BlendState.Opaque;
            GraphicsDevice.DepthStencilState = DepthStencilState.Default;
            
            List<GraphicsEntity> tmp = new List<GraphicsEntity>();

            BoundingBox BBtoCheck = new BoundingBox( new Vector3( -1+this.currentX,-3,-5), new Vector3(1+this.currentX,3,-4) );

            tmp = this.bsp.FindObjects( BBtoCheck );

            foreach( GraphicsEntity entity in tmp )
            {
                // Copy any parent transforms.
                Matrix[] transforms = new Matrix[entity.Model.Bones.Count];
                entity.Model.CopyAbsoluteBoneTransformsTo(transforms);

                // Draw the model. A model can have multiple meshes, so loop.
                foreach( ModelMesh mesh in entity.Model.Meshes )
                {
                    // This is where the mesh orientation is set, as well 
                    // as our camera and projection.
                    foreach( BasicEffect effect in mesh.Effects )
                    {
                        effect.Texture = entity.Texture;
                        effect.EnableDefaultLighting();
                        effect.World = transforms[mesh.ParentBone.Index] *
                            Matrix.CreateRotationY(0.0f)
                            * Matrix.CreateTranslation(entity.Position);
                        effect.View = this.camera.ViewMatrix;
                        effect.Projection = this.camera.ProjectionMatrix;
                    }
                    // Draw the mesh, using the effects set above.
                    mesh.Draw();
                }
            }

            this.frameCounter++;
            this.frameTimer += gameTime.ElapsedGameTime.TotalSeconds;

            if (this.frameTimer > 1.0)
            {
                this.framesLastSecond = this.frameCounter;
                this.frameCounter = 0;
                this.frameTimer = 0;
            }

            spriteBatch.Begin();
            spriteBatch.DrawString(this.font, "FPS " + this.framesLastSecond.ToString(), new Vector2(0.1f, 0.1f), Color.White);
            spriteBatch.End();


            //ToDel: 4 dev
            if( this.currentX > 15 )
                this.direktion = -1;
            if( this.currentX < -15 )
                this.direktion = 1;

            if( this.direktion > 0 )
                this.currentX += 0.1f;
            else
                this.currentX -= 0.1f;
        }

        #region helper methods

        /// <summary> generate a random float between min and max
        /// </summary>
        private float randomFloat(float min, float max)
        {
            return min + (max - min) * (float)rand.NextDouble();
        }

        #endregion
    }
}
