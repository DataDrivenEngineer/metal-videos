#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION

#include <vector>

#include "Renderer.hpp"

static const std::vector<float> cubeVertices() {
  return std::vector<float> {
	// front face
	-0.5f, 0.5f, 0.0f,  // vertex #0 - coordinates
	1.0f, 0.0f, 0.0f, // color = red
	-0.5f, -0.5f, 0.0f,  // vertex #1 - coordinates
	1.0f, 0.0f, 0.0f, // color = red
	0.5f, -0.5f, 0.0f,   // vertex #2 - coordinates
	1.0f, 0.0f, 0.0f, // color = red
	0.5f, -0.5f, 0.0f,   // vertex #2 - coordinates
	1.0f, 0.0f, 0.0f, // color = red
	0.5f, 0.5f, 0.0f,   // vertex #3 - coordinates
	1.0f, 0.0f, 0.0f, // color = red
	-0.5f, 0.5f, 0.0f, // vertex #0 - coordinates
	1.0f, 0.0f, 0.0f, // color = red
	// back face
	-0.5f, 0.5f, 1.0f,  // vertex #4 - coordinates
	0.0f, 1.0f, 0.0f, // color = green
	-0.5f, -0.5f, 1.0f,  // vertex #5 - coordinates
	0.0f, 1.0f, 0.0f, // color = green
	0.5f, -0.5f, 1.0f,   // vertex #6 - coordinates
	0.0f, 1.0f, 0.0f, // color = green
	0.5f, -0.5f, 1.0f,   // vertex #6 - coordinates
	0.0f, 1.0f, 0.0f, // color = green
	0.5f, 0.5f, 1.0f,    // vertex #7 - coordinates
	0.0f, 1.0f, 0.0f, // color = green
	-0.5f, 0.5f, 1.0f,  // vertex #4 - coordinates
	0.0f, 1.0f, 0.0f, // color = green
	// left face
	-0.5f, 0.5f, 1.0f,  // vertex #4 - coordinates
	0.0f, 0.0f, 1.0f, // color = blue
	-0.5f, -0.5f, 1.0f,  // vertex #5 - coordinates
	0.0f, 0.0f, 1.0f, // color = blue
	-0.5f, -0.5f, 0.0f,  // vertex #1 - coordinates
	0.0f, 0.0f, 1.0f, // color = blue
	-0.5f, -0.5f, 0.0f,  // vertex #1 - coordinates
	0.0f, 0.0f, 1.0f, // color = blue
	-0.5f, 0.5f, 0.0f,  // vertex #0 - coordinates
	0.0f, 0.0f, 1.0f, // color = blue
	-0.5f, 0.5f, 1.0f,  // vertex #4 - coordinates
	0.0f, 0.0f, 1.0f, // color = blue
	// right face
	0.5f, 0.5f, 0.0f,   // vertex #3 - coordinates
	1.0f, 0.4f, 0.0f, // color = orange
	0.5f, -0.5f, 0.0f,   // vertex #2 - coordinates
	1.0f, 0.4f, 0.0f, // color = orange
	0.5f, -0.5f, 1.0f,   // vertex #6 - coordinates
	1.0f, 0.4f, 0.0f, // color = orange
	0.5f, -0.5f, 1.0f,   // vertex #6 - coordinates
	1.0f, 0.4f, 0.0f, // color = orange
	0.5f, 0.5f, 1.0f,    // vertex #7 - coordinates
	1.0f, 0.4f, 0.0f, // color = orange
	0.5f, 0.5f, 0.0f,   // vertex #3 - coordinates
	1.0f, 0.4f, 0.0f, // color = orange
	// top face
	-0.5f, 0.5f, 1.0f,  // vertex #4 - coordinates
	1.0f, 0.0f, 1.0f, // color = purple
	-0.5f, 0.5f, 0.0f,  // vertex #0 - coordinates
	1.0f, 0.0f, 1.0f, // color = purple
	0.5f, 0.5f, 0.0f,   // vertex #3 - coordinates
	1.0f, 0.0f, 1.0f, // color = purple
	0.5f, 0.5f, 0.0f,   // vertex #3 - coordinates
	1.0f, 0.0f, 1.0f, // color = purple
	0.5f, 0.5f, 1.0f,    // vertex #7 - coordinates
	1.0f, 0.0f, 1.0f, // color = purple
	-0.5f, 0.5f, 1.0f,  // vertex #4 - coordinates
	1.0f, 0.0f, 1.0f, // color = purple
	// bottom face
	-0.5f, -0.5f, 1.0f,  // vertex #5 - coordinates
	0.0f, 1.0f, 1.0f, // color = cyan
	-0.5f, -0.5f, 0.0f,  // vertex #1 - coordinates
	0.0f, 1.0f, 1.0f, // color = cyan
	0.5f, -0.5f, 0.0f,   // vertex #2 - coordinates
	0.0f, 1.0f, 1.0f, // color = cyan
	0.5f, -0.5f, 0.0f,   // vertex #2 - coordinates
	0.0f, 1.0f, 1.0f, // color = cyan
	0.5f, -0.5f, 1.0f,   // vertex #6 - coordinates
	0.0f, 1.0f, 1.0f, // color = cyan
	-0.5f, -0.5f, 1.0f,  // vertex #5 - coordinates
	0.0f, 1.0f, 1.0f, // color = cyan
  };
}

Renderer::Renderer(MTL::Device * const pDevice)
: _pDevice(pDevice),
  _pCommandQueue(_pDevice->newCommandQueue()),
  _pRenderPipelineState(nullptr, [](MTL::RenderPipelineState * const p) { p->release(); }),
  _angle()
{
  buildShaders();
}

Renderer::~Renderer()
{
  _pCommandQueue->release();
}


void Renderer::buildShaders() {
  const std::unique_ptr<MTL::Library, void(*)(MTL::Library * const)> pLib(_pDevice->newDefaultLibrary(), [](MTL::Library * const l) { l->release(); });
  const std::unique_ptr<MTL::Function, void(*)(MTL::Function * const)> pVertexFn(pLib.get()->newFunction(NS::String::string("vertexShader", NS::UTF8StringEncoding)), [](MTL::Function * const f) { f->release(); });
  const std::unique_ptr<MTL::Function, void(*)(MTL::Function * const)> pFragmentFn(pLib.get()->newFunction(NS::String::string("fragmentShader", NS::UTF8StringEncoding)), [](MTL::Function * const f) { f->release(); });
  
  const std::unique_ptr<MTL::RenderPipelineDescriptor, void(*)(MTL::RenderPipelineDescriptor * const)> pRpd(MTL::RenderPipelineDescriptor::alloc()->init(), [](MTL::RenderPipelineDescriptor * const d) { d->release(); });
  pRpd.get()->setVertexFunction(pVertexFn.get());
  pRpd.get()->setFragmentFunction(pFragmentFn.get());
  pRpd.get()->colorAttachments()->object(0)->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
  pRpd->setDepthAttachmentPixelFormat(MTL::PixelFormatDepth32Float);
  
  NS::Error * pErr {nullptr};
  _pRenderPipelineState.reset(_pDevice->newRenderPipelineState(pRpd.get(), &pErr));
  if (!_pRenderPipelineState.get()) {
	__builtin_printf("%s", pErr->localizedDescription()->utf8String());
  }
}

void Renderer::drawFrame(const CA::MetalDrawable * const pDrawable, const MTL::Texture * const pDepthTexture) {
  MTL::CommandBuffer * pCmdBuf = _pCommandQueue->commandBuffer();

  MTL::RenderPassDescriptor * pRpd = MTL::RenderPassDescriptor::alloc()->init();
  pRpd->colorAttachments()->object(0)->setTexture(pDrawable->texture());
  pRpd->colorAttachments()->object(0)->setLoadAction(MTL::LoadActionClear);
  pRpd->colorAttachments()->object(0)->setClearColor(MTL::ClearColor::Make(0.0, 0.0, 0.0, 1.0));
  
  const std::unique_ptr<MTL::RenderPassDepthAttachmentDescriptor, void(*)(MTL::RenderPassDepthAttachmentDescriptor * const)> pRenderPassDepthAttachmentDescriptor(MTL::RenderPassDepthAttachmentDescriptor::alloc()->init(), [](MTL::RenderPassDepthAttachmentDescriptor * const d) { d->release(); });
  pRenderPassDepthAttachmentDescriptor->setTexture(pDepthTexture);
  
  pRpd->setDepthAttachment(pRenderPassDepthAttachmentDescriptor.get());
  
  const std::unique_ptr<MTL::DepthStencilDescriptor, void(*)(MTL::DepthStencilDescriptor * const)> pDepthStencilDescriptor(MTL::DepthStencilDescriptor::alloc()->init(), [](MTL::DepthStencilDescriptor * const d) { d->release(); });
  pDepthStencilDescriptor->setDepthWriteEnabled(true);
  pDepthStencilDescriptor->setDepthCompareFunction(MTL::CompareFunctionLess);
  
  const std::unique_ptr<MTL::DepthStencilState, void(*)(MTL::DepthStencilState * const)> pDepthStencilState(_pDevice->newDepthStencilState(pDepthStencilDescriptor.get()), [](MTL::DepthStencilState * const d) { d->release(); });
  
  const std::vector<float> vertices = cubeVertices();
  
  const std::unique_ptr<MTL::Buffer, void(*)(MTL::Buffer * const)> pVertexBuffer(_pDevice->newBuffer(vertices.data(), sizeof(float) * vertices.size(), MTL::ResourceStorageModeShared), [](MTL::Buffer * const b) { b->release(); });
  
  _angle += 0.01f;
  
  MTL::RenderCommandEncoder * pEnc = pCmdBuf->renderCommandEncoder(pRpd);
  pEnc->setRenderPipelineState(_pRenderPipelineState.get());
  pEnc->setDepthStencilState(pDepthStencilState.get());
  pEnc->setVertexBuffer(pVertexBuffer.get(), 0, 5);
  pEnc->setVertexBytes(&_angle, sizeof(float_t), 7);
  pEnc->drawPrimitives(MTL::PrimitiveTypeTriangle, NS::UInteger(0), 36);
  pEnc->endEncoding();
  pCmdBuf->presentDrawable(pDrawable);
  pCmdBuf->commit();

  pRpd->release();
}
