#include <avr/io.h>

void OLED_init();

void OLED_reset();

void OLED_home();

void OLED_goto_line(uint8_t line);

void OLED_goto_column(uint8_t column);

void OLED_clear_line(uint8_t line);

void OLED_pos(uint8_t line, uint8_t column);

void OLED_write_data(char c);

void OLED_print_char(char* c);

void OLED_set_brightness(int lvl);