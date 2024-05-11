#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>

#include "file.h"
#include "municipio.h"
#include "hash_table.h"
#include "ui.h"

int main() {

    uint32_t operation;
    uint32_t size_json;
    json_error_t error;
    json_t *root = NULL;
    Municipio **municipios = NULL;
    Hashtable *hashTableMunicipios = NULL;

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
    
    do {
        
        printf("\n\n");
        operation = mainMenu();

        clear();

        switch (operation) {

            case UI_CONSULT:

                int32_t codigo_ibge = consultation();

                if (codigo_ibge == UI_ERROR) {

                    printf("Você informou um código IBGE inválido!");
                    break;

                }

                Municipio *municipio = getValueByKey(hashTableMunicipios, (uint32_t)codigo_ibge);

                if (municipio == NULL) {

                    printf("Você informou um código IBGE de uma cidade que não existe na tabela!");
                    break;

                }

                printMunicipio(municipio);

                break;
            
            case UI_ERROR:

                printf("Você selecionou uma opção que não existe no menu!");
                break;
        }

    } while (operation != UI_EXIT);

    destroyHashTable(hashTableMunicipios);
    
    return EXIT_SUCCESS;
}
