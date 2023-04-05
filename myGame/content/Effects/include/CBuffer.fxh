#include "Light.fxh"

#define MaxDirextLightNum 10
#define MaxPointLightNum 10
#define MaxSpotLightNum 10

cbuffer CBChangesEveryDrawing : register(b0)
{
    matrix g_World;
}

cbuffer CBChangesEveryFrame : register(b1)
{
    matrix g_View;
    float3 g_EyePosW;
}

cbuffer CBChangesOnResize : register(b2)
{
    matrix g_Proj;
}

cbuffer CBChangesRarely : register(b3)
{
    float4 g_AmbientColor;
    DirectionalLight g_DirLight[MaxDirextLightNum];
    PointLight g_PointLight[MaxPointLightNum];
    SpotLight g_SpotLight[MaxSpotLightNum];
    int g_NumDirLight;
    int g_NumPointLight;
    int g_NumSpotLight;
}