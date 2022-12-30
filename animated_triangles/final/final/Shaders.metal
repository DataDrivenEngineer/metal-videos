//

#include <metal_stdlib>
using namespace metal;

[[vertex]] float4 vertexShader(
							   const device packed_float3 * triangleVertices [[buffer(5)]],
							   const constant float * timer [[buffer(7)]],
							   const ushort vertexIndex [[vertex_id]])
{
  const float x = triangleVertices[vertexIndex].x;
  const float z = triangleVertices[vertexIndex].z;
  const float y = triangleVertices[vertexIndex].y + sin(*timer);
  // y - 1 to y + 1
  // timer = 0, sin(timer) = 0
  // timer = 0.01, sin(timer) = 0.00017, y = y + 0.00017
  // timer = 0.02, sin(timer) = 0.00035, y = y + 0.00035
  //  return float4(triangleVertices[vertexIndex], 1.0f);
  return float4(x, y, z, 1.0f);
}

[[fragment]] float4 fragmentShader() {
  return float4(1.0f, 0.0f, 1.0f, 1.0f);
}
