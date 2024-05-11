#pragma once

#define UI_ERROR -1
#define UI_CONSULT 1
#define UI_EXIT 0

#include <stdint.h>

int8_t mainMenu();

int32_t consultation();

char *input(const char *msg);

void clear();