#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>

#include "file.h"
#include "municipio.h"
#include "ui.h"

int main() {

    uint32_t operation;
    json_error_t error;
    json_t *root;

    char * jsonString = readFile("municipios.min.json");

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

                break;
            
            case UI_ERROR:

                printf("Você selecionou uma opção que não existe no menu!");
                break;
        }

    } while (operation != UI_EXIT);

    json_decref(root);
    
    return EXIT_SUCCESS;
}
