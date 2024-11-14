#include <avr/io.h>

extern int game_started;

void OLED_create_home_menu();

void OLED_create_menu();

int OLED_navigate_menu();

void OLED_select_menu_item(int page);

void OLED_select_difficulty_item(int page);