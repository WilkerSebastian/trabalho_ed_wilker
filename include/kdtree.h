#pragma once

#include "municipio.h"

typedef struct kdnode {

    Municipio *value;
    struct kdnode *right;
    struct kdnode *left;

} KDnode;

KDnode *createKDNode(Municipio *value);

KDnode *insertMunicipioInKD(KDnode *root, Municipio *value, int deep);

void findNearestMunicipios(KDnode *root, Municipio *target, int n, KDnode **nearestMunicipios);

void printKD(KDnode* root, int deep);

void destroyKDTree(KDnode *root);