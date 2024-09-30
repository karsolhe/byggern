void joystick_test();

int joystick_pos();

enum Direction joystick_dir();

int sliders_pos();

enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NEUTRAL
};