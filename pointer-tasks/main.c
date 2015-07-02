//
//  main.c
//  AdventureGame

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


typedef enum PathSegmentContents {
    PathSegmentContentsTreasure = 1,
    PathSegmentContentsMonster = 2,
    PathSegmentContentsNone = 0,
    PathSegmentContentsGem = 3,
    PathSegmentContentsSpyglass = 4
} PathSegmentContents;

typedef enum ItemType {
    Gem,
    Spyglass
}

typedef struct PathSegment {
    PathSegmentContents contents;
    struct PathSegment *mainRoad;
    struct PathSegment *sideBranch;
} PathSegment;

typedef struct Item {
   int health;
} Item;

typedef struct Player {
    char *name;
    int health;
    int wealth;
    int distance_travelled;
    Item *gem;
    Item *spyglass;
    PathSegment *currentLocation;
} Player;

typedef enum Direction {
    Forward,
    Turn
} Direction;

#pragma mark - Game Path Creation

Item* constructItem()
{
    Item *item = malloc(sizeof(Item));
    item->health = 10;
    return item;
}

void GemStatus(Item *gem)
{
    gem->health = gem->health - 1;
    if (gem->health == 0) {
        printf(" \nThe gem appears to have shattered!\n \n");
    }
}

void SpyglassStatus(Item *spyglass)
{
    spyglass->health = spyglass->health - 2;

    if (spyglass->health == 0) {
        printf("\nThe spyglass appears to have broken!\n \n");
    }
}

bool parseYN() {
    char response[35];
    fgets(response, 35, stdin);
    if (strstr(response, "yes")) {
        return true;
    } else {
        return false;
    }
}

int InspectAhead(PathSegment *segment, PathSegmentContents contents, int miles)
{
    PathSegment *nextsegment;
    if (segment->mainRoad != NULL) {
        nextsegment = segment->mainRoad;
    } else if (segment->sideBranch != NULL) {
        nextsegment = segment->sideBranch;
    } else {
        printf("You think you see the end of your journey!");
        return 0;
    }

    if (miles == 0) {
        return 0;
    } else if (segment->contents == contents) {
        return 1 + InspectAhead(nextsegment, contents, miles - 1);
    } else {
        return 0 + InspectAhead(nextsegment, contents, miles - 1);
    }
}

int InspectForMonstersAhead(PathSegment *segment) {
    return InspectAhead(segment, PathSegmentContentsMonster, 5);
}

int InspectForTreasuresAhead(PathSegment *segment) {
    return InspectAhead(segment, PathSegmentContentsTreasure, 5);
}

void UseSpyglass(Player *player)
{
    PathSegment *path = player->currentLocation;
    PathSegment *main = path->mainRoad;
    PathSegment *side = path->sideBranch;

    printf("You can see five miles ahead....\n");

    int monsters_in_main = InspectForMonstersAhead(main);
    int treasure_in_main = InspectForTreasureAhead(main);
    int monsters_in_side = InspectForMonstersAhead(side);
    int treasure_in_side = InspectForTreasuresAhead(side);


    printf("In the main road...\n");
    printf("You see %d monsters!\n You see %d treasures!\n", monsters_in_main, treasure_in_main);
    printf("In the side road...\n");
    printf("You see %d monsters!\n You see %d treasures!\n", monsters_in_side, treasure_in_side);
}

void SpyglassOpportunity(Player *player)
{
    printf("\n Hmmm.. This maybe would be a good chance to use the spyglass??\n \n");
    bool answer = parseYN();

    if (answer) {
        UseSpyglass(player);
        SpyglassStatus(player->spyglass);
    } else {
        printf("You decided against using the spyglass.\n");
    }
}

PathSegment *CreatePathSegment(PathSegmentContents contents) {
    PathSegment *path = malloc(sizeof(PathSegment));
    path->contents = contents;
    path->mainRoad = NULL;
    path->sideBranch = NULL;
    return path;
}

PathSegmentContents RandomContents(Item *gem, Item *spyglass) {
    int roll = rand() % 100;
    // 1 in 100 chance that a location will have the gem
    // if the gem has already been taken by a segment reroll
    if (roll <= 1) {
      if (gem != NULL) {
          gem = NULL;
          return PathSegmentContentsGem;
      } else {
          return RandomContents(gem, spyglass);
      }
    }
    if (roll > 30 && roll < 36) {
        if (spyglass != NULL) {
            spyglass = NULL;
            return PathSegmentContentsSpyglass;
        } else {
            return RandomContents(gem, spyglass);
        }
    }
    if (roll > 10 && roll < 20) return PathSegmentContentsMonster;
    if (roll > 20 && roll < 30) return PathSegmentContentsTreasure;
    return PathSegmentContentsNone;
}

PathSegment *GenerateAdventure() {
    srand((int)time(NULL));

    PathSegment *home = CreatePathSegment(PathSegmentContentsNone);
    Item *gem = constructItem();
    Item *spyglass = constructItem();

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

void printu(Player *player)
{
    printf("%s ", player->name);

}
void FreePathHelper(PathSegment *segment);

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
        SpyglassOpportunity(player);
    } else if (path->mainRoad) {
        printf("The only way forward is straight ahead.\n");
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
        printf("Your health is at %d. Keep going %s!\n", player->health, player->name);
    } else if (player->health > 40) {
        printf("Your health is at %d! Start making more cautious decisions.\n", player->health);
    } else if (player->health > 20) {
        printf("Your health is at %d! Be careful %s!\n", player->name);
    } else if (player->health < 20) {
        printf("Your current health is at %d! Your outlook is grim %s!\n", player->health, player->name);
    }

}

void printDamageTaken()
{
    printf("A Monster has attacked you!!\n");
}

void printTreasureFound()
{
    printf("You have found some treasure!\n You are closer to completing you goal!\n");
}

void printGemProtection()
{
    printf("Your Gem protected you from a monster attack!\n You escaped unscathed!\n");
}

void printGemFound()
{
    printf("You found a strange glowing gem!\n You think it could be useful...\n");
}

void printSpyglassFound()
{
    printf("You found what appears to be an antique spyglass! Use it to spot danger ahead!");
}

void PlayerTakesDamage(Player *player)
{
    Item *gem = player->gem;
    if (gem == NULL) {
        printDamageTaken();
        player->health = player->health - 5;
    } else if (gem->health == 0) {
        printDamageTaken();
        player->health = player->health - 5;
    } else {
        printGemProtection();
    }

}

void NewStatus(Player *player)
{
    PathSegment *location = player->currentLocation;
    PathSegmentContents contents = location->contents;
    Item *gem = player->gem;

    switch (contents) {
        case 1:
            printTreasureFound();
            player->wealth = player->wealth + 5;
            break;
        case 2:
            PlayerTakesDamage(player);
            break;
        case 3:
            printGemFound();
            player->gem = constructItem();
            break;
        case 4:
            printSpyglassFound();
            player->spyglass = constructItem();
            break;
        default:
            break;
    }

    if (gem != NULL && gem->health != 0) {
        GemStatus(player->gem);
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
        NewStatus(player);
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
        NewStatus(player);
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
void GetPlayerName(char *name)
{
    printf("Tell me, what is your name?\n");
    fgets(name, 35, stdin);
    char *n;
    //n = strtok(name, '\n');
}

Player *constructPlayer(PathSegment *path)
{
    Player *player = malloc(sizeof(Player));
    char name[35];
    GetPlayerName(name);

    player->name = name;
    printf("Your name is %s? Okay.", player->name);

    player->currentLocation = path;
    player->distance_travelled = 0;
    player->wealth = 0;
    player->health = 100;
    player->gem = NULL;

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

void printVictory()
{
    printf("YOU HAVE WON!!!!\n");
}

void printGameOver()
{
    printf("GAME OVER!!\n");
}

bool GameStatus(Player *player)
{
    if (player->wealth == 100) {
        printVictory();
        return true;
    } else if (player->health == 0) {
        printGameOver();
        return true;
    }
    return false;
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

        if (GameStatus(player)) {
            playing = false;
        }
    }

    //FreeAllPathSegments(path);

    return 0;
}
