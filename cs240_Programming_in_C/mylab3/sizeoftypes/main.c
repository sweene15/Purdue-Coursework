#include <stdio.h>

main()
{
int sizeOfChar;
int sizeOfInt;
int sizeOfFloat;
int sizeOfDouble;
int sizeOfUnsignedChar;
int sizeOfUnsignedInt;
int sizeOfSignedInt;
int sizeOfSignedChar;
int sizeOfLong;
int sizeOfLongInt;
int sizeOfLongDouble;
int sizeOfShort;
int sizeOfShortInt;
int sizeOfShortDouble;

sizeOfChar = sizeof(char);
sizeOfInt = sizeof(int);
sizeOfFloat = sizeof(float);
sizeOfDouble = sizeof(double);
sizeOfUnsignedChar = sizeof(unsigned char);
sizeOfUnsignedInt = sizeof(unsigned int);
sizeOfSignedInt = sizeof(signed int);
sizeOfSignedChar = sizeof(signed char);
sizeOfLong = sizeof(signed long);
sizeOfLongInt = sizeof(long int);
sizeOfLongDouble = sizeof(long double);
sizeOfShort = sizeof(short);
sizeOfShortInt = sizeof(short int);

printf("Char: %d\nInt: %d\nFloat: %d\nDouble: %d\nUnsigned Char: %d\nUnsigned Int: %d\nSigned Int: %d\nSigned Char: %d\nLong: %d\nLong Int: %d\nLong Double: %d\nShort: %d\nShort Int: %d\n", sizeOfChar, sizeOfInt, sizeOfFloat, sizeOfDouble, sizeOfUnsignedChar,  sizeOfUnsignedInt, sizeOfSignedInt, sizeOfSignedChar, sizeOfLong, sizeOfLongInt, sizeOfLongDouble, sizeOfShort, sizeOfShortInt);


}

