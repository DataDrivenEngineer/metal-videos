#import "QuartzCore/CAMetalLayer.h"
#import "Metal/MTLDevice.h"
#import <MetalKit/MTKView.h>
#import "Renderer.hpp"

@interface RendererAdapter : NSObject<MTKViewDelegate>
{
  Renderer * _pRenderer;
}
-(nonnull instancetype) initWithMTKView: (MTKView *)pView;
@end
