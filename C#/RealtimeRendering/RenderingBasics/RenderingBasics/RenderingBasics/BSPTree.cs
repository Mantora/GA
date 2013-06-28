using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;

namespace RenderingBasics
{
    public class BSP //binary space partitioning
    {
        private BSPNode root;

        public BSP( Vector3 min, Vector3 max)
        {
            this.root = new BSPNode(min, max);
        }

        //fügt ein GraphicsEntity den nodes hinzu
        public void addObject( GraphicsEntity ent )
        {
            if( !this.root.AddObject( ent ) )
                throw new Exception("BSP to small for world!");
        }

        //gibt eine liste mit GraphicsEntity mit den Objekten zurück, die in min&max gefunden werden
        public List<GraphicsEntity> FindObjects( BoundingBox BBtoCheck )
        {
            List<GraphicsEntity> tmp = new List<GraphicsEntity>();

            //von root aus alle nodes absuchen
            //und anhand von min & max objekte zurückgeben
            root.isObjectInView( BBtoCheck, tmp );

            return tmp;
        }

        public List<GraphicsEntity> FindObjects( BoundingFrustum BBtoCheck )
        {
            List<GraphicsEntity> tmp = new List<GraphicsEntity>();

            //von root aus alle nodes absuchen
            //und anhand von min & max objekte zurückgeben
            root.isObjectInView( BBtoCheck, tmp );

            return tmp;
        }
    }
    
    public class BSPNode
    {
        //container für graphics entities
        public List<GraphicsEntity> contents;

        private BoundingBox bb;

        private BSPNode[] childNodes;

        //Konstruktor
        public BSPNode(Vector3 min, Vector3 max)
        {
//            this.bb = new BoundingBox( min, max );
            Vector3 mi = Vector3.Min( min, max );
            Vector3 ma = Vector3.Max( min, max );

            this.bb = new BoundingBox( mi, ma );

            this.contents = new List<GraphicsEntity>();
        }

        //Methode zum hinzufügen eines objektes
        //return: ist das Object vollständig in diesem BSPNode
        public bool AddObject( GraphicsEntity ent )
        { 
            //prüfen ob dieses Object komplett in diesem Bereich liegt
            //ja: liegt in dieser Ebene
            //nein: eine eben tiefer kontrollieren
        
            switch( this.bb.Contains( ent.BoundingBox ) )
            {
                case ContainmentType.Contains:
                    //beinhaltet
                    
                    //unterboxen erstellen zum kontrollieren
                    initChildNotes();
                    //unterboxen durchgehen
                    foreach( BSPNode node in this.childNodes )
                    {
                        if( node.AddObject( ent ) )
                        {
                             return true;
                        }
                    }
                    this.contents.Add( ent );
                    return true;
                break;
           }
           return false;
        }

        //function zum herausfinden, ob die BoundingBox im bereich ist
        public void isObjectInView( BoundingBox BBtoCheck, List<GraphicsEntity> list )
        {
            if( this.bb.Contains( BBtoCheck ) != ContainmentType.Disjoint )
            {
                list.AddRange( this.contents );

                if( this.childNodes != null )
                {
                    foreach( BSPNode node in this.childNodes )
                    {
                        node.isObjectInView( BBtoCheck, list );
                    }
                }
            }
        }

        public void isObjectInView( BoundingFrustum BBtoCheck, List<GraphicsEntity> list )
        {
            
            if( this.bb.Contains( BBtoCheck ) != ContainmentType.Disjoint )
            {
                list.AddRange( this.contents );

                if( this.childNodes != null )
                {
                    foreach( BSPNode node in this.childNodes )
                    {
                        node.isObjectInView( BBtoCheck, list );
                    }
                }
            }
            
        }

        internal void initChildNotes()
        {
            //wurden die childNodes schon erzeugt ?
            if( null != this.childNodes )
                return;

            //nur array erzeugen
            this.childNodes = new BSPNode[8];

            Vector3 center = (this.bb.Min + this.bb.Max ) * 0.5f;

            Vector3[] corners = this.bb.GetCorners();
 
            float offset = 2;

            for( int i = 0; i < 8; i++ )
            {
                Vector3 corner = corners[i];
                if( corner.X < 0 ) corner.X -= offset;
                if( corner.Y < 0 ) corner.Y -= offset;
                if( corner.Z < 0 ) corner.Z -= offset;

                if( corner.X > 0 ) corner.X += offset;
                if( corner.Y > 0 ) corner.Y += offset;
                if( corner.Z > 0 ) corner.Z += offset;

                this.childNodes[i] = new BSPNode( center, corners[i] );
            }
        }
    }
}
