#include <stdio.h>
#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */

struct Points3D
{
	float x,y,z;
};

struct Points2D
{
	float x,y;
};

struct Polygone
{
	int count_vertices;
	int index_pos[256];
	int index_textureKoords[256];
	int index_texture;
};

int main()
{
	//variables
	char str[128] = "";
	int i_countVerts = 0;
	Points3D points3D[256] = { 0 };

	int i_countTexturePos = 0;
	Points2D points2D[256] = { 0 };

	int i_countPolygone = 0;
	Polygone polygones[256] = { 0 };

	int i_countTextures = 0;
	char cstr_textureNames[256][30] = { 0 };

	FILE * pFile;
	const char* fileName = "compound.tg4";


	pFile = fopen(fileName,"r");

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

	//printf file info
	printf("\n");
	printf("%s:\n",fileName);
	printf("%d vertices\n", i_countVerts);
	printf("%d texture positions\n", i_countTexturePos);
	printf("%d polygones\n", i_countPolygone);
	printf("%d textures\n", i_countTextures);

	system("pause");
	return 0;
}