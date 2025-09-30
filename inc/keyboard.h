#pragma once

#include <stdlib.h>
#include "scan.h"
#include "serial.h"
#include "tusb.h"

bool keyboard_parse( uint8_t keycodes[6], uint8_t *modifier );
