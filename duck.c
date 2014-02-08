#include <stdio.h>
#include "bitwise_op.c"
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIGNATURE_1 0x0A
#define SIGNATURE_2 0xA0
#define SIGNATURE_3 0x5A
#define SIGNATURE_4 0x95
#define SIGNATURE_LENGTH 4

FILE * OpenFile(char FileName[], char * mode);
int Duckfile(FILE * fptr_in, FILE * fptr_out);
int FileIsDucked(FILE * fptr_in);
void MarkFileAsDucked(FILE * target);

FILE * OpenFile(char FileName[], char *mode){
    FILE *myfile = NULL;
    myfile = fopen(FileName,mode);

    return myfile;
}

int FileIsDucked(FILE * fptr_in){
  unsigned int signatures[SIGNATURE_LENGTH] = {SIGNATURE_1,SIGNATURE_2,SIGNATURE_3,SIGNATURE_4};
  int i;
  for(i=0;i<SIGNATURE_LENGTH;i++){
    if(fgetc(fptr_in) != signatures[i]){
      //sequence has mismatch - file has not been ducked
      fseek(fptr_in,0,SEEK_SET);
      return 0;
    }
  }
  //file has been ducked
  return 1;
}

void MarkFileAsDucked(FILE * target){
  unsigned int signatures[SIGNATURE_LENGTH] = {SIGNATURE_1,SIGNATURE_2,SIGNATURE_3,SIGNATURE_4};

  fseek(target,0,SEEK_SET);
  int i;
  for(i=0;i<SIGNATURE_LENGTH;i++){
      fputc(signatures[i],target);
  }
}

int main(int argc, const char * argv[])
{
  if(argc < 2){
    printf("Bad argument\n");
    return 0;
  }


    FILE * fptr_in = OpenFile(argv[1], "rb");
    char * outputname = malloc(sizeof(char) * 5 + sizeof(char)*10);
    strcpy(outputname, argv[1]);
    strcat(outputname, ".d"); //for debugging purpose
 
    if(fptr_in == NULL ){
      printf("Unable to read file. File may not exist.\n");
      return 0;
    }

    FILE * fptr_out = OpenFile(outputname, "wb");

    if(fptr_out == NULL){
       printf("Unable to write file. Check folder permission.\n");
       return 0;
    }

    int ducking_mode = Duckfile(fptr_in,fptr_out);

    printf("Saved encrypted file as %s\n",outputname);

    fclose(fptr_in);
    fclose(fptr_out);

    if(ducking_mode == 0){

       char prev;

       FILE * preview_ptr = OpenFile(outputname, "rb");
    
       printf("\n\n ======== Unducked Contents ========\n\n");
       do{
         prev = fgetc(preview_ptr);
         printf("%c",prev);
       }while(prev != EOF);

       fclose(preview_ptr);
    }

    printf("\n");

    
    return 0;
}

void PopulateKeyholeArray(int * keyholes, char * duckingkey){
  //Create boolean keyhole array used to determine whether current bit should be flipped
  int i,j=0;
  for(i = 0; i < strlen(duckingkey); i++){
     keyholes[i] = (int)(duckingkey[j] & 0x01);
     if(j++ > 8){
       j=0;
     }
  }
}

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

int Duckfile(FILE * fptr_in, FILE * fptr_out){
  char duck_key[64];
  srand(time(NULL));
  int ducking_mode = 0;

   if(!FileIsDucked(fptr_in)){
      printf("\n[ENCRYPTING] Please specify the Ducking Key (do not lose this key): "); 
      ducking_mode = 1;
   }else{
      printf("\n[REVERSING] Please specify the Ducking Key to unduck this file: ");
   }

   scanf("%s",duck_key);

   if(ducking_mode){
      MarkFileAsDucked(fptr_out);
   }


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

       int i = 0, j =0;

       for(i = 1; i <= 8; i++){
          bytecount += 1;
          
          int writebit = getBitFromByte(i, block);
          int FLIP_THIS_BIT = keyholes[j]; 

          if(FLIP_THIS_BIT){
            //If the  Ducking-Key tells you to duck this bit, do it
            byte_ducked = FillBit(byte_ducked, (writebit == 0 ? 1 : 0), i);
          }else{
            //Leave intact otherwise
            byte_ducked = FillBit(byte_ducked, writebit, i);
          }
          j = i;

          if(j > strlen(duck_key)){
            j = 0;
          }
       }
     
       fputc(byte_ducked,fptr_out);
    }

    printf("\n");
   
    
    printf("%d Bytes Can Fly!\n", bytecount);
    return ducking_mode;
}
