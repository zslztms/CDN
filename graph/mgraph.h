//
// Created by wxxxx on 2020/12/1.
//

#ifndef GRAPH_MGRAPH_H
#define GRAPH_MGRAPH_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>//strcmp
#include<math.h>
#define maxvertices 100
#define maxweight 32767
typedef int weight;
typedef struct{
    int vexnum;
    weight edge[maxvertices][maxvertices];
}mgraph;
extern void create(mgraph &G);
extern void shortpath(mgraph &G);
#endif //GRAPH_MGRAPH_H
