struct VTX_IN
{
    float4 vPos : POSITION;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

//  SV = SystemValue
struct VTX_OUT
{
    float4 vPos : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;    
};

cbuffer Transform : register(b0)
{
    float4 cbPos;
}

cbuffer MaterialData : register(b1)
{
    int cbiData;
    float cbfData;
    float2 cbxy;
    float3 cbxyz;
    float4 cbxyzw;
    matrix cbmat;
}

SamplerState pointSampler : register(s0);
SamplerState linearSampler : register(s1);
SamplerState anisotropicSampler : register(s2);

VTX_OUT VS_Test(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    output.vPos = _in.vPos + cbPos;
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
    return output;
}