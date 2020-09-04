/* 
 * CS:APP Data Lab 
 * 
 * <Justin Kyle Chang 205388820>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
	/* Repeatedly ^ x's left counter part with its right counter part 
	until the final two bits are compared. The ending result should have a 
	least significant bit of 0 or 1 indicating if  there were 
	an odd (1) or even (0) number of zeros in x*/

	int half = (x >> 16) ^ x;
	half = (half >> 8) ^ half;
	half = (half >> 4) ^ half;
	half = (half >> 2) ^ half;
	half = (half >> 1) ^ half;
	return half&1;
}
/* 
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x18765432
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n) {	
	/* Create mask for 'max' integer, define 'shiftRightAmt' as 31 - n, and 
	'shiftLeftAmt' as 32 - n. Obtain the truncated value when rotating 
	by shifting 'max' 'shiftRightAmt' times to the right and then & x. 
	Initialize 'truncatedToFront as 'truncated' shifted left 'shiftleft'
	times to set truncated to the most significant positions.
	Because we are performing a left shift, bits will be padded with zero.
	Switch padded bits to one. Finally, shift x to the right n 
	times and return x & 'truncatedToFront'. */

	int max = ~(0x1 << 31);
	int shiftRightAmt = 31 + (~n + 1);
	int shiftLeftAmt = 32 + (~n + 1);
 	
	int truncatedMax = max >> shiftRightAmt;
	int truncated = truncatedMax & x;
	
	int truncatedToFront = truncated << shiftLeftAmt;
	truncatedToFront |= ~(truncatedMax << shiftLeftAmt);

	x >>= n;
	x |= truncatedMax << shiftLeftAmt;

	return x & truncatedToFront;
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {

	/* Declare a max byte to use to navigate to the desired n and m byte
	(maxByteM and maxByteN). Perform & with 'maxByteN' and 'maxByteM'
	to x to  obtain value at position n and m. Swap the values of
	'byteN' and 'byteM' by shifting to the least sig position and then 
	back left to the opposite n and m position. Perform & on x 
	with the ~ of both 'maxByteN' and 'maxByteM' to zero out x at 
	desired positions. Return x | with the swapped values of m
	and n. */

	int maxByte = 0xff; //value 255

	int maxByteN = (maxByte << (n << 3));
	int maxByteM = (maxByte << (m << 3)); 
	
	int byteN = maxByteN & x; //get value of byte at position n
	int byteM = maxByteM & x; //get value of byte at position m

	int swapM = (((byteN >> (n << 3)) << (m << 3)) & maxByteM);  
	int swapN = (((byteM >> (m << 3)) << (n << 3)) & maxByteN);
	
	x &= ~maxByteN;
	x &= ~maxByteM;

	return x | (swapN | swapM);		
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ .| + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
	/* Understand that the max of a short can be contained in 15 bits, while
	the min can be contained in 16 bits. Knowing this, we know that the 
	remaining 17 bit must be all zeros (to yield max) or all ones (to 
	yield negative min of 16 bit). We shift right 15 times to sign extend 
	the 17 bits. If the bits are all either 0 or 1, return 1; otherwise, 
	return 0. */ 

	int z = x >> 15;
	return !z | !(~z ^ 0);
}
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
	/* Apply De Morgan's Law by taking the | of ~x and ~y then return
	the ~ of that result */

	return ~(~x|~y);
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
	/* Because we can't use -, convert y into negative using ~y + 1. Get
	the signs of x, y, and differences of x and y. Overflow ocurs in two
	situations when x is (+), y is (-), and 'difference' is (-) or 
	when x is (-), y is (+), and 'difference' is (+). If x happens 
	to have different signs than y and 'difference', return 0;
	otherwise, return 1. */

	int difference = x + (~y + 1);
	int signX = x >> 31;
	int signY = y >> 31;
	int signDiff = difference >> 31;
	return !((signX ^ signY) & (signX ^ signDiff));
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
	/* Declare variable 'check' to identify the differing bits between x 
	and y. Perform a series of shifts from 1 to 16 increasing by 2^n
	on 'check' and	| that value with every prior 'check'. This takes into
	account the value of every bit with respect to their position. After
	& 'check' with ~(check >> 1) | min and (x ^ min) | (y ^ max), we 
	return the !!x to ensure either zero or one is returned. */
 
	int min = ~0 << 31;
	int max = ~min;

	int check = x ^ y;
	check |= check >> 1;
	check |= check >> 2;
	check |= check >> 4;
	check |= check >> 8;
	check |= check >> 16;

	check &= ~(check >> 1) | min;
	check &= (x ^ min) & (y ^ max);

	return !!check;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
	/* Understand that the max value of n bits can be contained in n-1
	bits, while the min can be contained in n bits. Knowing this,
	the remaining (32 - n - 1) bits must be all 0's (to yield 
	max) or all 1's (to yield negative min of n bits). We calculate the 
	shift amount, n - 1 then shift x to the right shift amount times. If 
	the bits are all either 0 or 1, return 1; otherwise, return 0. */

	int shiftAmount = ~((~n) + 1);
	int z = x >> shiftAmount;
	return !z | !(~z ^ 0);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	/* Use proof -x = ~x + 1 for two's complement numbers*/

	int switchSigns = ~x;
	return switchSigns + 1;
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
	/* Declare y as the ~ of x + 1 because if x is max, adding 1 should 
	cause overflow to tMin and then ~ should revert it back to tMax. 
	Check if x and y are equal; if  x is a max, performing this 
	procedure should yield the value of 0 for z. We return the ! of 
	z to turn 0 into 1. NOTICE! We must also add a !(~x) to 
	account for x being 0xffffffff which would also yield 0 for z 
	and 1 for !z. Including this, will negate this error. */
 
	int y = ~(x + 1);
	int z = x ^ y; 
	return !(z + !(~x));
}
