//

#include <metal_stdlib>
using namespace metal;

[[vertex]] float4 vertexShader(
							   const device packed_float3 * triangleVertices [[buffer(5)]],
							   const ushort vertexIndex [[vertex_id]])
{
  return float4(triangleVertices[vertexIndex], 1.0f);
}

[[fragment]] float4 fragmentShader() {
  return float4(1.0f, 0.0f, 1.0f, 1.0f);
}
