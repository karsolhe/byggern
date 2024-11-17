#include <avr/io.h>

void OLED_init();

void write_c(uint8_t data);

void write_d(uint8_t data);

void OLED_reset();

void OLED_goto_page(uint8_t page);

void OLED_goto_column(uint8_t column);

void OLED_clear_page(uint8_t page);

void OLED_pos(uint8_t page, uint8_t column);

void OLED_write_data(char c);

void OLED_print_char(char c);

void OLED_print_string(char* str);

void OLED_print_arrow(uint8_t page, uint8_t column);

void OLED_erase_arrow(uint8_t page, uint8_t column);

void OLED_print_heart(uint8_t page, uint8_t column);

void OLED_print_lives(int lives);