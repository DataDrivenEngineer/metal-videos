#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION

#include "Renderer.hpp"

Renderer::Renderer(CA::MetalDrawable * const pDrawable, MTL::Device * const pDevice)
: _pDrawable(pDrawable),
  _pDevice(pDevice),
  _pCommandQueue(_pDevice->newCommandQueue())
{}

Renderer::~Renderer()
{
  _pCommandQueue->release();
}

void Renderer::draw() const
{
  MTL::CommandBuffer * pCmdBuf = _pCommandQueue->commandBuffer();
  
  MTL::RenderPassDescriptor * pRpd = MTL::RenderPassDescriptor::alloc()->init();
  pRpd->colorAttachments()->object(0)->setTexture(_pDrawable->texture());
  pRpd->colorAttachments()->object(0)->setLoadAction(MTL::LoadActionClear);
  pRpd->colorAttachments()->object(0)->setClearColor(MTL::ClearColor::Make(0.0, 1.0, 0.0, 1.0));
  
  MTL::RenderCommandEncoder * pEnc = pCmdBuf->renderCommandEncoder(pRpd);
  pEnc->endEncoding();
  pCmdBuf->presentDrawable(_pDrawable);
  pCmdBuf->commit();
  
  pRpd->release();
}
