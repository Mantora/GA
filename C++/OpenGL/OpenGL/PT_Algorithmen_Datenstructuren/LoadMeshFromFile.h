#pragma once

#include <stdio.h>

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

class LoadMeshFromFile
{
	public:
		//Variables
		int i_countVerts;
		Points3D points3D[256];

		int i_countTexturePos;
		Points2D points2D[256];

		int i_countPolygone;
		Polygone polygones[256];

		int i_countTextures;
		char cstr_textureNames[256][30];

		FILE * pFile;

		//functions
		LoadMeshFromFile( char* filename );
		~LoadMeshFromFile( void );


};
