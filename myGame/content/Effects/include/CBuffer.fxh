#include "Light.fxh"

#define MaxDirextLightNum 10
#define MaxPointLightNum 10
#define MaxSpotLightNum 10

cbuffer CBChangesEveryDrawing
{
    float4x4 World : WORLD < string UIWidget="None"; >;
}

cbuffer CBChangesEveryFrame
{
    float4 CamPos : CAMPOSITION < string UIWidget="None"; >;
    float4x4 ViewProjection : VIEWPROJECTION < string UIWidget="None"; >;
}

cbuffer CBChangesOnResize
{
    //matrix g_Proj;
}

cbuffer CBChangesRarely
{
    float4 AmbientColor : AMBIENT <
		string UIName =  "Ambient Light";
		string UIWidget = "Color";
	> = { 1.0f, 1.0f, 1.0f, 0.0f };
    DirectionalLight DirectLights[MaxDirextLightNum];
    PointLight PointLights[MaxPointLightNum];
    SpotLight SpotLights[MaxSpotLightNum];
    int NumDirLight = 0;
    int NumPointLight = 0;
    int NumSpotLight = 0;
}