/*
 * error.h
 *
 *  Created on: 04.04.2013
 *      Author: frank
 */

#ifndef ERROR_H_
#define ERROR_H_

#include <Arduino.h>


#define MAX_INFO_LEVEL 10

void error(String Msg);

void info(String Msg);
void info(String Msg, int level);

// xx

#endif /* ERROR_H_ */
