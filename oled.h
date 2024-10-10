#include <avr/io.h>

//#define oled_c ((volatile char *) 0x1000)
//#define oled_d ((volatile char *) 0x1200)

void OLED_init();

void write_c(uint8_t data);

void write_d(uint8_t data);

void OLED_reset();

void OLED_home();

void OLED_goto_line(uint8_t line);

void OLED_goto_column(uint8_t column);

void OLED_clear_line(uint8_t line);

void OLED_pos(uint8_t line, uint8_t column);

void OLED_write_data(char c);

void OLED_print_letter(char c);

void OLED_print_string(char* str);

void OLED_set_brightness(int lvl);

void OLED_print_arrow(uint8_t page, uint8_t column);