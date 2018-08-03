#ifndef _ACTIONS_H_
#define _ACTIONS_H_

typedef enum{
    _move,   //move to point
    _stop,   //when mouse left key goes up
    _decay   //decay to move faster
} _ACTIONS;

typedef struct{
    float x;
    float y;
} VECTOR;

typedef struct{
    _ACTIONS ac_ind;//index of action from enum in actions.h
    VECTOR vec;//direction of action
} _action;

#endif