/*
 * File:   printer.c
 * Author: 477grp8
 *
 * Created on April 28, 2015, 9:30 PM
 */

#include <xc.h>
#include "printer.h"

char pbuff[256];

void initPrinter(){
    PB2DIV = 1; //divide by 1, PBCLK2 = 8MHZ
    U3RXR =  0x0;
    RPB5R =  0x1;
    U3STA = 0;
    U3MODE = 0x00008800;
    U3STASET =  0x0400;
    U3BRG =  12; //16-bit baud rate prescaler, 266.667kHz/400 = 20kBaud
}

void processPrinter( print_t *settings ){
    if( !(U3STAbits.UTXBF) && settings->buff_size > 0 ){
        U3TXREG = pbuff[settings->buff_start++];
        settings->buff_size--;
        settings->buff_start %= 256;
    }
}

int printString( print_t *settings , char *str , size_t len ){
    int i;
    for(i=0;i<len;++i){
        if(settings->buff_size == 256){
            return -1;
        }
        pbuff[settings->buff_end++] = str[i];
        settings->buff_end %= 256;
        settings->buff_size++;
    }
}

int printChar( print_t *settings , char ch ){
    if(settings->buff_size == 256) return -1;
    pbuff[settings->buff_end++] = ch;
    settings->buff_end %= 256;
    settings->buff_size++;
}

int printFloat( print_t *settings , float val ){
    int i = val*100;
    int thous    = i/10000;
    int hund     = i/1000 - thous*10;
    int tenth    = i/100  - thous*100   - hund*10;
    int dectenth = i/10   - thous*1000  - hund*100  - tenth*10;
    int dechund  = i/1    - thous*10000 - hund*1000 - tenth*100 - dectenth*10;
    if(thous){
        printChar(settings,(char)thous+48);
    }
    else{ printChar(settings,' '); }
    if(hund || thous){
        printChar(settings,(char)hund+48);
    }
    else{ printChar(settings,' '); }
    printChar(settings,(char)tenth+48);
    printChar(settings,'.');
    printChar(settings,(char)dectenth+48);
    printChar(settings,(char)dechund+48);
}

void printStock( print_t *settings, char* ticker, size_t length, float value, float open, float close){
    printString(settings,"Ticker: ", 8);
    printString(settings,ticker,length);
    printChar(settings,'\n');
    printString(settings,"Value:  ", 8);
    printFloat(settings,value);
    printChar(settings,'\n');
    printString(settings,"Open:   ", 8);
    printFloat(settings,open);
    printChar(settings,'\n');
    printString(settings,"Close:  ", 8);
    printFloat(settings,close);
    printChar(settings,'\n');
    printChar(settings,'\n');
    printChar(settings,'\n');
}