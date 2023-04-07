// �����
struct DirectionalLight
{
    float4 Color;
    float3 Direction;
};

// ���
struct PointLight
{
    float4 Color;
    float3 Position;
    float Range;
    float3 Att;
};

// �۹��
struct SpotLight
{
    float4 Color;
    float3 Position;
    float Range;
    float3 Direction;
    float Spot;
    float3 Att;
};