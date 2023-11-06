//
// Created by alexdavid on 02.11.2023.
//

#include "util.h"
#include <stdlib.h>
#include <stdio.h>

char *floatToString(float value, int precision) {
    char *str = (char *) malloc(sizeof(char) * 20);
    sprintf(str, "%.*f", precision, value);
    return str;
}