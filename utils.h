#ifndef __UTILS_H__
#define __UTILS_H__
#include "t_cell.h"
#include "hasse.h"


void CreateMermaidGraph(list_adjac* listeAdjacence);
void CreateMermaidPartition(t_partition * partition, t_hasse * hasse);

#endif