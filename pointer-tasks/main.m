//
//  main.m
//  adventure game
//
//  Created by ricardo antonio cacho on 2015-07-04.
//  Copyright (c) 2015 rcacho. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameController.h"
#import "AdventureGenerator.h"


int main(int argc, const char * argv[])
{
    @autoreleasepool {
        
        GameController *game = [[GameController alloc] init]
        
        [game start];
        
        
        AdventureGenerator *generator = [[AdventureGenerator alloc] init];
        
        PrintPath(path);
        
        bool playing = true;
        
       
        
        Player *player = constructPlayer(path);

        
    }
    return 0;
}

