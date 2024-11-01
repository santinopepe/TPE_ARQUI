#ifndef SOUND_DRIVER_H
#define SOUND_DRIVER_H

#include <lib.h>



/**
 * @brief Function that makes a sound, until stop_beep is called (Code at libasm.asm)
 * @param void 
 * @returns void
*/
extern void beep2(); 

/**
 * @brief Function that stops the sound (Code at libasm.asm)
 * @param void 
 * @returns void
*/

extern void stop_beep(); // Declaración de la función


/**
 * @brief Function that makes a sound for a certain time
 * @param time The time the sound will last
 * @returns void
*/
void makeSound(uint64_t time);

#endif // SOUND_DRIVER_H
