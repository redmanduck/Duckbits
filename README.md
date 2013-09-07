## Duckbits Pseudo-Encryption (File Ducking)
Duckbits flips bit according to the sequence calculated by the key user entered. 

## How it works

File ducking works essentially by manipulating the bits in the given file. There is no :randomness: in how the algorithm manipulate the bits, it is well defined in the key used to duck them. 

The ducking key is converted into binary, for example "foobar" will become "011001100110111101101111011000100110000101110010"

    This combination will be used to feed the flipping mechanism that flips the bits in the data file at the interval defined by the sequence of the ducking key.

    Example. 

         [011001100110111101101111011]          Ducking-Key is XOR with the data continuously
    Data: 0110100001100101011011000110|1100     at any location the result gives a one, the data bit is flipped
          011011110010000..

         [011001100110111101..]       Until the data file is exhausted
         1100011011110010000

Because of this, the algorithm is two-way if you have the ducking key. 

## Repetition

It is possible for a file to be ducked multiple times by multiple keys. To unduck the file, you must unduck the ducked file in the exact reverse order with its respective key(s). 

## Compiling and Running
     
    make duckbits
    ./duckbits <file_to_be_ducked>

and you can also do a reverse ducking

    ./duckbits <ducked_file>

Disclaimer: This is for experimental purpose and is by no mean a secure way of encrypting your documents. Use it at your own risk, or fork it :)
