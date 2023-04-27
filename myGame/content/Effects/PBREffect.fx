#include "include\CBuffer.fxh"
#include "include\Common.fxh"
#include "include\PBRCommon.fxh"
#include "include\ShadowMap.fxh"

/************* Resources *************/
Texture2D AlbedoTexture;
Texture2D NormalTexture;
Texture2D MetallicRoughnessTexture;

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
    float3 Tangent : TANGENT;
    float3 Bitangent : BINORMAL;
};

struct VS_OUTPUT
{
    float4 Position : SV_Position;
    float4 WorldPosition : POSITION;
    float3 Normal : NORMAL;
    float2 TextureCoordinate : TEXCOORD0;
    float3x3 TBN:TBN;
};

/************* Vertex Shader *************/

VS_OUTPUT vertex_shader(VS_INPUT IN)
{
    VS_OUTPUT OUT = (VS_OUTPUT) 0;
    OUT.Position = mul(IN.ObjectPosition, mul(World, ViewProjection));
    OUT.WorldPosition = mul(IN.ObjectPosition, World);
    OUT.TextureCoordinate = get_corrected_texture_coordinate(IN.TextureCoordinate);
    OUT.Normal = IN.Normal;
    OUT.TBN = float3x3(normalize(IN.Tangent), normalize(IN.Bitangent), normalize(IN.Normal));
    return OUT;
}

/************* Pixel Shader *************/

float4 pixel_shader(VS_OUTPUT IN) : SV_Target
{
    float3 albedo = AlbedoTexture.Sample(ColorSampler, IN.TextureCoordinate);
    float3 mr = MetallicRoughnessTexture.Sample(ColorSampler, IN.TextureCoordinate);
    float uMetallic = mr.g;
    float uRoughness = mr.b;
    albedo = pow(albedo, float3(2.2, 2.2, 2.2));

    float3 N = mul(normalize(NormalTexture.Sample(ColorSampler, IN.TextureCoordinate).xyz), IN.TBN);
    float3 V = normalize(CamPos.xyz - IN.WorldPosition.xyz);
    float NdotV = max(dot(N, V), 0.0);
 
    float3 F0 = float3(0.04, 0.04, 0.04);
    F0 = lerp(F0, albedo, uMetallic);

    float3 Lo = float3(0.0, 0.0, 0.0);
    
    for (int i = 0; i < NumDirLight; ++i)
    {
        float3 L = normalize(-DirectLights[i].Direction);
        float3 H = normalize(V + L);
        float NdotL = max(dot(N, L), 0.0);

        float3 radiance = DirectLights[i].Color.rgb * DirectLights[i].Color.a*1;

        float NDF = DistributionGGX(N, H, uRoughness);
        float G = GeometrySmith(N, V, L, uRoughness);
        float3 F = fresnelSchlick(F0, V, H);
      
        float3 numerator = NDF * G * F;
        float denominator = max((4.0 * NdotL * NdotV), 0.001);
        
        Lo += ((float3(1, 1, 1) - F) * (1 - uMetallic) * albedo / PI + numerator / denominator) * radiance * NdotL;
        //float3 BRDF = numerator / denominator;

        //Lo += BRDF * radiance * NdotL;
    }
    
    float3 color = Lo;

    //color = color / (color + float3(1.0, 1.0, 1.0));
    color = color + AmbientColor.rgb * AmbientColor.a * albedo;
    float4 OUT = float4(pow(color, 0.45), 1.0);
    return OUT;
}

VS_OUTPUT shadowmap_vert(VS_INPUT IN)
{
    VS_OUTPUT OUT;
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
    pass p1
    {
        
    }
}