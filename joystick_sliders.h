#include <stdint.h>
#include <avr/io.h>

typedef enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NEUTRAL
}Direction;

typedef struct {
    int8_t x_offset;
    int8_t y_offset;
} joy_cal_pos;

typedef struct pos_t{
    uint16_t x;
    uint16_t y;
}pos_t;

typedef struct sliders_t{
    int left;
    int right;
} sliders_t;

typedef struct touch_buttons{
    int left;
    int right;
} touch_buttons;

enum Direction joystick_dir();

uint8_t joystick_button();

touch_buttons touch_button();

sliders_t sliders_pos();

sliders_t sliders_percent();

pos_t joystick_pos();

pos_t joystick_percent();