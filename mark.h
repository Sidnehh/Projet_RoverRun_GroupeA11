//
// Created by Sidney (Ingénieur) on 25/11/2024.
//
#ifndef UNTITLED1_MARK_H
#define UNTITLED1_MARK_H
#include "tree.h"
#include "map.h"
#include "moves.h"
#include "stack.h"

t_localisation ExecutePhase(t_localisation start_pos, t_map map, int nb_movements);
void MarcFullTravel(t_localisation start_pos, t_map map);

#endif //UNTITLED1_MARK_H
