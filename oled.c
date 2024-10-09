#include "oled.h"
#include <avr/io.h>
#include <stdint.h>

volatile char *oled_c = (char*) 0x1000;
volatile char *oled_d = (char*) 0x1200;

void write_c(uint8_t data) {
    oled_c[0] = data;
}

void write_d(uint8_t data) {
    oled_d[0] = data;
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
}

void OLED_reset(){
    //iterate through pages and columns and set all to 0
    //set
    for(int i = 0; i < 8; i++) {
        write_c(0xb0 + i); // set page start address
        write_c(0x00); // set lower bits in column start address
        write_c(0x10); // set higher bits in column start address
        for(int j = 0; j < 128; j++) {
            write_d(0);
        }
    }
}

void OLED_home(){

}

void OLED_goto_line(uint8_t line){  //kanksje heller kall goto_page
    uint8_t page = line / 8;  //kanksje det heller er page_nr som blir tatt inn i funksjonen
    write_c(0xb0 + page); //set page start address
    write_c(0x00); //set lower bits in column start address
    write_c(0x10); //set higher bits in column start address
    //kanksje to linjer over er nødvendig
}

void OLED_goto_column(uint8_t column){
    write_c(0x00 + (column & 0x0f)); //set lower bits in column start address
    write_c(0x10 + (column >> 4)); //set higher bits in column start address

}

void OLED_clear_line(uint8_t line){
    uint8_t page = line / 8;
    write_c(0xb0 + page); //set page start address
    write_c(0x00); //set lower bits in column start address
    write_c(0x10); //set higher bits in column start address
    for(int i = 0; i < 128; i++) {
        write_d(0);
    }
    write_d(0b00000000);
}

void OLED_pos(uint8_t line, uint8_t column){
    //find correct page by dividing line by 8
    uint8_t page = line / 8;   //kanskje heller page_nr som parameter
    write_c(0xb0 + page); //set page start address
    //low_bits = column & 0x0f;
    //set column start address 
    write_c(0x00 + (column & 0x0f)); //set lower bits in column start address
    write_c(0x10 + (column >> 4)); //set higher bits in column start address

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