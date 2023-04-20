#include "include\CBuffer.fxh"
#include "include\Common.fxh"

TextureCube ColorTexture <
    string ResourceName = "default_color.dds";
    string UIName =  "Color Texture";
    string ResourceType = "2D";
>;
SamplerState ColorSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = WRAP;
    AddressV = WRAP;
};
float P = 64;
struct VS_INPUT
{
    float4 ObjectPosition : POSITION;
    float2 TextureCoordinate : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 Position : SV_Position;
    float4 WorldPosition : POSITION;
    float3 Normal : NORMAL;
    float2 TextureCoordinate : TEXCOORD0;
};

/************* Vertex Shader *************/

VS_OUTPUT vertex_shader(VS_INPUT IN)
{
    VS_OUTPUT OUT;
    OUT.WorldPosition = IN.ObjectPosition;
    IN.ObjectPosition.xyz += CamPos.xyz;
    IN.ObjectPosition.w = 1.0f;
    OUT.Position = mul(IN.ObjectPosition, ViewProjection).xyww;
    return OUT;
}

/************* Pixel Shader *************/

float4 pixel_shader(VS_OUTPUT IN) : SV_Target
{
    //float4 OUT = float4(IN.WorldPosition.xyz + (float3)0.5f, 1.0f);
    float4 OUT = ColorTexture.Sample(ColorSampler, IN.WorldPosition.xyz);
    return OUT;
}

/************* Techniques *************/

technique11 main11
{
    pass p0
    {
        SetVertexShader(CompileShader(vs_5_0, vertex_shader()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_5_0, pixel_shader()));
    }
}