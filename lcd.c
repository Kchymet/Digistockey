/* 
 * File:   lcd.c
 * Author: 477grp8
 *
 * Created on April 28, 2015, 9:27 PM
 */

#include <xc.h>
#include "lcd.h"
#include "delay.h"

void writeEN(){
    LCDCE = 0; //enable LCD chip
    LCDWR = 0; //enable write to LCD
}

void writeDIS(){
    LCDCE = 1; //chip enable high
    LCDWR = 1; //stop writing
}

void LCDStat(){
    delayNs(2);  //TODO Change later to 1, leaving it slow while I'm working
}

void sendByte( char b ){
    DB = b;
    writeEN();
    asm("nop");
    writeDIS();
}

void sendCommand( char cmd ){
    LCDStat();
    LCDCD = 1;
    sendByte(cmd);
}

void sendData( char data ){
    LCDStat();
    LCDCD = 0;
    sendByte(data);
}

void setMode(){
    sendCommand( 0x83 );
}

void setGraphicHome(){
    sendData( 0x00 );
    sendData( 0x08 );
    sendCommand( 0x42 );
}

void setGraphicArea(){
    sendData( 0x14 );
    sendData( 0x00 );
    sendCommand( 0x43 );
}

void setTextHome(){
    sendData( 0x00 );
    sendData( 0x00 );
    sendCommand( 0x40 );
}

void setTextArea(){
    sendData( 0x14 );
    sendData( 0x00 );
    sendCommand( 0x41 );
}

void setCGRom(){
    sendData( 0x03 );
    sendData( 0x00 );
    sendCommand( 0x22 );
}

void setAddrPointer( char first , char second ){
    sendData( first );
    sendData( second );
    sendCommand( 0x24 );
}

void DAWSet(){ sendCommand( 0xB0 ); }
void DARSet(){ sendCommand( 0xB1 ); }
void DAReset(){
    sendCommand(0xB2);
}

void TestMessage(){
    int i;
    setAddrPointer( 0x00 , 0x00 );
    DAWSet();
    for(i=8;i>0;i=i--){
        LCDStat();
        sendData(0x28);LCDStat();
        sendData(0x45);LCDStat();
        sendData(0x59);LCDStat();
        sendData(0x00);LCDStat();
        sendData(0x2C);LCDStat();
        sendData(0x4F);LCDStat();
        sendData(0x4F);LCDStat();
        sendData(0x4B);LCDStat();
        sendData(0x01);LCDStat();
        sendData(0x00);LCDStat();
        sendData(0x00);LCDStat();
        sendData(0x00);LCDStat();
        sendData(0x00);LCDStat();
        sendData(0x00);LCDStat();
        sendData(0x00);LCDStat();
        sendData(0x00);LCDStat();
        sendData(0x00);LCDStat();
        sendData(0x00);LCDStat();
        sendData(0x00);LCDStat();
        sendData(0x00);LCDStat();
        sendData(0x21);LCDStat();
        sendData(0x00);LCDStat();
        sendData(0x34);LCDStat();
        sendData(0x48);LCDStat();
        sendData(0x49);LCDStat();
        sendData(0x4E);LCDStat();
        sendData(0x47);LCDStat();
        sendData(0x01);LCDStat();
        sendData(0x00);LCDStat();
        sendData(0x00);LCDStat();
        sendData(0x00);LCDStat();
        sendData(0x00);LCDStat();
        sendData(0x00);LCDStat();
        sendData(0x00);LCDStat();
        sendData(0x00);LCDStat();
        sendData(0x00);LCDStat();
        sendData(0x00);LCDStat();
        sendData(0x00);LCDStat();
        sendData(0x00);LCDStat();
        sendData(0x00);
     }
}
void clearMemory(int n){
    //clear 20 cols by 16 rows: 320 addresses
    int i;
    DAWSet();
    for(i=n;i>0;i--){
        sendData(0x00);LCDStat();
    }
    DAReset();
}

void clearGraphics(){
    setAddrPointer( 0x00 , 0x00 );
    clearMemory(120);
}

void clearText(){
    setAddrPointer( 0x00 , 0x00 );
    clearMemory(120);
}

void clearDisplay(){
    setAddrPointer( 0x00 , 0x00 );
    clearMemory(320);
}
void WriteDisplay(){
    setAddrPointer( 0x00 , 0x00 );
    TestMessage();
}
void setCursorPattern(){
    sendCommand( 0xA0 );
}

void setCursorPointer( char col , char row ){
    sendData(col);
    sendData(row);
    sendCommand( 0x21 );
}

void setDisplayMode(){
    sendCommand(0x94);
}

void PrintInt  (int val){
    DAWSet();
    sendData(val+16);
    LCDStat();
    DAReset();
}
void PrintChar (char val){
    int i = val;
    i = i - 32;
    DAWSet();
    sendData(i);
    LCDStat();
    DAReset();
}
void PrintString(char* string){
    int i = 0;
    char next;
    next = string[i];
    while(next != '\0'){
        PrintChar(next);
        i++;
        next = string[i];
    }
}

void PrintFloat(float val)
{
    //always prints 5 places
    int i = val*100;
    int pflag = 0;
    int thous    = i/10000;
    int hund     = i/1000 - thous*10;
    int tenth    = i/100  - thous*100   - hund*10;
    int dectenth = i/10   - thous*1000  - hund*100  - tenth*10;
    int dechund  = i/1    - thous*10000 - hund*1000 - tenth*100 - dectenth*10;
    if(thous && !pflag){
        PrintInt(thous);
        pflag = 1;
    }
    else{
        PrintString(" ");
    }
    if(hund){
        PrintInt(hund);
        pflag = 1;
    }
    else{
        PrintString(" ");
    }
    PrintInt(tenth);

    PrintString(".");
    PrintInt(dectenth);
    PrintInt(dechund);
}

void PrintEmptyLine(){
    // 20 spaces per line
    PrintString("                    ");
}

void PrintMenu(char *menu, int select){
    clearDisplay();
    setAddrPointer( 0x00 , 0x00 );
    size_t line=0, chs = 0, i=0;
    if(select==line){ PrintChar('>'); }
    else{ PrintChar(' '); }
    chs++;
    while(menu[i]!='\0'){
        if(menu[i]=='\n'){
            while(chs++<20){
                PrintChar(' ');
            }
            if(++line == select){
                PrintChar('>');
            }
            else{ PrintChar(' '); }
            chs = 1;
        }
        else{
            chs++;
            PrintChar(menu[i]);
        }
        i++;
    }
    PrintEmptyLine();
    PrintEmptyLine();
    PrintEmptyLine();
    PrintEmptyLine();
    PrintEmptyLine();
}

void PrintStockInfo(char* ticker, float value, float open, float close, float predict){
    int negflag;
    float change = value - open;
    if(change < 0){
        negflag = 1;
        change = open - value;
    }
    else{
        negflag = 0;
    }

    setAddrPointer( 0x00 , 0x00 );
    PrintString(" Stock     Report   ");
    PrintEmptyLine();
    PrintEmptyLine();
    PrintString("   Ticker: ");
    PrintString(ticker);
    int i=0;
    while(ticker[i++] != '\0'){}
    while(i++ <= 5){ PrintString(" "); }
    PrintString("    ");
    PrintEmptyLine();
    PrintString("   Value: ");
    PrintFloat(value);
    PrintString("    ");
    PrintString("   Open:  ");
    PrintFloat(open);
    PrintString("    ");
    PrintString("   Close: ");
    PrintFloat(close);
    PrintString("     ");
    //PrintEmptyLine();
    PrintString(" Change:");
    if(negflag){
        PrintString("-");
    }
    else{ PrintString("+"); }
    PrintFloat(change);
    PrintString("    ");
    PrintString(" Predict: ");
    PrintFloat(predict);
    PrintString("    ");
    PrintEmptyLine();
    PrintString("       ^ Menu       ");
    PrintString(" <Prev *Print Next> ");
    PrintString("       v Menu       ");
    PrintEmptyLine();
}

void initLCD(){
    //initialize test values
    LATF = 0;
    LATE = 0;
    TRISF = 0;
    TRISE = 0;

    //Open Drain Controls
    ODCE = 0x00;
    ODCF = 0x00;

    //set LCD control output enables
    TRISFbits.TRISF0 = 0; //RF0 output
    TRISFbits.TRISF5 = 0; //RF5 output
    TRISDbits.TRISD0 = 0; //RD0 output
    TRISDbits.TRISD5 = 0; //RD5 output
    TRISDbits.TRISD9 = 0;//RD9 output
    TRISDbits.TRISD10 = 0; //RD10 output
    TRISDbits.TRISD11 = 0; //RD11 output

    //LCD Init
    LCDHALT = 1;
    LCDCE = 1;
    LCDCD = 1;
    LCDRD = 1;
    LCDWR = 1;
    LCDRST = 0;
    delayMs(50);
    LCDRST = 1;
    delayMs(50);

    setTextHome(); //map text memory
    setTextArea(); //map
    setGraphicHome();
    setGraphicArea();
    setMode();
    setCursorPattern();
    setDisplayMode(); //works


    clearDisplay(); //why isn't the display clearing
    setAddrPointer( 0x00 , 0x00 );

    //PrintStockInfo("ATVI", 122.72,2.81, 22.8);

    delayMs(50);
    LCDCE = 0; //enable chip
    delayMs(5000);

}