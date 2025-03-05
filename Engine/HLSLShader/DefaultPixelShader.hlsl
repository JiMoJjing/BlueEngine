struct PixelInput
{
    float4 position : SV_Position;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
};

//// Texture.
//Texture2D diffuseMap : register(t0);
//SamplerState diffuseSampler : register(s0);

float4 main(PixelInput input) : SV_TARGET
{
    return float4(input.color, 1);
}