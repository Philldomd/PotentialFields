cbuffer EntitySize : register(b0)
{
	float2 dim;
};

struct GeometryInputType
{
	float4 pos : POSITION;
	float4 color : COLOR;
};

struct PixelInputType
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
};

static const float2 resolution = float2(1024.0, 768.0);

[maxvertexcount(4)]
void main(point GeometryInputType input[1] : SV_POSITION, inout TriangleStream<PixelInputType> triStream)
{
	PixelInputType output = (PixelInputType)0;
	float4 pos  = input[0].pos;
	float4 color = input[0].color;


	//left bottom
	output.pos = float4((pos.x/resolution.x) * 2.0 - 1.0,
						((resolution.y - (pos.y + dim.y)) / resolution.y) * 2.0 - 1.0, 0.0, 1.0);
	output.color = input[0].color;
	triStream.Append(output);

	//left top
	output.pos = float4((pos.x / resolution.x) * 2.0 - 1.0,
						((resolution.y - pos.y) / resolution.y) * 2.0 - 1.0, 0.0, 1.0);
	output.color = input[0].color;
	triStream.Append(output);

	//right bottom
	output.pos = float4(((pos.x + dim.x) / resolution.x) * 2.0 - 1.0,
						((resolution.y - (pos.y + dim.y)) / resolution.y) * 2.0 - 1.0, 0.0, 1.0);
	output.color = input[0].color;
	triStream.Append(output);

	//right top
	output.pos = float4(((pos.x + dim.x) / resolution.x) * 2.0 - 1.0,
						((resolution.y - pos.y) / resolution.y) * 2.0 - 1.0, 0.0, 1.0);
	output.color = input[0].color;
	triStream.Append(output);
}