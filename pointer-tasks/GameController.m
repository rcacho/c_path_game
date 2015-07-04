//
//  GameController.m
//  pointer-tasks
//
//  Created by ricardo antonio cacho on 2015-07-04.
//  Copyright (c) 2015 rcacho. All rights reserved.
//

#import "GameController.h"


@implementation GameController

-(instancetype)init {
    self = [super init];
    
    if (self) {
        self.generator = [[AdventureGenerator alloc] init];
    }
    return self;
}

-(void)start {
    [self.generator createAdventure];
    [self.player createPlayer];
    [self setGameRunning:YES];
    [self runLoop];
}

-(void)runLoop {
    
    while (self.gameRunning) {
        Player *player = self.player;
        [player getStatus];
        

        // see where we are in the game
        // if player is dead or has won change gameRunning
        [self gameStatus];
    }
}

-(void)gameStatus {
    
    [self setGameRunning:NO];
}

@end
