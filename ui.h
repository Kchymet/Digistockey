/* 
 * File:   ui.h
 * Author: 477grp8
 *
 * Created on April 28, 2015, 11:59 PM
 */

#ifndef UI_H
#define	UI_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "printer.h"

    typedef enum{
        UP,
        DOWN,
        LEFT,
        RIGHT,
        MIDDLE
    } direction_e;

    void processUI( print_t* );


#ifdef	__cplusplus
}
#endif

#endif	/* UI_H */

