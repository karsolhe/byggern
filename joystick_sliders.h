
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
    int x;
    int y;
}pos_t;

typedef struct sliders_t{
    int left;
    int right;
} sliders_t;

typedef struct touch_buttons{
    int left;
    int right;
} touch_buttons;


void joystick_calibrate(joy_cal_pos *cal_pos);

enum Direction joystick_dir(joy_cal_pos cal_pos);

uint8_t joystick_button();

touch_buttons touch_button();

uint8_t left_touch_button();

uint8_t right_touch_button();

sliders_t sliders_pos();

sliders_t sliders_percent();

pos_t joystick_pos(joy_cal_pos cal_pos);

pos_t joystick_percent(joy_cal_pos cal_pos);