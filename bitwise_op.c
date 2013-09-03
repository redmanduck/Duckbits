#include <stdio.h>
#include <stdlib.h>
#include "bitwise_op.h"

int getBitFromByte(int maskposition, unsigned char byte){
	unsigned char mask  = 0x80;
	switch(maskposition){
		case 1:
		  mask = 0x80;
		break;
		case 2:
		  mask = 0x40;
		break;
		case 3:
		  mask = 0x20;
		break;
		case 4:
		  mask = 0x10;
		break;
		case 5:
		  mask = 0x08;
		break;
		case 6:
		  mask = 0x04;
		break;
		case 7:
		  mask = 0x02;
		break;
		case 8:
		  mask = 0x01;
		break;
	}

	return ((byte & mask) != 0);
}

unsigned char FillBit(unsigned char Bucket, int bitToFill, int offset){
	//Position: LSB ...MSB  7..0
	int absoffset = (offset - 8);
	if(absoffset < 0) absoffset *= -1;
	Bucket |= (bitToFill << absoffset);
	return Bucket;
}


