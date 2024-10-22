#include "soundDriver.h"
#include <time.h>

extern uint8_t inb(uint16_t in1);
extern void outb(uint16_t out1, uint8_t in1);

void makeSound(uint64_t time){
    beep(50);
    sleep(time);
    stop_beep();
}


 //Play sound using built-in speaker
 static void play_sound(uint32_t nFrequence) {
 	uint32_t Div;
 	uint8_t tmp;
 
        //Set the PIT to the desired frequency
 	Div = 1193180 / nFrequence;
 	outb(0x43, 0xb6);
 	outb(0x42, (uint8_t) (Div) );
 	outb(0x42, (uint8_t) (Div >> 8));
 
        //And play the sound using the PC speaker
 	tmp = inb(0x61);
  	if (tmp != (tmp | 3)) {
 		outb(0x61, tmp | 3);
 	}
 }
 
 //make it shut up
 static void nosound() {
 	uint8_t tmp = inb(0x61) & 0xFC;
     
 	outb(0x61, tmp);
 }
 
 //Make a beep
 void beep2() {
 	 play_sound(1000);
 	 sleep(1000);
 	 nosound();
          //set_PIT_2(old_frequency);
 }
