#include "oled.h"
#include <avr/io.h>
#include <stdint.h>

volatile char *write_c = (char*) 0x1000;
volatile char *oled_d = (char*) 0x1200;

//void write_c(uint8_t data);

void OLED_init() {
    write_c[0] = 0xae; // display off
    write_c[0] = 0xa1; //segment remap
    write_c[0] = 0xda; //common pads hardware: alternative
    write_c[0] = 0x12;
    write_c[0] = 0xc8; //common output scan direction:com63~com0
    write_c[0] = 0xa8; //multiplex ration mode:63
    write_c[0] = 0x3f;
    write_c[0] = 0xd5; //display divide ratio/osc. freq. mode
    write_c[0] = 0x80;
    write_c[0] = 0x81; //contrast control
    write_c[0] = 0x50;
    write_c[0] = 0xd9; //set pre-charge period
    write_c[0] = 0x21;
    write_c[0] = 0x20; //Set Memory Addressing Mode
    write_c[0] = 0x02;
    write_c[0] = 0xdb; //VCOM deselect level mode
    write_c[0] = 0x30;
    write_c[0] = 0xad; //master configuration
    write_c[0] = 0x00;
    write_c[0] = 0xa4; //out follows RAM content
    write_c[0] = 0xa6; //set normal display
    write_c[0] = 0xaf; // display on

    // write_c(0xae); // display off
    // write_c(0xa1); //segment remap
    // write_c(0xda); //common pads hardware: alternative
    // write_c(0x12);
    // write_c(0xc8); //common output scan direction:com63~com0
    // write_c(0xa8); //multiplex ration mode:63
    // write_c(0x3f);
    // write_c(0xd5); //display divide ratio/osc. freq. mode
    // write_c(0x80);
    // write_c(0x81); //contrast control
    // write_c(0x50);
    // write_c(0xd9); //set pre-charge period
    // write_c(0x21);
    // write_c(0x20); //Set Memory Addressing Mode
    // write_c(0x02);
    // write_c(0xdb); //VCOM deselect level mode
    // write_c(0x30);
    // write_c(0xad); //master configuration
    // write_c(0x00);
    // write_c(0xa4); //out follows RAM content
    // write_c(0xa6); //set normal display
    // write_c(0xaf); // display on
}

void OLED_reset(){

}

void OLED_home(){

}

void OLED_goto_line(uint8_t line){

}

void OLED_goto_column(uint8_t column){

}

void OLED_clear_line(uint8_t line){


}

void OLED_pos(uint8_t line, uint8_t column){

}

void OLED_write_data(char c){
    // for(int i = 0; i < 8; i++) {
    //     oled_d[i] = c;
    // }
    write_c[0] = 0xb0; // set page start address

    while(1) {
        oled_d[0] = 0b00111000;
        oled_d[1] = 0b00111000;
        oled_d[2] = 0b01111100;
        oled_d[3] = 0b00111000;
        oled_d[4] = 0b00010000;
    } 
}

void OLED_print_char(char* c){

}

void OLED_set_brightness(int lvl){

}