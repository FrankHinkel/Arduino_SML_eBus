/*
 * error.cpp
 *
 *  Created on: 04.04.2013
 *      Author: Frank Hinkel
 */

#include "error.h"


void error(String Msg) {
	//if(!ErrorMsg.length()) ErrorMsg=Msg;

	info(Msg,MAX_INFO_LEVEL);
}

void info(String Msg) {
	info(Msg, 3);
}

void info(String Msg, int level) {
	if (level <= MAX_INFO_LEVEL) {
		Serial.println(Msg);
	}
}

