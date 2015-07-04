//
//  PathSegment.m
//  pointer-tasks
//
//  Created by ricardo antonio cacho on 2015-07-04.
//  Copyright (c) 2015 rcacho. All rights reserved.

#import "PathSegment.h"



@implementation PathSegment

-(instancetype)init {
    self = [super self];
    
    if (self){
        self.contents = [PathSegment randomContents];
    }
    return self;
}

+(PathSegmentContents *)randomContents {
    
    
    PathSegmentContents *contents = [[PathSegmentContents alloc] init];
    return contents;
}

@end
