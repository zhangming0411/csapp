/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  int var1 = ~x & y;
  int var2 = x & ~y;
  return ~(~var1 & ~var2);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  int Tmin = 1 << 31;
  return !(x ^ ~0 ^ Tmin);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int var1 = 0xAA;
  int var2 = var1 + (var1 << 8) + (var1 << 16) + (var1 << 24);
  int var3 = x & var2;
  return !(var3 ^ var2);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int var1 = x >> 3;  // right移三位
  // 那么只有三种情况 a.111000 b.111001 c.110xxx
  int cond1 = !(x ^ 0x38);  // a
  int cond2 = !(x ^ 0x39);  // b
  // 然后就是 110xxx -> a.000..000110
  int cond3 = !(var1 ^ 0x6); // c
  return !( !cond1 & !cond2 & !cond3 );
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int var1 = !(!x) << 31 >> 31;  // if x ? 1111...111(T1) : 0000...000(T0)
  int var2 = y & var1;  // if x ? y : T0 
  int var3 = (z | var1 ) ^ var1;  // if x ? T0 : z
  return (var2 | var3);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int isEqual = !(x ^ y);  // 是否相等 如果相等肯定满足
  int signX = !((x >> 31) & 0x1);  // 是否大于等于0
  int signY = !((y >> 31) & 0x1);  // 是否大于等于0
  int minus = x + ~y + 1;  // x - y
  // 那么分三种情况 a. x大于等于0 y小于0 （否） b. x小于0 y大于等于0(是) c. 两者同号 则比较差值(这时候差值肯定不会溢出)
  // int cond1 = !(!signX | signY);  // a
  // int cond2 = !(signX | !signY);  // b
  int cond2 = signX | !signY;  // b
  // c同号   且minus小于等于0满足
  int isSameSign = !(signX ^ signY);  // 是否同号
  int signMinus = (minus >> 31) & 0x1;  // 是否为负
  // int cond3 = !( !isSameSign | !signMinus);
  int cond3 = !isSameSign | !signMinus;
  // 所以最终结果就是 要么相等 要么cond1 要么cond3(把多余的!（!cond）格式修改为 cond)
  return !((!isEqual) & cond2 & cond3);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  // 想了一晚上，到第二天早上才有灵感。利用了当 x ！= 0 时候-x和x必有一个为负的性质
  // 靠，（原答案(~(( ~x + 1 ) ^ x) >> 31) & 0x1）  在x=INT_MIN的时候不满足 略微思考 把异或换成或就好啦。
  return (~(( ~x + 1 ) | x) >> 31) & 0x1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  return 0;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  unsigned sign = uf & 0x80000000;  // 掩码取符号位
  unsigned power = uf << 1 >> 24;  // 范围 0 到 255
  unsigned tail = uf & 0x7fffff;  // 23位
  if ( power == 255)  // 不管是NaN 还是 inf 都不会变
    return uf;
  else if ( power == 0)  // 又有两种情况 tail最高位是否是0
  {
    if ( tail >= 0x4000000)  // 最高位是1 这样就变成了格式化数
    {
      tail = (tail * 2) >> 1;
      power += 1;
    }
    else  // 否则就乘以二 依然是非格式化数
      tail = tail << 1;
  }
  else
  {
    power += 1; // 这时候要检测power是否变成了255，如果是的话，要把tail变成0
    if (power == 255)
      tail = 0;
  }
  return sign + (power << 23) + tail;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */

int floatFloat2Int(unsigned uf) {
  int ret_prob = 0x80000000u;
  unsigned sign = uf & 0x80000000;  // 掩码取符号位
  unsigned power = uf << 1 >> 24;  // 范围 0 到 255
  unsigned tail = (uf & 0x7fffff) | 0x800000;  // 24位 先取尾23位然后把第24位置1
  // printf("uf=%X, sign=%X, power=%X, tail=%X\n", uf, sign, power, tail);
  if (power == 0)  // 如果tail是0 那么就是0； 如果不是0 说明是接近0的数 然鹅大于-1的负数取int还是0（向0舍入） 总之 都是0
    return 0;
  else if ( power > 0 && power < 127)  // 绝对值小于1
    return 0;  
  else if ( power >= 127+32)  // 两种情况 1 NaN和inf 2 格式化表示 但是幂超过了32 所以肯定超限(31次方是有可能的 INT_MIN)
    return ret_prob;
  else if ( power == 127 )
  {
      if (sign == 0x80000000)
        return -1;
      else
        return 1;
  }
  else  // 剩下的情况就是power不为0的格式化数字
  {
    int real_e = power - 127;
    // printf("real_e=%d\n", real_e);
    return (sign >> (32-real_e)) + (tail << 8 >> (32-real_e));
  }
  return ret_prob;
}

/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    return 2;
}
