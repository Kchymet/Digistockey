/*
 * File:   delay.c
 * Author: 477grp8
 *
 * Created on April 28, 2015, 9:32 PM
 */

#include <xc.h>

void delayMs(int n){
    //take ~32khz / 8 * 4 -> 1ms period
    T1CON = 0x00008010; //TODO update scaler
    int i;
    for(i=0;i<n;++i){
        TMR1 = 0;
        while(TMR1<417);
    }
    T1CON = 0x00000000;
}

void delayNs(int n){
    //take ~32khz / 8 * 4 -> 1ms period
    T1CON = 0x00008010; //TODO update scaler
    int i;
    for(i=0;i<n;++i){
        TMR1 = 0;
        while(TMR1<7);
    }
    T1CON = 0x00000000;
}