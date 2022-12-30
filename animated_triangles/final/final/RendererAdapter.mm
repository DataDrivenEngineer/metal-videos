#import "RendererAdapter.h"

@implementation RendererAdapter
//- (void)draw:(id <CAMetalDrawable>) drawable device: (id <MTLDevice>) device
//{
//  _pRenderer = new Renderer((__bridge CA::MetalDrawable *)drawable, (__bridge MTL::Device *)device);
//  _pRenderer->draw();
//}
-(nonnull instancetype) initWithMTKView: (MTKView *)pView
{
  self = [super init];
  _pRenderer = new Renderer((__bridge MTL::Device *)pView.device);
  return self;
}
-(void)drawInMTKView:(MTKView *)view
{
  _pRenderer->drawFrame((__bridge CA::MetalDrawable *)view.currentDrawable);
}
-(void) mtkView:(MTKView *)view drawableSizeWillChange:(CGSize)size
{
}

-(void)dealloc
{
  delete _pRenderer;
}
@end
