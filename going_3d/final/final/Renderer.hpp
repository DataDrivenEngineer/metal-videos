#include <memory>

#include <Metal/Metal.hpp>
#include <QuartzCore/CAMetalDrawable.hpp>

class Renderer {
public:
  Renderer(MTL::Device * const pDevice);
  ~Renderer();
  void drawFrame(const CA::MetalDrawable * const pDrawable, const MTL::Texture * const pDepthTexture);
private:
  MTL::Device * const _pDevice;
  MTL::CommandQueue * const _pCommandQueue;
  std::unique_ptr<MTL::RenderPipelineState, void(*)(MTL::RenderPipelineState *)> _pRenderPipelineState;
  float_t _angle;
  
  void buildShaders();
};
