// 方向光
struct DirectionalLight
{
    float4 Color;
    float3 Direction;
};

// 点光
struct PointLight
{
    float4 Color;
    float3 Position;
    float Range;
    float3 Att;
};

// 聚光灯
struct SpotLight
{
    float4 Color;
    float3 Position;
    float Range;
    float3 Direction;
    float Spot;
    float3 Att;
};