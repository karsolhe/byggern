#include <avr/io.h>
#include "can.h"

extern int game_started;

extern int menu;

void menu_create_home_menu();

void menu_create_difficulty_menu();

int menu_navigate();

void menu_select_item(int page);

CAN_message menu_select_difficulty_item(int page);