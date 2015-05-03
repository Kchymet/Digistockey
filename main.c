/* 
 * File:   main.cpp
 * Author: 477grp8
 *
 * Created on February 21, 2015, 3:39 PM
 */

// PIC32MZ2048ECH064 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>
#include "config.h"
#include "printer.h"
#include "lcd.h"
#include "delay.h"
#include "ui.h"

/* Printer Stuff */
print_t pbuff_settings;

int main(int argc, char** argv) {

    initLCD();
    initPrinter();
    initUI();
    
    while( 1 )
    {
        processUI( &pbuff_settings );
        processPrinter( &pbuff_settings );
    }
    return 0;
}

