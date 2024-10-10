#include "oled.h"
#include <avr/io.h>
#include <stdint.h>
#include "fonts.h"

volatile char *oled_c = (char *) 0x1000;
volatile char *oled_d = (char *) 0x1200;


void write_c(uint8_t data) {
    oled_c[0] = data;
}

void write_d(uint8_t data) {
    oled_d[0] = data;
}

void OLED_home(){

}

void OLED_goto_line(uint8_t line){  //kanksje heller kall goto_page
    write_c(0xb0 + line); //set page start address
}

void OLED_goto_column(uint8_t column){
    write_c(0x00 + (column & 0x0f)); //set lower bits in column start address
    write_c(0x10 + (column >> 4)); //set higher bits in column start address
}

void OLED_clear_line(uint8_t line){
    OLED_goto_line(line);
    OLED_goto_column(0);
    for(int i = 0; i < 128; i++) {
        write_d(0);
    }
}


void OLED_reset(){
    //iterate through pages and columns and set all to 0
    for(int i = 0; i < 8; i++) {
        // oled_c[0] = (0xb0 + i);
        // oled_c[0] = (0x00);
        // oled_c[0] = (0x10);
        OLED_goto_line(i);
        OLED_goto_column(0);
        for(int j = 0; j < 128; j++) {
            // oled_d[0] = (0b00000000);
            write_d(0);
        }
    }
}


void OLED_pos(uint8_t line, uint8_t column){
    //find correct page by dividing line by 8
    OLED_goto_line(line);
        
    
    OLED_goto_column(column);
}

//the GDDRAM column address pointer will be increased automatically by one after each data write.
void OLED_write_data(char c){
    write_d(c);
}

void OLED_print_letter(char c){
    for(int i = 0; i < 5; i++) {
        write_d(pgm_read_byte(&font5[c - 32][i]));
    }
}

void OLED_print_string(char* str){
    for(int i = 0; str[i] != '\0'; i++) {
        OLED_print_letter(str[i]);
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

void OLED_init() {
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
    // write_c(0x02); //page addressing mode
    // write_c(0xdb); //VCOM deselect level mode
    // write_c(0x30);
    // write_c(0xad); //master configuration
    // write_c(0x00); 
    // write_c(0xa4); //out follows RAM content
    // write_c(0xa6); //set normal display
    // write_c(0xaf); // display on 
    //OLED_pos(0, 0);
    oled_c[0] = (0xae); // display off
    oled_c[0] = (0xa1); //segment remap
    oled_c[0] = (0xda); //common pads hardware: alternative
    oled_c[0] = (0x12);
    oled_c[0] = (0xc8); //common output scan direction:com63~com0
    oled_c[0] = (0xa8); //multiplex ration mode:63
    oled_c[0] = (0x3f);
    oled_c[0] = (0xd5); //display divide ratio/osc. freq. mode
    oled_c[0] = (0x80);
    oled_c[0] = (0x81); //contrast control
    oled_c[0] = (0x50);
    oled_c[0] = (0xd9); //set pre-charge period
    oled_c[0] = (0x21);
    oled_c[0] = (0x20); //Set Memory Addressing Mode
    oled_c[0] = (0x02); //page addressing mode
    oled_c[0] = (0xdb); //VCOM deselect level mode
    oled_c[0] = (0x30);
    oled_c[0] = (0xad); //master configuration
    oled_c[0] = (0x00);
    oled_c[0] = (0xa4); //out follows RAM content
    oled_c[0] = (0xa6); //set normal display
    oled_c[0] = (0xaf); // display on
    

}