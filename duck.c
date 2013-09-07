#include <stdio.h>
#include "bitwise_op.c"
#include <stdlib.h>
#include <string.h>
#include <time.h>

FILE * OpenFile(char FileName[], char mode[]);
void Duckfile(FILE * fptr_in, FILE * fptr_out);

FILE * OpenFile(char FileName[], char mode[]){
    FILE *myfile = NULL;
    myfile = fopen(FileName,mode);

    return myfile;
}

int main(int argc, const char * argv[])
{

    char * outputname = malloc(sizeof(char) * 5 + sizeof(char)*10);
    strcpy(outputname, argv[1]);
    strcat(outputname, ".duckman");

    FILE * fptr_in = OpenFile(argv[1], "rb");

    if(fptr_in == NULL ){
      printf("Unable to read file. File may not exist.\n");
      return 0;
    }

    FILE * fptr_out = OpenFile(outputname, "wb");

    if(fptr_out == NULL){
       printf("Unable to write file. Check folder permission.\n");
       return 0;
    }

  	Duckfile(fptr_in,fptr_out);

    printf("Saved encrypted file as %s\n",outputname);

    return 0;
}

void PopulateKeyholeArray(int * keyholes, char * duckingkey){
  //Create boolean keyhole array used to determine whether current bit should be flipped
  int i = 0;
  for(i = 0; i < strlen(duckingkey); i++){
     keyholes[i] = 1;
  }
}

void Duckfile(FILE * fptr_in, FILE * fptr_out){
	char duck_key[64];
  srand(time(NULL));

	printf("\nPlease specify the Ducking-Key (512 bits): ");
	scanf("%s",duck_key);


  /*

    How is the Ducking-Key used. The ducking key is converted into binary, for example "foobar" will become "011001100110111101101111011000100110000101110010"

    This combination will be used to feed the flipping mechanism. 

    Example. 

         [011001100110111101101111011]          Ducking-Key is masked with the data continuously
    Data: 0110100001100101011011000110|1100     at any 1s, the data bit is flipped
          011011110010000..

         [011001100110111101..]       Until the data file is exhausted
         1100011011110010000

  */

   printf("\n[ PROCESSING ] Ducking file right here right now..\n");

    int * keyholes = malloc(sizeof(int) * strlen(duck_key));
    PopulateKeyholeArray(keyholes, duck_key); 

    int bytecount = 0;

    unsigned int block;
    unsigned char byte_ducked;

    while(block != EOF){
    	byte_ducked = 0x00;  //container for the byte we're going to fill up

    	block = fgetc(fptr_in);
    	if(block == EOF){
    		break;
    	}

       int i = 0;
   		 for(i = 1; i <= 8; i++){
   		  bytecount += 1;
        

   		 	int writebit = getBitFromByte(i, block);
   		 	int FLIP_THIS_BIT = rand() % 2; 

   		 	if(FLIP_THIS_BIT){
   		 		//If the  Ducking-Key tells you to duck this bit, do it
   		 		byte_ducked = FillBit(byte_ducked, (writebit == 0 ? 1 : 0), i);
   		 	}else{
   		 		//Leave intact otherwise
   		 		byte_ducked = FillBit(byte_ducked, writebit, i);
   		 	}

   		 }

   		 fputc(byte_ducked,fptr_out);
    }

    printf("\n");
   
    printf("%d Bytes Can Fly!\n", bytecount);
}