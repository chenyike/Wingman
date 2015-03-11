//
//  Functions.h
//  Test_1
//
//  Created by Francisco de Villalobos on 9/25/13.
//  Copyright (c) 2013 Francisco de Villalobos. All rights reserved.
//


#ifndef Functions_h
#define Functions_h

char motor_control(char dir, int speed, char motor_num, char report);

int max(unsigned int* Data, int length);

void sort(unsigned int* Data, char order, int size);

int size(int Data, int type);

#endif
