#ifndef TYPES_H
#define TYPES_H

#include "defines.h"
#include <asm/types.h>
#include <stdint.h>
#include <stdbool.h>

#define TILE_TREE   04
#define TILE_BRIDGE 14
#define TILE_WATER  15
#define TILE_HOUSE  16
#define TILE_FOG    23

#define TILE_ICON_START 26 // 26-28
#define TILE_ICON_A     29
#define TILE_ICON_B     30
#define TILE_ICON_LEFT  31
#define TILE_ICON_UP    32
#define TILE_ICON_RIGHT 33
#define TILE_ICON_DOWN  34
#define TILE_ARROW      35

#define TILE_ICON_YOU   40 // 40-41
#define TILE_ICON_CPU   42 // 42-43

#define MAX_TEAM_SIZE 4


typedef enum {
    UNIT_TYPE_BRAWN,
    UNIT_TYPE_ARCHER,
    UNIT_TYPE_HEALER,
    UNIT_TYPE_BOAT,
} type_of_unit;


typedef enum {
    DIRECTION_LEFT,
    DIRECTION_RIGHT,
    DIRECTION_UP,
    DIRECTION_DOWN
} direction_t;


typedef enum {
    AI_TARGET_NONE, // assign to an AI unit so it can choose a new strategy
    AI_TARGET_NEAR, // attack nearest enemy
    AI_TARGET_ATK, // attacks the enemy with lowest HP
    AI_TARGET_RUN, // runs away from an enemy
    AI_TARGET_HEAL, // (unimplemented) healer unit move towards weakest unit
    AI_TARGET_HEALER // cause a unit to move towards the healer
} ai_strat_t;


typedef struct {
    int8_t health;
    int8_t maxHealth;
    int8_t damagePoints;
    uint8_t movePoints;
    uint8_t damageRadius;
} stat_t;

typedef struct {
    uint8_t row, column;
    bool isDead;
    bool hasMoved;
    bool hasAttacked;
    uint8_t spriteNumber;
    uint8_t tile;
    ai_strat_t strategy;
    type_of_unit type;
    stat_t stats;
    void *heldUnit;   // pointer to the other unit that this unit is holding, NULL if none
    bool isHeld;        // true if this unit is being carried by another
    // void (*idk);
} unit_t;


typedef struct {
    uint8_t width, height;
    uint8_t size; // width * height
    uint8_t *data;
} map_t;


typedef enum {
    CONTROLLER_PLAYER,
    CONTROLLER_COMPUTER,
    CONTROLLER_LINK
} control_t;


typedef struct {
    uint8_t size; // number of units in the following array
    unit_t **units; // pointer to array of units
    control_t control; // type of player for this team
} team_t;



// structure that is used for each match
typedef struct {
    team_t *teams[3];
    uint8_t numTeams;
} match_t;


// position (x, y)
typedef struct {
    uint8_t x, y;
} position_t;

/**
 * When `lastPos` is (0, 0), then that is equivalent to NULL
 */
typedef struct {
    position_t curPos;
    void *lastEntry; // pointer to queue_t
} queue_t;


#endif