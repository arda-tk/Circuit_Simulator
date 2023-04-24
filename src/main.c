// FIXME set default character set to UTF-8

/**
* Simple Analog Circuit Simulator Coded in C
*
* Group Members:
*               Arda Tanil Kersu
*               Zehra Deniz Salman
*               Can Rollas
*
* Advisors:
*         Abdurrahman Gumus
*         Md. Salam
*/

/*
 * Known bugs:
 *
 * If after a simulation, program is stopped, and run again for another simulation,
 * and crashes due to seg fault, do the following:
 *
 * Locate either of "testResistive()" or "testRLC()" in the source file "visual.c", add
 * an empty newline under the last line in the function of "puts (" ");" (or remove it,
 * if added previously), to force the compiler to rebuild the program. You should not
 * be getting seg fault after that.
 */

#include <stdlib.h>
#include "../include/visual.h"

int main()
{

    /*
     * Uncomment the function below to test the simulator on a resistive circuit such
     * as the one shown below, where "R" stands for "ohms", and "V" for "volts":
     *
     *   __ 2R __  __ 6R __  __ 4R __
     *  |        |         |         |
     * 20V      4R        8R        30V
     *  |        |         |         |
     *  |________|___GND___|_________|
     *
     *  To initialize the circuit, enter the following values on terminal:
     *  20 NV
     *  2 NO
     *  4 NO
     *  6 NO
     *  8 NO
     *  4 NO
     *  30 NV
     *
     *  where "NV" stands for "volts" with "No" orders of magnitude such as mili, pico, kilo etc.
     *  and "NO" stands for "ohms" with "No" orders of magnitude.
     */

    //testResistive();


    /*
     * Uncomment the function below to test the simulator on a RLC circuit such
     * as the one shown below:
     *
     *   __ 2kO __ __ 25mH __
     *  |         |          |
     * 10mV      10nF       4kO
     *  |         |          |
     *  |________GND_________|
     *
     *  To initialize the circuit, enter the following values on terminal:
     *  10 mV
     *  2 kO
     *  10 nF
     *  25 mH
     *  4 kO
     */

    //testRLC();

    exit(EXIT_SUCCESS);
}
