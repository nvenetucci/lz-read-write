//=====================
// Nicholai Venetucci
//=====================

#include "stdio.h"
#include "stdlib.h"

int main(int argc, char *argv[]){
  if(argc != 3){
    printf("invalid number of command line arguments\n");
    exit(1);
  }

  FILE * ifp, * ofp;

  ifp = fopen(argv[1], "rb");

  if(ifp == NULL){
    printf("error opening file %s\n", argv[1]);
    exit(1);
  }

  unsigned char input, output, buffer;
  // shift counters to keep track of how many bits to shift
  int leftShift = 1;
  int rightShift = 8; // they also somewhat tell us our position in the loop (how many bytes we've read in)

  ofp = fopen(argv[2], "wb");
  
  // read in one byte at a time
  while(fread(&input, 1, 1, ifp) == 1){
    // when leftShift equals 1, we're either reading in the very 1st byte, or the 1st byte after every 9th byte
    if(leftShift == 1){
      buffer = input << leftShift; // this byte is shifted left by 1 and stored in the buffer
    }
    else{
      // shift the byte right and add to whatever was last stored in the buffer
      output = buffer | (input >> rightShift); // rightShift values range from 7 to 0
      fprintf(ofp, "%d\n", output); // write out as decimal

      // stored in the buffer is the byte we've read in, shifted left
      buffer = input << leftShift; // leftShift values range from 2 to 9

      // when leftShift equals 9, we've just read in our 9th byte, or every 9th byte thereafter
      if(leftShift == 9){
	// reset the shift counters so they'll return to being 1 and 8 in the next iteration
        leftShift = 0;
        rightShift = 9;
      }
    }

    // increment and decrement shift counters at the end of each iteration
    leftShift++;
    rightShift--;
  }

  fclose(ofp);
  fclose(ifp);

  return 0;
}
