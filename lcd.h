/* 
 * File:   lcd.h
 * Author: 477grp8
 *
 * Created on April 17, 2015, 12:50 AM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

/* LCD Stuff */
#define LCDWR LATFbits.LATF5 //RF5
#define LCDRD LATDbits.LATD9 //RD9
#define LCDCE LATDbits.LATD10 //RD10
#define LCDCD LATDbits.LATD11 //RD11
#define LCDHALT LATDbits.LATD0 //RD0
#define DB0 LATEbits.LATE0 //RE0
#define DB1 LATEbits.LATE1 //RE1
#define DB2 LATEbits.LATE2 //RE2
#define DB3 LATEbits.LATE3 //RE3
#define DB4 LATEbits.LATE4 //RE4
#define DB5 LATEbits.LATE5 //RE5
#define DB6 LATEbits.LATE6 //RE6
#define DB7 LATEbits.LATE7 //RE7
#define D0 PORTEbits.RE0 //RE0
#define D1 PORTEbits.RE1 //RE1
#define D2 PORTEbits.RE2 //RE2
#define D3 PORTEbits.RE3 //RE3
#define D4 PORTEbits.RE4 //RE4
#define D5 PORTEbits.RE5 //RE5
#define D6 PORTEbits.RE6 //RE6
#define D7 PORTEbits.RE7 //RE7
#define DB  LATE //RE
#define LCDRST LATDbits.LATD5 //RD5
#define DIR LATFbits.LATF0

    void writeEN();
    void writeDIS();
    void LCDStat();
    void sendByte(char);
    void sendCommand(char);
    void sendData(char);
    void setMode();
    void setGraphicsHome();
    void setGraphicsArea();
    void setTextHome();
    void setTextArea();
    void setCGRom();
    void setAddrPointer(char,char);
    void DAWSet();
    void DARSet();
    void DAReset();
    void TestMessage();
    void clearMemory();
    void clearGraphics();
    void clearText();
    void clearDisplay();
    void WriteDisplay();
    void setCursorPattern();
    void setDisplayMode();
    void PrintInt(int);
    void PrintChar(char);
    void PrintString(char*);
    void PrintFloat(float);
    void PrintEmptyLine();
    void PrintStockInfo(char*,float,float,float);
    void initLCD();

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

