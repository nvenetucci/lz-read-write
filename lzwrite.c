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
  int leftShift = 7;
  int rightShift = 1; // they also somewhat tell us our position in the loop (how many bytes we've read in)

  ofp = fopen(argv[2], "wb");

  // read in one byte at a time
  while(fread(&input, 1, 1, ifp) == 1){
    // when leftShift equals 7, we're either reading in the very 1st byte, or the 1st byte after every 8th byte
    if(leftShift == 7){
      // these bytes are simply shifted right by 1, and written out
      output = input >> rightShift;
      fwrite(&output, 1, 1, ofp);

      // stored in the buffer is the byte we've read in, shifted left by 7
      buffer = input << leftShift;
    }
    else{
      // shift the byte right and add to whatever was last stored in the buffer
      output = buffer | (input >> rightShift); // the value of rightShift will range from 2 to 8
      fwrite(&output, 1, 1, ofp);

      // stored in the buffer is the byte we've read in, shifted left
      buffer = input << leftShift; // the value of leftShift will range from 6 to 0

      // when leftShift equals 0, we've just read in our 8th byte, or every 8th byte thereafter
      if(leftShift == 0){
	// reset the shift counters so they'll return to being 7 and 1 in the next iteration
        leftShift = 8;
        rightShift = 0;

        // write out what's in the buffer, which would be the 8th byte shifted left by 0
        fwrite(&buffer, 1, 1, ofp);
      }
    }

    // decrement and increment shift counters at the end of each iteration
    leftShift--;
    rightShift++;
  }

  // to avoid adding addition padding when not needed
  if(leftShift != 7) // as long as our last byte isn't a multiple of 8
    fwrite(&buffer, 1, 1, ofp); // write out what's left in the buffer (the padded full byte)

  fclose(ofp);
  fclose(ifp);

  return 0;
}
