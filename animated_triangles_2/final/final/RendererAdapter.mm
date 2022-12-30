#import "RendererAdapter.h"

@implementation RendererAdapter

- (nonnull instancetype) initWithMTKView:(MTKView *)pView
{
  self = [super init];
  _pRenderer = new Renderer((__bridge MTL::Device *)pView.device);
  return self;
}

-(void)drawInMTKView:(MTKView *)view
{
  _pRenderer->drawFrame((__bridge const CA::MetalDrawable * const)view.currentDrawable);
}

-(void)mtkView:(MTKView *)view drawableSizeWillChange:(CGSize)size
{
}

-(void)dealloc
{
  delete _pRenderer;
}
@end
