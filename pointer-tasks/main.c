//
//  main.c
//  AdventureGame

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

typedef enum PathSegmentContents {
    PathSegmentContentsTreasure,
    PathSegmentContentsMonster,
    PathSegmentContentsNone,
} PathSegmentContents;

typedef struct PathSegment {
    PathSegmentContents contents;
    struct PathSegment *mainRoad;
    struct PathSegment *sideBranch;
} PathSegment;

typedef struct Player {
    int health;
    int wealth;
    int distance_travelled;
    PathSegment *currentLocation;
} Player;

typedef enum Direction {
    Forward,
    Turn
} Direction;

#pragma mark - Game Path Creation

PathSegment *CreatePathSegment(PathSegmentContents contents) {
    PathSegment *path = malloc(sizeof(PathSegment));
    path->contents = contents;
    path->mainRoad = NULL;
    path->sideBranch = NULL;
    return path;
}

PathSegmentContents RandomContents() {
    int roll = rand() % 10;
    if (roll == 0) return PathSegmentContentsMonster;
    if (roll < 3) return PathSegmentContentsTreasure;
    return PathSegmentContentsNone;
}

PathSegment *GenerateAdventure() {
    srand((int)time(NULL));
    
    PathSegment *home = CreatePathSegment(PathSegmentContentsNone);
    
    PathSegment *leftBranchCursor = home; // primary
    PathSegment *rightBranchCursor = NULL;
    
    for (int i = 0; i < 100; i++) {
        
        if (leftBranchCursor != NULL) {
            // append to left branch
            leftBranchCursor->mainRoad = CreatePathSegment(RandomContents());
            leftBranchCursor = leftBranchCursor->mainRoad;
        }
        
        if (rightBranchCursor != NULL) {
            // append to right branch
            rightBranchCursor->sideBranch = CreatePathSegment(RandomContents());
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

void PrintPathSegments(PathSegment *main, PathSegment *side) {
    if (!main) return;
    
    if (main->mainRoad && main->sideBranch) {
        printf("|\\");
    } else {
        if (main->mainRoad) {
            printf("|");
        }
        
        if (side) {
            if (side->sideBranch) {
                printf(" |");
            } else {
                printf("/");
            }
        }
    }
}

void PrintPath(PathSegment *pathStart) {
    
    PathSegment *mainPath = pathStart->mainRoad;
    PathSegment *sidePath = pathStart->sideBranch;
    
    while (mainPath->mainRoad != NULL) {
        PrintPathSegments(mainPath, sidePath);
        
        printf("\n");
        mainPath = mainPath->mainRoad;
        
        if (mainPath->sideBranch) {
            sidePath = mainPath->sideBranch;
        } else if (sidePath) {
            sidePath = sidePath->sideBranch;
        }
    }
}

void FreeAllPathSegments(PathSegment *segment) {
    // properly deallocate all segments along the path
    FreePathHelper(segment->mainRoad);
    FreePathHelper(segment->sideBranch);

    free(segment);
}

void FreePathHelper(PathSegment *segment) {
    if (segment != NULL)
    {
        FreeAllPathSegments(segment);
    }
}

void PlayerDistance(Player *player)
{
    printf("You have managed to travel %d miles from home!\n", player->distance_travelled);
}

void PlayerOptions(Player *player)
{
    PathSegment *path = player->currentLocation;
    if (path->mainRoad && path->sideBranch) {
        printf("You are at a crossroads!\n What decision will you make?\n");
    } else if (path->mainRoad) {
        printf("The only way forward is straight a head.\n");
    } else if (path->sideBranch) {
        printf("The main road is blocked. You will have to take the side road.\n");
    } else {
        printf("It seems there is nowhere to go from here...\n");
    }
}

void PlayerWealth(Player *player)
{
    printf("You have managed to gather %d pieces of treasure!\n", player->wealth);
    printf("Only %d more to go to win the game!\n", 100 - player->wealth);
}

void PlayerHealth(Player *player)
{
    if (player->health > 80) {
        printf("Your health is at %d.\n", player->health);
    } else if (player->health > 60) {
        printf("Your health is at %d. Keep going!\n", player->health);
    } else if (player->health > 40) {
        printf("Your health is at %d! Start making more cautious decisions.\n", player->health);
    } else if (player->health < 20) {
        printf("Your current health is at %d! Be careful!\n", player->health);
    }
    
}
void PlayerStatus(Player* player)
{
    PlayerDistance(player);
    PlayerWealth(player);
    PlayerHealth(player);
    PlayerOptions(player);

}

void MoveForward(Player *player)
{
    PathSegment *path = player->currentLocation;
    
    if (path->mainRoad) {
        player->currentLocation = path->mainRoad;
        player->distance_travelled = player->distance_travelled + 1;
    } else if (path->sideBranch) {
        printf("There is no path ahead. You will have to turn.\n");
    } else {
        printf("There does not seem to be anywhere to go.\n");
    }
}

void MoveTurn(Player *player)
{
    PathSegment *path = player->currentLocation;
    
    if (path->sideBranch) {
        player->currentLocation = path->sideBranch;
        player->distance_travelled = player->distance_travelled + 1;
    } else if (path->mainRoad) {
        printf("There is no path in that direction. You will have to go ahead.\n");
    } else {
        printf("There does not seem to be anywhere to go.\n");
    }
}


void PlayerMove(Player *player, Direction direction)
{
    if (direction == Forward) {
        MoveForward(player);
    } else if (direction == Turn) {
        MoveTurn(player);
    } else {
        printf("The given direction was not understood.\n");
    }
}

Player *constructPlayer(PathSegment *path)
{
    Player *player = malloc(sizeof(Player));

    player->currentLocation = path;
    player->distance_travelled = 0;
    player->wealth = 0;
    player->health = 100;

    return player;
}

bool ForwardPhrase(char input[])
{
    if (strstr(input, "ahead")) {
        return true;
    } else if (strstr(input, "forward")) {
        return true;
    } else if (strstr(input, "straight")) {
        return true;
    } else {
        return false;
    }
}

int TurnPhrase(char input[])
{
    if (strstr(input, "turn")) {
        return true;
    } else if (strstr(input, "left")) {
        return true;
    } else if (strstr(input, "right")) {
        return true;
    } else if (strstr(input, "side")) {
        return true;
    } else {
        return false;
    }
}

Direction parseInput(char input[])
{
    if (ForwardPhrase(input)) {
        return Forward;
    } else if (TurnPhrase(input)) {
        return Turn;
    } else {
        return -1;
    }
}

void handleResponse(char input[], Player *player)
{
    Direction direction = parseInput(input);
    
    PlayerMove(player, direction);
    
}

int main(int argc, const char * argv[]) {
    
    PathSegment *path = GenerateAdventure();
    PrintPath(path);
    
    bool playing = true;
    
    char input[300];
    
    Player *player = constructPlayer(path);

    while (playing) {
        // init player
        PlayerStatus(player);

        fgets(input, 300, stdin);
        strtok(input, "\n"); // trim newline at end of input
        handleResponse(input, player);

        printf("input was %s\n", input);
    }
    
    FreeAllPathSegments(path);
    
    return 0;
}
