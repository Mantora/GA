// global effect parameters
float4x4	g_mWorld;
float4x4	g_mView;
float4x4    g_mViewInverse;
float4x4	g_mProjection;

float		g_fTime;


struct TLightSource
{
	float3		vPositionWS;		// position of light in world space
	float3		vColor;				// combines color and intensity
	float3		vAttenuation;		// defines light intensity depending on distance
};

TLightSource	g_xLight = 
{
	{1.0, 0.5, -0.5},
	{3, 2.5, 2.0},
	{0.5, 0.5, 0.5 }
};


// material properties
texture		g_tDiffuseMap 	< string SasResourceAddress = "Earth_Diffuse.dds"; >;

sampler		g_sDiffuseMap =
sampler_state {
	texture = g_tDiffuseMap;
	MipFilter = Linear;
	MagFilter = Linear;
	MinFilter = Linear;
};

texture		g_tSpecularMap 	< string SasResourceAddress = "Earth_Specular.jpg"; >;

sampler		g_sSpecularMap =
sampler_state {
	texture = g_tSpecularMap;
	MipFilter = Linear;
	MagFilter = Linear;
	MinFilter = Linear;
};


texture		g_tEnviromentMap 	< string SasResourceAddress = "Spheremap.jpg"; >;

sampler		g_sEnviromentMap =
sampler_state {
	texture = g_tEnviromentMap;
	MipFilter = Linear;
	MagFilter = Linear;
	MinFilter = Linear;
};


float		g_fSpecularPower = 50;		// power value for phong shader / defines specular highlight size

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

    float3  vPositionWS : TEXCOORD1;
	float3	vNormalWS	: TEXCOORD2;
	
	float	fPointSize	: PSIZE;
};

// -----------------------------------------------------------------------------
TOutputVertex
vsMain(TInputVertex i)
{
	const float4x4 mWorldView = mul(g_mWorld, g_mView);
	const float4x4 mWorldViewProjection = mul(mWorldView, g_mProjection);
	
	TOutputVertex o;
	o.vPositionPS = mul(float4(i.vPositionOS, 1), mWorldViewProjection);
	o.vColor = i.vColor;
	o.vTexCoord = i.vTexCoord;
    o.vPositionWS = mul(float4(i.vPositionOS, 1), g_mWorld).xyz;
	o.vNormalWS = mul(float4(i.vNormalOS, 0), g_mWorld).xyz;
	o.fPointSize = 4.0;
	
	return o;	
}

// -----------------------------------------------------------------------------

float4
psMain(TOutputVertex i) : COLOR0
{
    i.vNormalWS = normalize(i.vNormalWS);






    float3 vSurfaceToLightWS = g_xLight.vPositionWS - i.vPositionWS;
    float fLightDistance = length( vSurfaceToLightWS );

    float fLightIntensity = 1 / ( g_xLight.vAttenuation.x + 
                                 g_xLight.vAttenuation.y * fLightDistance + 
                                 g_xLight.vAttenuation.z * fLightDistance  * fLightDistance );

    float3 vLightVecWS = normalize( vSurfaceToLightWS );

    float fDiffuseReflectivity = max( dot( i.vNormalWS, vLightVecWS), 0); //lambert
    float4 vDiffuseMaterial = tex2D( g_sDiffuseMap, i.vTexCoord);

    float3 vReflectionWS = -reflect( vLightVecWS, i.vNormalWS );
    float3 vCameraPositionWS = mul( float4(0,0,0,1), g_mViewInverse );
    float3 vEyeVecWS = normalize( vCameraPositionWS - i.vPositionWS );
    float fSpecularReflectivity = pow( max( dot(vReflectionWS, vEyeVecWS), 0 ), 5 ); //phong
    float4 vSpecularMaterial = tex2D( g_sSpecularMap, i.vTexCoord );

    float fAmbientIntensity = 0.1;
    float fAmbientReflectivity = 1;
    float4 vAmbientMaterial = tex2D( g_sDiffuseMap, i.vTexCoord);

    float4 vColor = 0;
    vColor.rgb = g_xLight.vColor * fAmbientIntensity * fAmbientReflectivity * vAmbientMaterial +
                 g_xLight.vColor * fLightIntensity * fDiffuseReflectivity * vDiffuseMaterial +
                 g_xLight.vColor * fLightIntensity * fSpecularReflectivity * vSpecularMaterial;

    vColor.a = 1;


    float3 vReflectedEyeVecWS = -reflect( vEyeVecWS, i.vNormalWS );

    //float fPlaneHeight = 0.1;
    //float2 vEnvironmentTexCoord = vReflectedEyeVecWS.xz / vReflectedEyeVecWS.y * fPlaneHeight;

    float3 v = normalize( float3( vReflectedEyeVecWS.x, 0, vReflectedEyeVecWS.z ));
    float fAlpha = v.z > 0 ? acos(v.x) : -acos(v.x);
    float fBeta = -asin( vReflectedEyeVecWS.y );

    float fPi = 3.14159265358;
    float2 vEnvironmentTexCoord = float2( fAlpha / fPi * 0.5, 
                                         (fBeta + fPi / 2) / fPi);

    vColor = tex2D( g_sEnviromentMap, vEnvironmentTexCoord);


    return vColor;
}

// -----------------------------------------------------------------------------
// techniques
technique MyTechnique
{
	pass object
	{
		VertexShader = compile vs_2_0 vsMain();
		PixelShader = compile ps_2_0 psMain();
	}
}

// -----------------------------------------------------------------------------
