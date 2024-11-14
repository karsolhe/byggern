#include "oled.h"
#include <avr/io.h>
#include <stdint.h>
#include "fonts.h"

extern volatile char *oled_c;
extern volatile char *oled_d;

void write_c(uint8_t data) {
    oled_c[0] = data;
}

void write_d(uint8_t data) {
    oled_d[0] = data;
}

void OLED_home(){

}

void OLED_goto_page(uint8_t page){  //kanksje heller kall goto_page
    write_c(0xb0 + page); //set page start address
}

void OLED_goto_column(uint8_t column){
    write_c(0x00 + (column & 0x0f)); //set lower bits in column start address
    write_c(0x10 + (column >> 4)); //set higher bits in column start address
}

void OLED_clear_page(uint8_t page){
    OLED_goto_page(page);
    OLED_goto_column(0);
    for(int i = 0; i < 128; i++) {
        write_d(0);
    }
}

void OLED_reset(){
    //iterate through pages and columns and set all to 0
    for(int i = 0; i < 8; i++) {
        OLED_clear_page(i);
    }
}


void OLED_pos(uint8_t page, uint8_t column){
    //find correct page by dividing line by 8
    OLED_goto_page(page);
    OLED_goto_column(column);
}

//the GDDRAM column address pointer will be increased automatically by one after each data write.
void OLED_write_data(char c){
    write_d(c);
}

void OLED_print_char(char c){
    for(int i = 0; i < 5; i++) {
        write_d(pgm_read_byte(&(font5[c - 32][i])));
    }
}

void OLED_print_string(char* str){
    for(int i = 0; str[i] != '\0'; i++) {
        OLED_print_char(str[i]);
    }
}

void OLED_set_brightness(int lvl){

}

void OLED_print_arrow(uint8_t page, uint8_t column){
    OLED_pos(page, column);
    OLED_write_data(0b00011000);
    OLED_write_data(0b00011000);
    OLED_write_data(0b01111110);
    OLED_write_data(0b00111100);
    OLED_write_data(0b00011000);
}

void OLED_erase_arrow(uint8_t page, uint8_t column){
    OLED_pos(page, column);
    OLED_write_data(0);
    OLED_write_data(0);
    OLED_write_data(0);
    OLED_write_data(0);
    OLED_write_data(0);
}

void OLED_print_heart(uint8_t page, uint8_t column){
    OLED_pos(page, column);
    OLED_write_data(0b00001100);
    OLED_write_data(0b00011110);
    OLED_write_data(0b00111111);
    OLED_write_data(0b01111110);
    OLED_write_data(0b11111100);
    OLED_write_data(0b01111110);
    OLED_write_data(0b00111111);
    OLED_write_data(0b00011110);
    OLED_write_data(0b00001100);
}

void OLED_print_lives(int lives){
    OLED_reset();
    OLED_pos(1, 20);

    OLED_print_string("Lives left: ");

    for(int i = 1; i < lives+1; i++){
        OLED_print_heart(4, i*20);
    }
}

void OLED_init() {
    write_c(0xae); // display off
    write_c(0xa1); //segment remap
    write_c(0xda); //common pads hardware: alternative
    write_c(0x12);
    write_c(0xc8); //common output scan direction:com63~com0
    write_c(0xa8); //multiplex ration mode:63
    write_c(0x3f);
    write_c(0xd5); //display divide ratio/osc. freq. mode
    write_c(0x80);
    write_c(0x81); //contrast control
    write_c(0x50);
    write_c(0xd9); //set pre-charge period
    write_c(0x21); 
    write_c(0x20); //Set Memory Addressing Mode
    write_c(0x02); //page addressing mode
    write_c(0xdb); //VCOM deselect level mode
    write_c(0x30);
    write_c(0xad); //master configuration
    write_c(0x00); 
    write_c(0xa4); //out follows RAM content
    write_c(0xa6); //set normal display
    write_c(0xaf); // display on 
};