// global effect parameters
float4x4	g_mWorld;
float4x4	g_mView;
float4x4	g_mViewInverse;
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
	{1.0, 0.5, -1.5},
	{3, 2.5, 2.0},
	{0.5, 0.5, 0.5}
};


texture		g_tEnvironmentMap 	< string SasResourceAddress = "uffizi_cross.dds"; >;

sampler		g_sEnvironmentMap =
sampler_state {
	texture = g_tEnvironmentMap;
	MipFilter = Linear;
	MagFilter = Linear;
	MinFilter = Linear;
};


// material properties
texture		g_tDiffuseMap 	< string SasResourceAddress = "earth_diffuse.dds"; >;

sampler		g_sDiffuseMap =
sampler_state {
	texture = g_tDiffuseMap;
	MipFilter = Linear;
	MagFilter = Linear;
	MinFilter = Linear;
};

texture		g_tNormalMap 	< string SasResourceAddress = "EarthNormalMap.jpg"; >;

sampler		g_sNormalMap =
sampler_state {
	texture = g_tNormalMap;
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
float		g_fSpecularPower = 50;		// power value for phong shader / defines specular highlight size

// -----------------------------------------------------------------------------

struct TInputVertex
{
	float3	vPositionOS	: POSITION0;
    float3  vTangentOS  : TANGENT0;
    float3  vBinormalOS : BINORMAL0;
	float3	vNormalOS	: NORMAL0;
	float4	vColor		: COLOR0;
	float2	vTexCoord	: TEXCOORD0;
};

struct TOutputVertex
{
	float4	vPositionPS	: POSITION0;
	float4	vColor		: COLOR0;
	float2	vTexCoord	: TEXCOORD0;

	float3	vPositionWS	: TEXCOORD1;
	float3	vNormalWS	: TEXCOORD2;

    float3  vTangentWS  : TEXCOORD3;
    float3  vBinormalWS : TEXCOORD4;
	
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

	o.vNormalWS = mul(float4(i.vNormalOS, 0), g_mWorld).xyz; //Object Space to WorldSpace
    o.vTangentWS = mul( float4( i.vTangentOS, 0), g_mWorld).xyz;
    o.vBinormalWS = mul( float4( i.vBinormalOS, 0), g_mWorld).xyz;

	o.fPointSize = 4.0;
	
	return o;	
}

// -----------------------------------------------------------------------------

float4
psMain(TOutputVertex i) : COLOR0
{
    float3 vNormalTS = tex2D( g_sNormalMap, i.vTexCoord) * 2 - 1; //*2-1 um Wertebereich anzupassen

    float3x3 mTStoWS = float3x3( i.vTangentWS, i.vBinormalWS, i.vNormalWS );
    i.vNormalWS = mul( vNormalTS, mTStoWS );


	float3 vCameraPositionWS = mul(float4(0,0,0,1), g_mViewInverse);
	float3 vEyeVecWS = normalize(vCameraPositionWS - i.vPositionWS);

    if( dot( vEyeVecWS, i.vNormalWS)  < 0 )
    {
        //return float4(1,0,0,0); //shader printf
       // float3 vTmp = cross( vEyeVecWS, i.vNormalWS);
        float3 vTmp = cross(vEyeVecWS, i.vNormalWS);
		i.vNormalWS = cross(vTmp, vEyeVecWS);
    }
    else
    {
        //return float4(0,1,0,0); //shader printf
    }

    // spherical environment map
/*	float3 v = normalize(float3(vReflectedEyeVecWS.x, 0, vReflectedEyeVecWS.z));
	float fAlpha = v.z > 0 ? acos(v.x) : -acos(v.x);
	float fBeta = -asin(vReflectedEyeVecWS.y);
*/
	i.vNormalWS = normalize(i.vNormalWS);







	float3 vSurfaceToLightWS = g_xLight.vPositionWS - i.vPositionWS;
	float fLightDistance = length(vSurfaceToLightWS);

	float fLightIntensity = 1 / (g_xLight.vAttenuation.x +
								 g_xLight.vAttenuation.y * fLightDistance +
								 g_xLight.vAttenuation.z * fLightDistance * fLightDistance);
	
	float3 vLightVecWS = normalize(vSurfaceToLightWS);
	float fDiffuseReflectivity = max(dot(i.vNormalWS, vLightVecWS), 0);							// lambert
	float4 vDiffuseMaterial = tex2D(g_sDiffuseMap, i.vTexCoord);


	float3 vReflectionWS = -reflect(vLightVecWS, i.vNormalWS);


	float fSpecularReflectivity = pow(max(dot(vReflectionWS, vEyeVecWS), 0), g_fSpecularPower);	// phong
	float4 vSpecularMaterial = tex2D(g_sSpecularMap, i.vTexCoord);

	float fAmbientIntensity = 0.1; 
	float fAmbientReflectivity = 1; 
	float4 vAmbientMaterial = tex2D(g_sDiffuseMap, i.vTexCoord);

	float3 vLightingColor = g_xLight.vColor * fAmbientIntensity * fAmbientReflectivity * vAmbientMaterial
						  + g_xLight.vColor * fLightIntensity * fDiffuseReflectivity * vDiffuseMaterial
						  + g_xLight.vColor * fLightIntensity * fSpecularReflectivity * vSpecularMaterial;



	float3 vReflectedEyeVecWS = -reflect(vEyeVecWS, i.vNormalWS);
	
	/* plane
	float fPlaneHeight = 0.1;
	float2 vEnvironmentTexCoord = vReflectedEyeVecWS.xz / vReflectedEyeVecWS.y * fPlaneHeight;
	vColor = tex2D(g_sEnvironmentMap, vEnvironmentTexCoord);
	*/

	/* spherical environment map
	float3 v = normalize(float3(vReflectedEyeVecWS.x, 0, vReflectedEyeVecWS.z));
	float fAlpha = v.z > 0 ? acos(v.x) : -acos(v.x);
	float fBeta = -asin(vReflectedEyeVecWS.y);

	float fPi = 3.14159265358;
	float2 vEnvironmentTexCoord = float2(fAlpha / fPi * 0.5, 
										(fBeta + fPi / 2) / fPi);
	vColor = tex2D(g_sEnvironmentMap, vEnvironmentTexCoord);
	*/

	float3 vReflectionColor = texCUBE(g_sEnvironmentMap, vReflectedEyeVecWS);


	float4 vColor;
	float fFresnellValue = pow(abs(dot(i.vNormalWS, vEyeVecWS) + 1), -8) * vSpecularMaterial;
	vColor.rgb = lerp(vLightingColor, vReflectionColor, fFresnellValue);
	vColor.a = 1;
	return vColor;
}

// -----------------------------------------------------------------------------
// techniques
technique MyTechnique
{
	pass object
	{
		VertexShader = compile vs_3_0 vsMain();
		PixelShader = compile ps_3_0 psMain();
	}
}

// -----------------------------------------------------------------------------
