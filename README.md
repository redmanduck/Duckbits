# Duckbits Pseudo-Encryption (File Ducking)
Duckbits flips bit according to the sequence calculated by the key user entered. 

## How it works

The ducking key is converted into binary, for example "foobar" will become "011001100110111101101111011000100110000101110010"

    This combination will be used to feed the flipping mechanism that flips the bits in the data file at the interval defined by the sequence of the ducking key.

    Example. 

         [011001100110111101101111011]          Ducking-Key is XOR with the data continuously
    Data: 0110100001100101011011000110|1100     at any location the result gives a one, the data bit is flipped
          011011110010000..

         [011001100110111101..]       Until the data file is exhausted
         1100011011110010000
