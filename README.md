fifteen.c:

The Game of Fifteen is a puzzle played on a square, two-dimensional board with numbered tiles that slide. 
The goal of this puzzle is to arrange the board’s tiles from smallest to largest, left to right, top to bottom, with an empty space in board’s bottom-right corner.
Tiles may not be moved diagonally, though, or forcibly removed from the board.

Example:

$ ./fifteen 3

Crete 3x3 dimensional game board

WELCOME TO GAME OF FIFTEEN

8  7  6

5  4  3

2  1  _

Tile to move:


/**************************/

recover.c:

recover JPEG images are deleted from card memory. 
In the computer world, "deleted" tends not to mean "deleted" but "forgotten."
Our job is to access those JPEGs from card.raw and retrieve it

Command:
$ ./recover card.raw


/**************************/

resize.c: 
resize an image by a factor

Example:
./resize 4 smiley.bmp big-smile.bmp
convert small.bmp to large.bmp by a factor of 4


/**************************/

vigenere.c:

encrypting messages using a sequence of keys (or, put another way, a keyword). 
In other words, if p is some plaintext and k is a keyword (i.e., an alphbetical string, whereby A represents 0, B represents 1, C represents 2, …​, and Z represents 25), then each letter, ci, in the ciphertext, c, is computed as:
ci = ( pi + kj ) mod 26

The letters in k must be reused cyclically as many times as it takes to encrypt p.
If Vigenere himself wanted to say HELLO to someone confidentially, using a keyword of, say, ABC, he would encrypt the H with a key of 0 (i.e., A), the E with a key of 1 (i.e., B), and the first L with a key of 2 (i.e., C), at which point he’d be out of letters in the keyword, and so he’d reuse (part of) it to encrypt the second L with a key of 0 (i.e., A) again, and the O with a key of 1 (i.e., B) again. And so he’d write HELLO as HFNLP

Example:
$ ./vigenere bacon

plaintext: Meet me at the park at eleven am

ciphertext: Negh zf av huf pcfx bt gzrwep oz
