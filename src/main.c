#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>

int main() {

    FILE *arquivo = fopen("municipios.min.json", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo municipios.json\n");
        return EXIT_FAILURE;
    }

    fseek(arquivo, 0, SEEK_END);
    size_t tamanho = ftell(arquivo);
    rewind(arquivo);

    char *conteudo = (char *)malloc(tamanho + 1);
    fread(conteudo, sizeof(char), tamanho, arquivo);
    conteudo[tamanho] = '\0';

    fclose(arquivo);

    json_error_t erro;
    json_t *root = json_loads(conteudo, 0, &erro);
    free(conteudo); 

    if (root == NULL) {
        printf("Erro ao fazer o parse do JSON: %s\n", erro.text);
        return EXIT_FAILURE;
    }

    if (!json_is_array(root)) {
        printf("O JSON não é um array\n");
        json_decref(root);
        return EXIT_FAILURE;
    }

    size_t num_elementos = json_array_size(root);
    for (size_t i = 0; i < num_elementos; i++) {
        json_t *item = json_array_get(root, i);
        if (item != NULL && json_is_object(item)) {
            json_t *codigo_ibge = json_object_get(item, "codigo_ibge");
            json_t *nome = json_object_get(item, "nome");
            json_t *latitude = json_object_get(item, "latitude");
            json_t *longitude = json_object_get(item, "longitude");
            json_t *capital = json_object_get(item, "capital");
            json_t *codigo_uf = json_object_get(item, "codigo_uf");
            json_t *siafi_id = json_object_get(item, "siafi_id");
            json_t *ddd = json_object_get(item, "ddd");
            json_t *fuso_horario = json_object_get(item, "fuso_horario");

            if (codigo_ibge && nome && latitude && longitude && capital && codigo_uf && siafi_id && ddd && fuso_horario) {
                printf("Código IBGE: %lld\n", json_integer_value(codigo_ibge));
                printf("Nome: %s\n", json_string_value(nome));
                printf("Latitude: %f\n", json_real_value(latitude));
                printf("Longitude: %f\n", json_real_value(longitude));
                printf("Capital: %d\n", json_boolean_value(capital));
                printf("Código UF: %lld\n", json_integer_value(codigo_uf));
                printf("Siafi ID: %lld\n", json_integer_value(siafi_id));
                printf("DDD: %lld\n", json_integer_value(ddd));
                printf("Fuso Horário: %s\n", json_string_value(fuso_horario));
                printf("\n");
            } else {
                printf("Alguma chave não foi encontrada no objeto.\n");
            }
        }
    }

    json_decref(root);
    
    return EXIT_SUCCESS;
}
