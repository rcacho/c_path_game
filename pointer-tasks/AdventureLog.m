//
//  AdventureLog.m
//  pointer-tasks
//
//  Created by ricardo antonio cacho on 2015-07-04.
//  Copyright (c) 2015 rcacho. All rights reserved.
//

#import "AdventureLog.h"

@implementation AdventureLog

-(void)playerVictory {
    
    NSLog(@"Congratulations!!!!!!\n Despite All Odds You Have Made It Through!");
    
}

-(void)gameOver {
    NSLog(@"GGGGGAAAAAMMMMMMMEEEEEE OOOOOOVVVVVVEEEEEERRRRRRRRRR");
}




-(void) printDamageTaken {

    NSLog(@"A Monster has attacked you!!\n");
}

-(void) printTreasureFound {
    NSLog(@"You have found some treasure!\n You are closer to completing you goal!\n");
}

-(void) printGemProtection {
    NSLog(@"Your Gem protected you from a monster attack!\n You escaped unscathed!\n");
}

-(void)printGemFound
{
    NSLog(@"You found a strange glowing gem!\n You think it could be useful...\n");
}

-(void) printSpyglassFound {
    
   NSLog(@"You found what appears to be an antique spyglass! Use it to spot danger ahead!");

}

@end
