//

#include <metal_stdlib>
using namespace metal;

[[vertex]] float4 vertexShader(
							   const device packed_float3 * triangleVertices [[buffer(5)]],
							   const ushort vertexIndex [[vertex_id]],
							   const constant float * timer [[buffer(7)]])
{
  float4x4 mat = float4x4(1.0f);
  mat[3][1] = sin(*timer);
  return mat * float4(triangleVertices[vertexIndex], 1.0f);
//  const float x = triangleVertices[vertexIndex].x;
//  const float z = triangleVertices[vertexIndex].z;
//  const float y = triangleVertices[vertexIndex].y + sin(*timer);
//  return float4(x, y, z, 1.0f);
}

[[fragment]] float4 fragmentShader() {
  return float4(1.0f, 0.0f, 1.0f, 1.0f);
}
