#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>

#include "file.h"
#include "municipio.h"
#include "hash_table.h"
#include "kdtree.h"
#include "ui.h"

int main() {

    uint32_t operation;
    uint32_t size_json;

    int32_t codigo_ibge = 0;
    int32_t n = 0;

    json_error_t error;
    json_t *root = NULL;

    Municipio **municipios = NULL;
    Municipio *municipio = NULL;

    Hashtable *hashTableMunicipios = NULL;

    KDnode *kdTreeMunicipios = NULL;
    KDnode *nearestMunicipios = NULL;

    char *jsonString = readFile("municipios.min.json");

    if (jsonString == NULL) {
        printf("Ocooreu um erro ao ler o municipios.min.json\n");
        return EXIT_FAILURE;
    }
    
    root = json_loads(jsonString, 0, &error);
    free(jsonString); 

    if (root == NULL) {
        printf("Erro ao fazer o parse do JSON: %s\n", error.text);
        return EXIT_FAILURE;
    }

    size_json = json_array_size(root);

    municipios = calloc(size_json, sizeof(Municipio*));

    for (size_t i = 0; i < size_json; i++) {

        json_t *json = json_array_get(root, i);

        *(municipios + i) = createMunicipioFromJson(json);

    }

    json_decref(root);

    hashTableMunicipios = createHashTableMunicipio(municipios, size_json, size_json);

    if (hashTableMunicipios == NULL) {

        printf("Erro ao criar tabela hash dos municipios!\n");
        return EXIT_FAILURE;

    }

    for (size_t i = 0; i < size_json; i++) 
        kdTreeMunicipios = insertMunicipioInKD(kdTreeMunicipios, *(municipios + i), 0);

    if (kdTreeMunicipios == NULL) {

        printf("Erro ao criar arvore K-D dos municipios!\n");
        return EXIT_FAILURE;

    }

    
    do {
        
        printf("\n\n");
        operation = mainMenu();

        clear();

        switch (operation) {

            case UI_CONSULT:

                codigo_ibge = consultation();

                if (codigo_ibge == UI_ERROR) {

                    printf("Você informou um código IBGE inválido!");
                    break;

                }

                municipio = getValueByKey(hashTableMunicipios, (uint32_t)codigo_ibge);

                if (municipio == NULL) {

                    printf("Você informou um código IBGE de uma cidade que não existe na tabela!\n");
                    break;

                }

                printMunicipio(municipio);

                break;
            case UI_PROXIMITY:

                codigo_ibge = consultation();

                if (codigo_ibge == UI_ERROR) {

                    printf("Você informou um código IBGE inválido!\n");
                    break;

                }

                municipio = getValueByKey(hashTableMunicipios, (uint32_t)codigo_ibge);

                if (municipio == NULL) {

                    printf("Você informou um código IBGE de uma cidade que não existe na tabela!\n");
                    break;

                }

                n = questN(municipio->nome, size_json - 2);

                if (n == UI_ERROR) {

                    printf("Você informou uma quantidade inválida de municipios!\n");
                    break;

                }

                nearestMunicipios = NULL;

                findNearestMunicipios(kdTreeMunicipios, municipio, n, &nearestMunicipios);

                if (nearestMunicipios == NULL) {

                    printf("Erro a buscar cidades proximas\n");
                    break;
                
                }

                printKD(nearestMunicipios, 0);

                destroyKDTree(nearestMunicipios);
            
                break;
            case UI_ERROR:

                printf("Você selecionou uma opção que não existe no menu!");
                break;
        }

    } while (operation != UI_EXIT);

    destroyHashTable(hashTableMunicipios);
    destroyKDTree(kdTreeMunicipios);

    for (size_t i = 0;i < size_json;i++)
        destroyMunicipio(*(municipios + i));

    free(municipio);
    
    return EXIT_SUCCESS;
}
