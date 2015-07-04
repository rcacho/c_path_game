//
//  InputHandler.h
//  pointer-tasks
//
//
//
//
//  Created by ricardo antonio cacho on 2015-07-04.
//  Copyright (c) 2015 rcacho. All rights reserved.
//

#import <Foundation/Foundation.h>



//incharge of parsing user inputs
// the inputs should be passed to the controller which is
// what decided what happens with the parsed results
@interface InputHandler : NSObject

-(void)run;

-(void)handleResponse;

@end
