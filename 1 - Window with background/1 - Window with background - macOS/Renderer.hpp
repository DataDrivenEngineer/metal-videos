//
//  Renderer.hpp
//  1 - Window with background - macOS
//
//  Created by Dmitrii Belousov on 6/23/22.
//

#include "Metal/Metal.hpp"
#include "QuartzCore/CAMetalDrawable.hpp"

class Renderer {
public:
  Renderer(CA::MetalDrawable * const pDrawable, MTL::Device * const pDevice);
  ~Renderer();
  void draw() const;
private:
  CA::MetalDrawable * _pDrawable;
  MTL::Device * const _pDevice;
  MTL::CommandQueue * const _pCommandQueue;
};
