#include "LoadMeshFromFile.h"

LoadMeshFromFile::LoadMeshFromFile( char* fileName )
{
	pFile = fopen(fileName,"r");

	i_countVerts = 0;

	i_countTexturePos = 0;

	i_countPolygone = 0;

	i_countTextures = 0;

/******************read verts*****************/
	fscanf(pFile, "%d", &i_countVerts);
	for( int i = 0; i < i_countVerts; i++ )
	{
		fscanf(pFile, "%f", &points3D[i].x);
		fscanf(pFile, "%f", &points3D[i].y);
		fscanf(pFile, "%f", &points3D[i].z);
	}

/******************read texturePos*****************/
	fscanf(pFile, "%d", &i_countTexturePos);
	for( int i = 0; i < i_countTexturePos; i++ )
	{
		fscanf(pFile, "%f", &points2D[i].x);
		fscanf(pFile, "%f", &points2D[i].y);
	}

/******************read polygone*****************/
	//hier wird nur der index der Point3D position und Point2D textur gelesen
	fscanf(pFile, "%d", &i_countPolygone);
	for( int i = 0; i < i_countPolygone; i++ )
	{
		//anzahl der punkte i tes polygone
		int i_pointsToRead = 0;
		fscanf(pFile, "%d", &i_pointsToRead);
		
		polygones[i].count_vertices = i_pointsToRead;
		//alle punkte lesen
		for( int currentPolyCount = 0; currentPolyCount < i_pointsToRead; currentPolyCount++ )
		{
			int index_pos = 0;
			fscanf(pFile, "%d", &index_pos);
			polygones[i].index_pos[currentPolyCount] = index_pos;

			int index_tex = 0;
			fscanf(pFile, "%d", &index_tex);
			polygones[i].index_textureKoords[currentPolyCount] = index_tex;
		}

		int index_tex_ref = 0;
		fscanf(pFile, "%d", &index_tex_ref);
		polygones[i].index_texture = index_tex_ref;
	}

/*	printf("Polygones readed:\n");
	for( int i = 0; i < i_countPolygone; i++ )
	{
		printf( "%d) %d\n", i, polygones[i].count_vertices );
		for( int x = 0; x < polygones[i].count_vertices; x++ )
		{
			printf( "%d %d\t", polygones[i].index_pos[x], polygones[i].index_textureKoords[x] );
		}
		printf( "%d\n", polygones[i].index_texture );
	}
*/
/******************read texture name*****************/
	fscanf(pFile, "%d", &i_countTextures);
	for( int i = 0; i < i_countTextures; i++ )
	{
		fscanf(pFile, "%s", cstr_textureNames[i]);
	}
 

/******************end of read*****************/
	fclose(pFile);
}

LoadMeshFromFile::~LoadMeshFromFile(void)
{
}
