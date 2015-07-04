//
//  GameController.h
//  pointer-tasks
//
//  Created by ricardo antonio cacho on 2015-07-04.
//  Copyright (c) 2015 rcacho. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AdventureGenerator.h"
#import "Player.h"
#import "InputHandler.h"
#import "AdventureLog.h"

@interface GameController : NSObject

@property AdventureGenerator *generator;

@property Player *player;

@property InputHandler *inputHandler;

@property AdventureLog *log;

@property BOOL gameRunning;



-(instancetype)init;

-(void)start;

-(void)runLoop;

-(void)gameStatus;


@end
