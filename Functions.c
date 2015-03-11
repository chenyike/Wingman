//
//  Functions.c
//  Test_1
//
//  Created by Francisco de Villalobos on 9/25/13.
//  Copyright (c) 2013 Francisco de Villalobos. All rights reserved.
//


#include <stdio.h>
#include "Functions.h"
#include "Settings.h"
#include "m_general.h"
#include "m_usb.h"
#include "math.h"
#include "m_rf.h"
#include "m_bus.h"





/******************************************************************************************/
/*****************                      MAX Function                      *****************/
/******************************************************************************************/
// Returns the maximum value in an array
int max(unsigned int* Data, int length)
{
    int tmax = 0;
    int i = 0;
    for (i = 0; i<= length - 1; i++) {
        if (tmax < Data[i]) {
            tmax = Data[i];
        }
    }
    return tmax;
}

/******************************************************************************************/
/*****************                     SORT Function                      *****************/
/******************************************************************************************/
// Returns the vector in the correct order
void sort(unsigned int* Data, char order, int size)
{
    int aux = 0;
    int i = 0;
    int j = 0;
    
    
    for (i = 0; i< size-1; i++) {
        for (j=i+1; j<size; j++) {
            //m_usb_tx_string("  ");
            //m_usb_tx_int(Data[i]);
            if (order == 0) {
                if (Data[j] > Data[i]) {
                    aux = Data[j];
                    Data[j] = Data[i];
                    Data[i] = aux;
                }
            }
            if(order == 1){
                if (Data[j]<Data[i]) {
                    aux = Data[j];
                    Data[j] = Data[i];
                    Data[i] = aux;
                }
            }
        }
    }
}




/******************************************************************************************/
/*****************                     SIZE Function                      *****************/
/******************************************************************************************/
// Returns the size of a vector or array.
int size(int Data, int type){
    int asize;
    
    asize = Data/type;
    return asize;
}




