//

#include <metal_stdlib>

using namespace metal;

struct VertexIn {
  packed_float3 position;
  packed_float3 color;
};

struct VertexOut {
  float4 position [[position]];
  float3 color;
};

[[vertex]] VertexOut vertexShader(
							   const constant VertexIn * vertices [[buffer(5)]],
							   const ushort vertexIndex [[vertex_id]],
							   const constant float & angle [[buffer(7)]])
{
  const float a = sin(angle);
  // rotation around x
  float4x4 rotX = float4x4(1.0f);
  rotX[1][1] = cos(a);
  rotX[1][2] = sin(a);
  rotX[2][1] = -sin(a);
  rotX[2][2] = cos(a);
  // rotation around y
  float4x4 rotY = float4x4(1.0f);
  rotY[0][0] = cos(a);
  rotY[0][2] = -sin(a);
  rotY[2][0] = sin(a);
  rotY[2][2] = cos(a);
  // normalize Z matrix
  float4x4 normZ = float4x4(1.0f);
  const float zNear = 0.01f;
  const float zFar = 100.0f;
  normZ[2][2] = (1 - zNear) / zFar;
  normZ[3][2] = zNear;
  const constant VertexIn & vData = vertices[vertexIndex];
  VertexOut ret
  {
	.position = normZ * rotY * rotX * float4(vData.position, 1.0f),
	.color = vData.color
  };
  return ret;
}

[[fragment]] float4 fragmentShader(VertexOut in [[stage_in]]) {
  return float4(in.color, 1.0f);
}
