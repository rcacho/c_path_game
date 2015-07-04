//
//  AdventureGenerator.m
//  pointer-tasks
//
//  Created by ricardo antonio cacho on 2015-07-04.
//  Copyright (c) 2015 rcacho. All rights reserved.
//

#import "AdventureGenerator.h"

@implementation AdventureGenerator

-(PathSegment *)createAdventure {
    
    // need to generate randomness
    
    // create "home" - PathSegment
    
    // instantiate singletons -- gem and spyglass
    
    PathSegment *leftBranchCursor = home; // primary
    PathSegment *rightBranchCursor = NULL;
    int i;
    for ( i = 0; i < 100; i++) {
        
        if (leftBranchCursor != NULL) {
            // append to left branch
            leftBranchCursor->mainRoad = CreatePathSegment(RandomContents(gem, spyglass));
            leftBranchCursor = leftBranchCursor->mainRoad;
        }
        
        if (rightBranchCursor != NULL) {
            // append to right branch
            rightBranchCursor->sideBranch = CreatePathSegment(RandomContents(gem, spyglass));
            rightBranchCursor = rightBranchCursor->sideBranch;
        }
        
        if (leftBranchCursor && rightBranchCursor) {
            // if we're branched right now, maybe merge.
            if (rand() % 10 < 3) {
                rightBranchCursor->mainRoad = rightBranchCursor;
                rightBranchCursor = NULL;
            }
        } else {
            // if we're not branched right now, maybe split.
            if (rand() % 10 < 3) {
                rightBranchCursor = leftBranchCursor;
            }
        }
    }
    
    return home;
    
}

@end
