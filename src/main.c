#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>

#include "file.h"
#include "municipio.h"

int main() {

    char * jsonString = readFile("municipios.min.json");

    if (jsonString == NULL) {
        printf("Ocooreu um erro ao ler o municipios.min.json\n");
        return EXIT_FAILURE;
    }

    json_error_t error;
    json_t *root = json_loads(jsonString, 0, &error);
    free(jsonString); 

    if (root == NULL) {
        printf("Erro ao fazer o parse do JSON: %s\n", error.text);
        return EXIT_FAILURE;
    }

    Municipio *municipio = createMunicipioFromJson(json_array_get(root, 0));

    printMunicipio(municipio);

    json_decref(root);
    
    return EXIT_SUCCESS;
}
