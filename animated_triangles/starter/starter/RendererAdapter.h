#import "QuartzCore/CAMetalLayer.h"
#import "Metal/MTLDevice.h"
#import "Renderer.hpp"

@interface RendererAdapter : NSObject
{
  Renderer * _pRenderer;
}
-(void)draw:(id <CAMetalDrawable>) drawable device: (id <MTLDevice>) device;
@end
