#include "kdtree.h"

#include <math.h>

KDnode *createKDNode(Municipio *value) {

    KDnode *node = (KDnode*)malloc(sizeof(KDnode));

    if (node == NULL)
        return NULL;

    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;

}

KDnode *insertMunicipioInKD(KDnode *root, Municipio *value, int deep) {

    if (root == NULL) {

        KDnode *node = createKDNode(value);
        return node;

    }

    int nextDeep = deep + 1;

    if (deep % 2 == 0) {

        if (value->longitude < root->value->longitude)  {

            root->left = insertMunicipioInKD(root->left, value, nextDeep);
            return root;

        }
            
        root->right = insertMunicipioInKD(root->right, value, nextDeep);
        return root;
        
    } 
    
    if (value->latitude < root->value->latitude)  {

        root->left = insertMunicipioInKD(root->left, value, nextDeep);
        return root;

    }

    root->right = insertMunicipioInKD(root->right, value, nextDeep);
    return root;

}
 
void searchNearestMunicipios(KDnode *root, Municipio *target, int n, KDnode **nearestMunicipios, double distances[], int deep) {

    if (root == NULL)
        return;

    double distance = distanceMunicipios(root->value, target);

    for (int i = 0; i < n; i++) {

        if (distance < distances[i]) {

            for (int j = n - 1; j > i; j--) {

                distances[j] = distances[j - 1];
                *(nearestMunicipios + j) = *(nearestMunicipios + (j - 1));

            }

            distances[i] = distance;
            *(nearestMunicipios + i) = root;
            break;

        }

    }

    int nextDeep = deep + 1;

    if (deep % 2 == 0) {

        if (target->longitude < root->value->longitude) {

            searchNearestMunicipios(root->left, target, n, nearestMunicipios, distances, nextDeep);

        } else {
            
            searchNearestMunicipios(root->right, target, n, nearestMunicipios, distances, nextDeep);

        }

        if (target->longitude - root->value->longitude < distances[n - 1]) {


            if (target->latitude >= root->value->longitude) {

                searchNearestMunicipios(root->left, target, n, nearestMunicipios, distances, nextDeep);
                return;

            }

            searchNearestMunicipios(root->right, target, n, nearestMunicipios, distances, nextDeep);

        }
        
    } else {

        if (target->latitude < root->value->latitude)  {

            searchNearestMunicipios(root->left, target, n, nearestMunicipios, distances, nextDeep);

        } else {

            searchNearestMunicipios(root->right, target, n, nearestMunicipios, distances, nextDeep);

        }

        if (target->latitude - root->value->latitude < distances[n - 1]) {


            if (target->latitude >= root->value->latitude) {

                searchNearestMunicipios(root->left, target, n, nearestMunicipios, distances, nextDeep);
                return;

            }

            searchNearestMunicipios(root->right, target, n, nearestMunicipios, distances, nextDeep);

        }
 
    }

}

void findNearestMunicipios(KDnode *root, Municipio *target, int n, KDnode **nearestMunicipios) {

    if (root == NULL)
        return;

    double distances[n];

    for (int i = 0; i < n; i++) 
        distances[i] = __DBL_MAX__; // dando o maior valor possivel para distancias

    *nearestMunicipios = NULL;

    searchNearestMunicipios(root, target, n, nearestMunicipios, distances, 0);

}

void printKD(KDnode* root, int deep) {

    if (root != NULL) {
        
        printKD(root->left, deep + 1);
        printf("%d\n", root->value->codigo_ibge);
        printKD(root->right, deep + 1);

    }

}

void destroyKDTree(KDnode *root) {

    if (root == NULL)
        return;
    
    destroyKDTree(root->left);
    destroyKDTree(root->right);

    free(root);

}