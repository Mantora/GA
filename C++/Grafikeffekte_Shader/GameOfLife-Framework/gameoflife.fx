texture2D	g_tGameOfLifeInput;		// input texture for game of life simulation
texture2D	g_tTexture;				// texture to display, used by technique 'drawtexture'

float2		g_vTextureSize;			// size of game of life / input texture


// --------------------------------------------------------------------------------------------------------------------------------------------------------
sampler2D g_sTexture = 
sampler_state
{
	texture = g_tTexture;
};


// --------------------------------------------------------------------------------------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4	vPositionPS	: POSITION0;
	float2	vTexCoord	: TEXCOORD0;
};

VS_OUTPUT
vsMainQuad(float3 vPositionPS : POSITION0)
{
	VS_OUTPUT o;

	o.vPositionPS = float4(vPositionPS, 1);
	o.vTexCoord.x = 0.5 + 0.5 * vPositionPS.x;
	o.vTexCoord.y = 0.5 - 0.5 * vPositionPS.y;
	
	return o;
};

// --------------------------------------------------------------------------------------------------------------------------------------------------------
float4
psMainDrawTexture(float2 vTexCoord : TEXCOORD) : COLOR0
{
	return tex2D(g_sTexture, vTexCoord);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------
technique gameoflife
{
	// TODO
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------
technique drawtexture
{
	pass p0
	{
		Cullmode = none;
		ZEnable = false;
		VertexShader = compile vs_2_0 vsMainQuad();
		PixelShader = compile ps_2_0 psMainDrawTexture();
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------
