#pragma once

#define LED_PIN  17

#define COL0_PIN 20
#define COL1_PIN 22
#define COL2_PIN 26
#define COL3_PIN 27
#define COL4_PIN 28
#define COL5_PIN 29

#define ROW0_PIN 4
#define ROW1_PIN 5
#define ROW2_PIN 6
#define ROW3_PIN 7

#define WS2812_PIN  0
#define TRRS_PIN 1

#define OLED_SDA_PIN 2
#define OLED_SCL_PIN 3

#define MATRIX_COLS 6
#define MATRIX_ROWS 4

static const unsigned int MATRIX_SCAN_ROWS_PINS[MATRIX_ROWS] = { ROW0_PIN, ROW1_PIN, ROW2_PIN, ROW3_PIN };
static const unsigned int MATRIX_SCAN_COLS_PINS[MATRIX_COLS] = { COL0_PIN, COL1_PIN, COL2_PIN, COL3_PIN, COL4_PIN, COL5_PIN };

