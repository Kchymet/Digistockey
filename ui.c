/*
 * File:   ui.c
 * Author: 477grp8
 *
 * Created on April 28, 2015, 11:59 PM
 */

#define KPUP 0//PORTxbits.PORTxy
#define KPRIGHT 0//PORTxbits.PORTxy
#define KPDOWN 0//PORTxbits.PORTxy
#define KPLEFT 0//PORTxbits.PORTxy
#define KPMID 0//PORTxbits.PORTxy

#include <string.h>
#include "ui.h"
#include "printer.h"
#include "lcd.h"

typedef struct{
    char ticker[6];
    float value;
    float open;
    float close;
    float change;
} stock_t;

int isPressed(direction_e d){
    switch(d){
        UP: return KPUP; break;
        DOWN: return KPDOWN; break;
        LEFT: return KPLEFT; break;
        RIGHT: return KPRIGHT; break;
        MIDDLE: return KPMID; break;
        default: return 0; break;
    }
}

stock_t array[5];
int stock_index;
int pressed;

void initUI(){
    stock_index=0;
    pressed=0;
    /* SAMPLE STOCK 0 */
    strcpy(array[0].ticker,"GOOG");
    array[0].value=551.90;
    array[0].open=554.64;
    array[0].close=553.68;
    array[0].change=array[0].close-array[0].open;

    /* SAMPLE STOCK 1 */
    strcpy(array[0].ticker,"GOOGL");
    array[0].value=562.01;
    array[0].open=564.32;
    array[0].close=564.37;
    array[0].change=array[0].close-array[0].open;

    /* SAMPLE STOCK 2 */
    strcpy(array[0].ticker,"FB");
    array[0].value=80.57;
    array[0].open=81.83;
    array[0].close=80.68;
    array[0].change=array[0].close-array[0].open;

    /* SAMPLE STOCK 3 */
    strcpy(array[0].ticker,"MSFT");
    array[0].value=49.13;
    array[0].open=47.78;
    array[0].close=49.15;
    array[0].change=array[0].close-array[0].open;

    /* SAMPLE STOCK 4 */
    strcpy(array[0].ticker,"AAPL");
    array[0].value=130.18;
    array[0].open=134.46;
    array[0].close=130.56;
    array[0].change=array[0].close-array[0].open;
}

size_t length(char *a){
    int i=-1;
    while(a[++i]!='\0'){}
    return --i;
}

void processUI( print_t *pbuff_settings ){
    if(!pressed){
    if(isPressed(MIDDLE)){
        pressed=1;
        printStock( pbuff_settings, array[stock_index].ticker, length(array[stock_index].ticker),
                array[stock_index].value, array[stock_index].open, array[stock_index].close);
    }
    else if(isPressed(RIGHT)){
        pressed=1;
        stock_index=(stock_index+1)%5;
        PrintStockInfo( array[stock_index].ticker,
                array[stock_index].value, array[stock_index].open, array[stock_index].close);
    }
    else if(isPressed(LEFT)){
        pressed=1;
        stock_index=(stock_index-1)%5;
        PrintStockInfo( array[stock_index].ticker,
                array[stock_index].value, array[stock_index].open, array[stock_index].close);
    }
    else if(isPressed(DOWN)){ //TODO
    }
    else if(isPressed(UP)){ //TODO
    }
    }
}