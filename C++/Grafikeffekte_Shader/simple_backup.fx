// global effect parameters
float4x4	g_mWorld;
float4x4	g_mView;
float4x4	g_mProjection;

float		g_fTime;

texture		g_tTexture < string SasResourceAddress = "earth_diffuse.dds"; >;
sampler		g_sTexture =
sampler_state
{
	texture = g_tTexture;
};

const float PI = 3.14159265;

// -----------------------------------------------------------------------------

struct TInputVertex
{
	float3	vPositionOS	: POSITION0;
	float3	vNormalOS	: NORMAL0;
	float4	vColor		: COLOR0;
	float2	vTexCoord	: TEXCOORD0;
};

struct TOutputVertex
{
	float4	vPositionPS	: POSITION0;
	float4	vColor		: COLOR0;
	float2	vTexCoord	: TEXCOORD0;
	float3	vNormal		: TEXCOORD1;

	float fPointSize : PSIZE;
};

// -----------------------------------------------------------------------------
TOutputVertex
vsMain(TInputVertex i)
{
	const float4x4 mWorldView = mul(g_mWorld, g_mView);
	const float4x4 mWorldViewProjection = mul(mWorldView, g_mProjection);
	
	//
//	i.vPositionOS.x += i.vNormalOS*sin(g_fTime*g_fTime*PI)*0.1;
	i.vPositionOS.x += i.vNormalOS*sin(g_fTime+(i.vTexCoord.y*5+i.vTexCoord.x*6)*2*PI)*0.1;


	TOutputVertex o;
	o.vPositionPS = mul(float4(i.vPositionOS, 1), mWorldViewProjection);
	o.vColor = i.vColor;
	o.vTexCoord = i.vTexCoord;
	o.vNormal = i.vNormalOS;
	o.fPointSize = g_fTime*0.1;
	
	return o;	
}

TOutputVertex
vsOutline(TInputVertex i)
{
	i.vPositionOS += i.vNormalOS*0.01;
	i.vColor = float4(1,1,1,0);
	
	return vsMain(i);	
}

// -----------------------------------------------------------------------------
float4
psMain(TOutputVertex i) : COLOR0
{
	i.vTexCoord.x += g_fTime+sin( i.vTexCoord.y * PI * 2)* 0.4;
	i.vTexCoord.y += g_fTime+sin( i.vTexCoord.x * PI * 2)* 0.4;
	return tex2D( g_sTexture, i.vTexCoord);


//	return g_fTime%sin(g_fTime) ;
//	return i.vColor;
}

// -----------------------------------------------------------------------------
// techniques
technique MyTechnique
{
	//pass definition
	pass p1
	{
		//states
		VertexShader = compile vs_2_0 vsMain();
		PixelShader = compile ps_2_0 psMain();

		Fillmode = Solid;
//		ClipPlaneEnable = 1; //BitKombination	

//		ColorWriteEnable = Red;
		Shademode = Flat;
	}

	pass p2
	{
		VertexShader = compile vs_2_0 vsOutline();
		PixelShader = NULL;
		Cullmode = CW;
	}
}

// -----------------------------------------------------------------------------
