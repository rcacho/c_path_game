//
//  PathSegment.h
//  pointer-tasks
//
//  Created by ricardo antonio cacho on 2015-07-04.
//  Copyright (c) 2015 rcacho. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PathSegmentContents.h"

@interface PathSegment : NSObject

@property PathSegmentContents *contents;

@property PathSegment *mainBranch;

@property PathSegment *sideBranch;

-(instancetype)init;

+(PathSegmentContents *)randomContents;


@end
