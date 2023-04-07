#include "include\CBuffer.fxh"
#include "include\Common.fxh"

/************* Resources *************/
Texture2D ColorTexture <
    string ResourceName = "default_color.dds";
    string UIName =  "Color Texture";
    string ResourceType = "2D";
>;

float P = 64;

SamplerState ColorSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

/************* Data Structures *************/

struct VS_INPUT
{
    float4 ObjectPosition : POSITION;
    float2 TextureCoordinate : TEXCOORD;
	float3 Normal : NORMAL;
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
    VS_OUTPUT OUT = (VS_OUTPUT) 0;
    OUT.Position = mul(IN.ObjectPosition, mul(World,ViewProjection));
    OUT.WorldPosition = mul(IN.ObjectPosition, World);
    OUT.TextureCoordinate = get_corrected_texture_coordinate(IN.TextureCoordinate);
    OUT.Normal = normalize(mul(float4(IN.Normal, 0), World).xyz);
	
    return OUT;
}

/************* Pixel Shader *************/

float4 pixel_shader(VS_OUTPUT IN) : SV_Target
{
    float3 normal = normalize(IN.Normal);
    float3 viewDirection = normalize(CamPos - IN.WorldPosition);
    float4 color = ColorTexture.Sample(ColorSampler, IN.TextureCoordinate);
    float3 ambient = AmbientColor.rgb * AmbientColor.a * color.rgb;
    float4 OUT = 0;
    OUT.rgb = ambient;
    for (int i = 0; i < NumDirLight; ++i)
    {
        float3 lightDirection = normalize(-DirectLights[i].Direction);
        float3 halfVector = normalize(viewDirection + lightDirection);
        float l_dot_n = dot(normal, lightDirection);
        float h_dot_n = dot(normal, halfVector);
        float3 diffuse = DirectLights[i].Color.a * DirectLights[i].Color.rgb * color.rgb * max(l_dot_n, 0);
        float3 specular = DirectLights[i].Color.a * DirectLights[i].Color.rgb * pow(max(0, h_dot_n), P);
        OUT.rgb += diffuse + specular;

    }
    OUT.a = color.a;
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