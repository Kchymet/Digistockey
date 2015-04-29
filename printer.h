/* 
 * File:   printer.h
 * Author: 477grp8
 *
 * Created on April 28, 2015, 9:30 PM
 */

#ifndef PRINTER_H
#define	PRINTER_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct {
        int buff_start;
        int buff_end;
        int buff_size;
    } print_t;

    void initPrinter();
    void processPrinter(print_t*);
    int printString(print_t*,char*,size_t);
    int printChar(print_t*,char);
    void printStock(print_t*,char*,size_t,float,float,float);


#ifdef	__cplusplus
}
#endif

#endif	/* PRINTER_H */

