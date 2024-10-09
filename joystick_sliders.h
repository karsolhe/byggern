
typedef enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NEUTRAL
}Direction;

typedef struct pos_t{
    int x;
    int y;
}pos_t;

typedef struct sliders_t{
    int left;
    int right;
} sliders_t;

void joystick_calibrate();

enum Direction joystick_dir();

uint8_t joystick_button();

sliders_t sliders_pos();

sliders_t sliders_percent();

pos_t joystick_pos(void);

pos_t joystick_percent();