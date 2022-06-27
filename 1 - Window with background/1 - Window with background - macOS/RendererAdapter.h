//
//  RendererAdapter.h
//  1 - Window with background - macOS
//
//  Created by Dmitrii Belousov on 6/23/22.
//

#import "QuartzCore/CAMetalLayer.h"
#import "Metal/MTLDevice.h"
#import "Renderer.hpp"

@interface RendererAdapter : NSObject
{
  Renderer * _pRenderer;
}
-(void)draw:(id <CAMetalDrawable>) drawable device: (id <MTLDevice>) device;
@end
