

struct VSInput
{
	float3 Position : POSITION0;
	float4 Color :COLOR0;
};
struct VSOutput
{
	float4 Position : SV_POSITION; 
	float4 Color : COLOR0;
};


VSOutput VSMain(VSInput input)
{
	VSOutput output; 
	output.Position = float4(input.Position,1);
	output.Color = input.Color; 
	return output;
}

struct PSInput
{
	float4 position : SV_POSITION; 
	float4 color : COLOR0; 
};

float4 PSMain(PSInput input) :SV_TARGET
{
	return input.color; 
}