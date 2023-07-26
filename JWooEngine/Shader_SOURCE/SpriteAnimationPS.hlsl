#include "globals.hlsli"

struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};


float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float4) 0.0f;
    
    // 1200 1032 // 120 130
    // 1080 -> 540
    // -540 + 1200 
    color = albedoTexture.Sample(anisotropicSampler, In.UV);

    float2 diff = (AtlasSize - SpriteSize) / 2.0f;
    float2 frameUV = (SpriteLeftTop - diff - SpriteOffset);
    
    if (animationType == 1)
    {
        float2 UV = frameUV + (AtlasSize * In.UV);
    
        if (UV.x < SpriteLeftTop.x || UV.x > SpriteLeftTop.x + SpriteSize.x
        || UV.y < SpriteLeftTop.y || UV.y > SpriteLeftTop.y + SpriteSize.y)
            discard;
    
        color = atlasTexture.Sample(pointSampler, UV);
    }
    else 
    {
        float2 UV = frameUV + float2(AtlasSize.x * (1.0f - In.UV.x), AtlasSize.y * In.UV.y);

        if (UV.x < SpriteLeftTop.x || UV.x > SpriteLeftTop.x + SpriteSize.x
        || UV.y < SpriteLeftTop.y || UV.y > SpriteLeftTop.y + SpriteSize.y)
            discard;

        color = atlasTexture.Sample(pointSampler, UV);
    }
    
    color *= lightsAttribute[0].color;
    
    return color;
}