//
//  Player.h
//  pointer-tasks
//
//  Created by ricardo antonio cacho on 2015-07-04.
//  Copyright (c) 2015 rcacho. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PathSegment.h"
#import "PathSegmentEquipableItem.h"

@interface Player : NSObject

@property NSString *name;

@property PathSegment *currentLocation;

@property NSInteger health;

@property NSInteger wealth;

// array of PathSegmentEquipableItems
@property NSArray* inventory;



-(instancetype)createPlayer;

-(void)getStatus;

-(void)getName;

@end
