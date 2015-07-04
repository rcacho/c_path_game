//
//  InputHandler.m
//  pointer-tasks
//
//  Created by ricardo antonio cacho on 2015-07-04.
//  Copyright (c) 2015 rcacho. All rights reserved.
//

#import "InputHandler.h"

@implementation InputHandler

-(void)run {
     char input[300];
    fgets(input, 300, stdin);
    strtok(input, "\n"); // trim newline at end of input
    
    handleResponse(input, player);
    
}

@end
