#include <stdio.h>
#include "bitwise_op.c"
#include <stdio.h>
#include <string.h>

FILE * OpenFile(char FileName[], char mode[]);
void Duckfile(FILE * fptr_in, FILE * fptr_out);

FILE * OpenFile(char FileName[], char mode[]){
    FILE *myfile = NULL;
    myfile = fopen(FileName,mode);
  
    return myfile;
}

int main(int argc, const char * argv[])
{

	// scanf("%d");

    FILE * fptr_in = OpenFile("Breaking.Bad.S05E12.720p.HDTV.x264-EVOLVE.mkv", "rb");
    FILE * fptr_out = OpenFile("Breaking.Bad.S05E12.720p.HDTV.x264-EVOLVE.ducked", "wb");

	Duckfile(fptr_in,fptr_out);

    return 0;
}

void Duckfile(FILE * fptr_in, FILE * fptr_out){
	char duck_key[64];
	printf("Duckbits TWO-WAY ducking algorithm uses a 64 bytes key to secure your file using the low level DUCKMAN algorithm. Please enter the Ducking-Key (DK) you wish to use for this ducking: ");
	scanf("%s",duck_key);

    int bytecount = 0;
    unsigned int block;
    unsigned char byte_ducked;

    while(block != EOF){
    	// byte_buffer = 0x00;
    	byte_ducked = 0x00;

    	block = fgetc(fptr_in);
    	if(block == EOF){
    		break;
    	}

    	int i = 0;
   		 for(i = 1; i <= 8; i++){
   		    bytecount += 1;
   		 	int writebit = getBitFromByte(i, block);
   		 	// byte_buffer = FillBit(byte_buffer, writebit, i);
   		 	int DUCKTHIS = i % 2;

   		 	if(DUCKTHIS){
   		 		//If the  Ducking-Key tells you to duck this bit, do it
   		 		byte_ducked = FillBit(byte_ducked, (writebit == 0 ? 1 : 0), i);
   		 	}else{
   		 		//Leave intact otherwise
   		 		byte_ducked = FillBit(byte_ducked, writebit, i);
   		 	}

   		 }
   		 // printf("\nOriginal: %d (%c)\n",byte_buffer,byte_buffer);
   		 // printf("Ducked: %d (%c)\n",byte_ducked,byte_ducked);

   		 fputc(byte_ducked,fptr_out);
    }

    printf("\n");
   
    printf("%d Bytes Can Fly!\n", bytecount);
}