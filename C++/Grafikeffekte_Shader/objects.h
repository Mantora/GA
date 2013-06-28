#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED

#include <d3d9.h>

// create a cube object containing position & color components
HRESULT
CreateCube(IDirect3DDevice9* pDevice, 
			int* piNumVerticesOut, int* piNumTrianglesOut, int* piVertexSizeOut,
			IDirect3DVertexDeclaration9** ppVertexDeclarationOut,
			IDirect3DVertexBuffer9** ppVertexBufferOut,
			IDirect3DIndexBuffer9**	ppIndexBufferOut);

// create a torus object containing position, normal, texcoord & color components
HRESULT
CreateTorus(IDirect3DDevice9* pDevice, 
			int iSegments1, int iSegments2, float fRadius1, float fRadius2, 
			int* piNumVerticesOut, int* piNumTrianglesOut, int* piVertexSizeOut,
			IDirect3DVertexDeclaration9** ppVertexDeclarationOut,
			IDirect3DVertexBuffer9** ppVertexBufferOut,
			IDirect3DIndexBuffer9**	ppIndexBufferOut);


#endif // OBJECTS_H_INCLUDED

