#pragma once

#define UI_ERROR -1
#define UI_CONSULT 1
#define UI_PROXIMITY 2
#define UI_EXIT 0

#include <stdint.h>

int8_t mainMenu();

int32_t consultation();

int32_t questN(const char *nome, int max);

void clear();