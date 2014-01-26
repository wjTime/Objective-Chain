//
//  OCAUIKit+Colors.m
//  Objective-Chain
//
//  Created by Martin Kiss on 15.1.14.
//  Copyright (c) 2014 Martin Kiss. All rights reserved.
//

#import "OCAUIKit+Colors.h"





@implementation OCAUIKit (Colors)





#pragma mark -
#pragma mark Transformers
#pragma mark -


+ (OCATransformer *)colorFromCGColor {
    return [[OCAUIKit colorGetCGColor] reversed];
}


+ (OCATransformer *)colorGetCGColor {
    return [[OCATransformer fromClass:[UIColor class] toClass:nil
                           transform:^id(UIColor *input) {
                               
                               return (id)input.CGColor;
                               
                           } reverse:^UIColor *(id input) {
                               
                               CGColorRef color = (__bridge CGColorRef)input;
                               return [UIColor colorWithCGColor:color];
                           }]
            describe:@"CGColor from UIColor"
            reverse:@"UIColor from CGColor"];
}


+ (OCATransformer *)colorWithAlpha:(CGFloat)alpha {
    return [[OCATransformer fromClass:[UIColor class] toClass:[UIColor class]
                            transform:^UIColor *(UIColor *input) {
                                return [input colorWithAlphaComponent:alpha];
                                
                            } reverse:OCATransformationPass]
            describe:[NSString stringWithFormat:@"Color with aplha %@", @(alpha)]
            reverse:@"pass"];
}





@end


