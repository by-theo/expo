/**
 * Copyright (c) 2015-present, Horcrux.
 * All rights reserved.
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import "ABI44_0_0RNSVGNode.h"
#import "ABI44_0_0RNSVGLength.h"

@interface ABI44_0_0RNSVGLinearGradient : ABI44_0_0RNSVGNode

@property (nonatomic, strong) ABI44_0_0RNSVGLength *x1;
@property (nonatomic, strong) ABI44_0_0RNSVGLength *y1;
@property (nonatomic, strong) ABI44_0_0RNSVGLength *x2;
@property (nonatomic, strong) ABI44_0_0RNSVGLength *y2;
@property (nonatomic, copy) NSArray<NSNumber *> *gradient;
@property (nonatomic, assign) ABI44_0_0RNSVGUnits gradientUnits;
@property (nonatomic, assign) CGAffineTransform gradientTransform;

@end
