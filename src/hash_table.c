#include "hash_table.h"

Hashtable *createHashTableMunicipio(Municipio **municipios, uint32_t n, uint32_t MAX_ZISE) {

    Hashtable *hashTable = (Hashtable*)malloc(sizeof(Hashtable));

    hashTable->max = MAX_ZISE % 2 == 0 ? MAX_ZISE + 1 : MAX_ZISE;
    hashTable->length = 0;
    hashTable->table = (NodeHash**)calloc(hashTable->max, sizeof(NodeHash*));

    if (municipios == NULL)
        return hashTable;

    for (uint32_t i = 0; i < n; i++) {
        
        Municipio *municipio = *(municipios + i);

        uint8_t err = setKeyValue(hashTable, municipio->codigo_ibge, municipio);

        if (err == HASH_ERROR) {

            destroyHashTable(hashTable);
            return NULL;

        }

    }
    
    return hashTable;

}

NodeHash *createNodeHash(uint32_t key, Municipio* value) {

    NodeHash *node = (NodeHash*)malloc(sizeof(NodeHash));

    node->key = key;
    node->value = value;

    return node;

}

uint8_t setKeyValue(Hashtable *hashTable, uint32_t key, Municipio* value) {

    uint64_t hash = hashDJB2(key);

    uint32_t index = firstIndexHash(hash, hashTable->max);

    if (*(hashTable->table + index) == NULL) {

        NodeHash *node = createNodeHash(key, value); 

        if (node == NULL)
            return HASH_ERROR;

        *(hashTable->table + index) = node;
        hashTable->length++;

        return HASH_OK;

    } 

    uint64_t hash2 = hashSDBM(key);
    uint32_t iterations = 0;

    while (*(hashTable->table + index) != NULL && (*(hashTable->table + index))->key != key && hashTable->length + 1 < hashTable->max) {

        index = secondIndexHash(hash, hash2, iterations, hashTable->max);
        iterations++;

    }

    if (iterations == hashTable->max)
        return HASH_ERROR;

    if (*(hashTable->table + index) == NULL) {

        NodeHash *node = createNodeHash(key, value); 

        if (node == NULL)
            return HASH_ERROR;

        *(hashTable->table + index) = node;
        hashTable->length++;

        return HASH_OK;

    }

    return HASH_ERROR;

}

Municipio *getValueByKey(Hashtable *hashTable, uint32_t key) {

    uint64_t hash = hashDJB2(key);

    uint32_t index = firstIndexHash(hash, hashTable->max);

    if (*(hashTable->table + index) != NULL && (*(hashTable->table + index))->key == key) 
        return ((*(hashTable->table + index))->value);
    
    uint64_t hash2 = hashSDBM(key);
    uint32_t iterations = 0;

    while (*(hashTable->table + index) != NULL && (*(hashTable->table + index))->key != key && hashTable->length + 1 < hashTable->max) {
        index = secondIndexHash(hash, hash2, iterations, hashTable->max);
        iterations++;
    }

    
    if (*(hashTable->table + index) != NULL && (*(hashTable->table + index))->key == key) 
        return ((*(hashTable->table + index))->value);

    // caso tudo dei errado fazer busca linear, sim é uma gambiarra de ultima hora desculpa

    for (size_t i = 0; i < hashTable->length; i++)
        if ((*(hashTable->table + i))->key == key)
            return (*(hashTable->table + i))->value;
    
    return NULL; 

}

uint32_t firstIndexHash(uint64_t hash, uint32_t size) {

    return hash % size;

}

uint32_t secondIndexHash(uint64_t preHash, uint64_t hash, uint32_t index, uint32_t size) {

    return (preHash + index * hash) % size;

}   

uint64_t hashSDBM(uint32_t key) {

    uint64_t hash = 0;
    int c;

    for (c = key; c != 0; c >>= 8) 
        hash = c + (hash << 6) + (hash << 16) - hash;
    
    return hash;

}

uint64_t hashDJB2(uint32_t key) {

    uint64_t hash = 5381;
    hash = ((hash << 5) + hash) + key; 
    return hash;

}

void destroyHashTable(Hashtable *hashTable) {

    if (hashTable == NULL) 
        return;
    
    if (hashTable->table != NULL)
        free(hashTable->table);

    free(hashTable);

}