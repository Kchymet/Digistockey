/*
 * File:   ui.c
 * Author: 477grp8
 *
 * Created on April 28, 2015, 11:59 PM
 */

#define KPUP PORTBbits.RB2
#define KPDOWN PORTBbits.RB3
#define KPRIGHT PORTBbits.RB12
#define KPLEFT PORTBbits.RB14
#define KPMID PORTBbits.RB15

#include <xc.h>
#include <sys/attribs.h>
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
    float predict;
} stock_t;

stock_t hotlist[5];
stock_t portfolio[5];
int hotlist_index = 0, portfolio_index=0;

void initUI(){ 
    /* enable inputs on push button ports */
    TRISBbits.TRISB2 = 1;
    TRISBbits.TRISB3 = 1;
    TRISBbits.TRISB12 = 1;
    TRISBbits.TRISB14 = 1;
    TRISBbits.TRISB15 = 1;

    /* disable the silly analog default */
    ANSELBbits.ANSB2 = 0;
    ANSELBbits.ANSB3 = 0;
    ANSELBbits.ANSB12 = 0;
    ANSELBbits.ANSB14 = 0;
    ANSELBbits.ANSB15 = 0;

    /* SAMPLE STOCK 0 */
    strcpy(hotlist[0].ticker,"YHOO");
    hotlist[0].value=42.59;
    hotlist[0].open=43.12;
    hotlist[0].close=42.56;
    hotlist[0].predict=44.16;
    hotlist[0].change=hotlist[0].close-hotlist[0].open;

    /* SAMPLE STOCK 1 */
    strcpy(hotlist[1].ticker,"AOL");
    hotlist[1].value=39.90;
    hotlist[1].open=40.45;
    hotlist[1].close=39.90;
    hotlist[1].predict=40.55;
    hotlist[1].change=hotlist[1].close-hotlist[1].open;

    /* SAMPLE STOCK 2 */
    strcpy(hotlist[2].ticker,"CBS");
    hotlist[2].value=62.13;
    hotlist[2].open=62.50;
    hotlist[2].close=62.13;
    hotlist[2].predict=61.40;
    hotlist[2].change=hotlist[2].close-hotlist[2].open;

    /* SAMPLE STOCK 3 */
    strcpy(hotlist[3].ticker,"AMZN");
    hotlist[3].value=422.00;
    hotlist[3].open=427.11;
    hotlist[3].close=421.78;
    hotlist[3].predict=425.23;
    hotlist[3].change=hotlist[3].close-hotlist[3].open;

    /* SAMPLE STOCK 4 */
    strcpy(hotlist[4].ticker,"TWX");
    hotlist[4].value=84.41;
    hotlist[4].open=85.37;
    hotlist[4].close=84.41;
    hotlist[4].predict=82.8;
    hotlist[4].change=hotlist[4].close-hotlist[4].open;

        /* SAMPLE STOCK 0 */
    strcpy(portfolio[0].ticker,"GOOG");
    portfolio[0].value=551.90;
    portfolio[0].open=554.64;
    portfolio[0].close=553.68;
    portfolio[0].predict=553.69;
    portfolio[0].change=portfolio[0].close-portfolio[0].open;

    /* SAMPLE STOCK 1 */
    strcpy(portfolio[1].ticker,"GOOGL");
    portfolio[1].value=562.01;
    portfolio[1].open=564.32;
    portfolio[1].close=564.37;
    portfolio[1].predict=561.39;
    portfolio[1].change=portfolio[1].close-portfolio[1].open;

    /* SAMPLE STOCK 2 */
    strcpy(portfolio[2].ticker,"FB");
    portfolio[2].value=80.57;
    portfolio[2].open=81.83;
    portfolio[2].close=80.68;
    portfolio[2].predict=80.47;
    portfolio[2].change=portfolio[2].close-portfolio[2].open;

    /* SAMPLE STOCK 3 */
    strcpy(portfolio[3].ticker,"MSFT");
    portfolio[3].value=49.13;
    portfolio[3].open=47.78;
    portfolio[3].close=49.15;
    portfolio[3].predict=49.16;
    portfolio[3].change=portfolio[3].close-portfolio[3].open;

    /* SAMPLE STOCK 4 */
    strcpy(portfolio[4].ticker,"AAPL");
    portfolio[4].value=130.18;
    portfolio[4].open=134.46;
    portfolio[4].close=130.56;
    portfolio[4].predict=128.64;
    portfolio[4].change=portfolio[4].close-portfolio[4].open;

    /* Display Stock 0 on LCD */
    PrintStockInfo( hotlist[hotlist_index].ticker,
        hotlist[hotlist_index].value, hotlist[hotlist_index].open,
        hotlist[hotlist_index].close, hotlist[hotlist_index].predict);
}

size_t length(char *a){
    int i=-1;
    while(a[++i]!='\0'){}
    return i;
}

char MENUSTR[] = "Hotlist\nPortfolio\nReturn";

char MID_PUSH = 0;
char RIGHT_PUSH = 0;
char LEFT_PUSH = 0;
char UP_PUSH = 0;
char DOWN_PUSH = 0;

display_t currentScreen=DISPLAY;
stocktype_t currentType=HOTLIST;
size_t menusize=3;
int selected=0;

void processUI( print_t *pbuff_settings ){
    if(KPMID){
        if(!MID_PUSH){
        MID_PUSH=1;
            if(currentScreen==DISPLAY){
                if(currentType==HOTLIST){
                    printStock( pbuff_settings, hotlist[hotlist_index].ticker, length(hotlist[hotlist_index].ticker),
                        hotlist[hotlist_index].value, hotlist[hotlist_index].open, hotlist[hotlist_index].close);
                }
                else if(currentType==PORTFOLIO){
                    printStock( pbuff_settings, portfolio[portfolio_index].ticker, length(portfolio[portfolio_index].ticker),
                        portfolio[portfolio_index].value, portfolio[portfolio_index].open, portfolio[portfolio_index].close);
                }
            }
            else if(currentScreen==MENU){
                switch(selected){
                    case 0: currentType = HOTLIST; break;
                    case 1: currentType = PORTFOLIO; break;
                }
                currentScreen = DISPLAY;
                if(currentType==HOTLIST){
                    PrintStockInfo( hotlist[hotlist_index].ticker,
                        hotlist[hotlist_index].value, hotlist[hotlist_index].open, hotlist[hotlist_index].close,
                        hotlist[hotlist_index].predict);
                }
                else if(currentType==PORTFOLIO){
                    PrintStockInfo( portfolio[portfolio_index].ticker,
                        portfolio[portfolio_index].value, portfolio[portfolio_index].open, portfolio[portfolio_index].close,
                        portfolio[portfolio_index].predict);
                }
            }
        }
    }
    else{
        MID_PUSH=0;
    }

    if(KPRIGHT){
        if(!RIGHT_PUSH){
            RIGHT_PUSH=1;
            if(currentScreen==DISPLAY){
                if(currentType==HOTLIST){
                    ++hotlist_index;
                    hotlist_index=hotlist_index==5?0:hotlist_index;
                    PrintStockInfo( hotlist[hotlist_index].ticker,
                        hotlist[hotlist_index].value, hotlist[hotlist_index].open, hotlist[hotlist_index].close,
                        hotlist[hotlist_index].predict);
                }
                else if(currentType==PORTFOLIO){
                    ++portfolio_index;
                    portfolio_index=portfolio_index==5?0:portfolio_index;
                    PrintStockInfo( portfolio[portfolio_index].ticker,
                        portfolio[portfolio_index].value, portfolio[portfolio_index].open, portfolio[portfolio_index].close,
                        portfolio[portfolio_index].predict);
                }
            }
            else if(currentScreen==MENU){
                selected++;
                selected %= menusize;
                PrintMenu(MENUSTR,selected);
            }
        }
    }
    else{
        RIGHT_PUSH=0;
    }

    if(KPLEFT){
        if(!LEFT_PUSH){
            LEFT_PUSH=1;
            if(currentScreen==DISPLAY){
            
                if(currentType==HOTLIST){
                    --hotlist_index;
                    hotlist_index=hotlist_index==-1?4:hotlist_index;
                    PrintStockInfo( hotlist[hotlist_index].ticker,
                        hotlist[hotlist_index].value, hotlist[hotlist_index].open, hotlist[hotlist_index].close,
                        hotlist[hotlist_index].predict);
                }
                else if(currentType==PORTFOLIO){
                    --portfolio_index;
                    portfolio_index=portfolio_index==-1?4:portfolio_index;
                    PrintStockInfo( portfolio[portfolio_index].ticker,
                        portfolio[portfolio_index].value, portfolio[portfolio_index].open, portfolio[portfolio_index].close,
                        portfolio[portfolio_index].predict);
                }
            }
            else if(currentScreen==MENU){
                selected--;
                selected = selected<0?menusize-1:selected;
                PrintMenu(MENUSTR,selected);
            }
        }
    }
    else{
        LEFT_PUSH=0;
    }

    if(KPDOWN){
        if(!DOWN_PUSH){
            DOWN_PUSH=1;
            if(currentScreen==DISPLAY){
                PrintMenu(MENUSTR,selected);
                currentScreen=MENU;
            }
            else if(currentScreen==MENU){
                selected++;
                selected %= menusize;
                PrintMenu(MENUSTR,selected);
            }
        }
    }
    else{
        DOWN_PUSH=0;
    }
    
    if(KPUP){

        if(!UP_PUSH){
            UP_PUSH=1;
            if(currentScreen==DISPLAY){
                PrintMenu(MENUSTR,selected);
                currentScreen = MENU;
            }
            else if(currentScreen==MENU){
                selected--;
                selected = selected<0?menusize-1:selected;
                PrintMenu(MENUSTR,selected);
            }
        }
    }
    else{
        UP_PUSH=0;
    }

    delayMs(10);
}