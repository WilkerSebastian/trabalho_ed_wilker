#pragma once

#include "municipio.h"

#define HASH_ERROR 0
#define HASH_OK 1

typedef struct nodeHash {
    uint32_t key;
    Municipio* value;
} NodeHash;

typedef struct {
    NodeHash **table;
    uint32_t max;
    uint32_t length;
} Hashtable;

Hashtable *createHashTableMunicipio(Municipio **municipios, uint32_t n, uint32_t MAX_ZISE);

NodeHash *createNodeHash(uint32_t key, Municipio* value);

uint8_t setKeyValue(Hashtable *hashTable, uint32_t key, Municipio* value);

Municipio *getValueByKey(Hashtable *hashTable, uint32_t key);

uint32_t firstIndexHash(uint64_t hash, uint32_t size);

uint32_t secondIndexHash(uint64_t preHash, uint64_t hash, uint32_t index, uint32_t size);

uint64_t hashSDBM(uint32_t key);

uint64_t hashDJB2(uint32_t key);

void destroyHashTable(Hashtable *hashTable);