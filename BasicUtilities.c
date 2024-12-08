// header file
#include "BasicUtilities.h"

/*
Name: compareStrings
Process: compares text quantities (c-style strings) without case sensitivity
         with the following outcomes:
         - for equal sized strings, if the first parameter is alphabetically
           greater than the second parameter, returns positive number
         - for equal sized strings, if the first parameter is alphabetically
           less than the second parameter, returns negative number
         - for equal sized strings, if the first parameter is alphabetically
           equal to the second parameter, returns zero
         - for unequal sized strings with common letters up to the length
           of the shortest string, returns difference in the length
           of the strings
Function input/parameters: strings to be compared(const char *)
Function output/parameters: none
Function output/returned: processed result as specified (int)
Device input/---: none
Device output/---: none
Dependencies: getStringLength, toLowerCaseLetter
*/
int compareStrings( const char *leftStr, const char *rightStr )
   {
    int diff, index = 0;
    int leftStrLen = getStringLength( leftStr );
    int rightStrLen = getStringLength( rightStr );

    while( index < leftStrLen && index < rightStrLen )
       {
        diff = toLowerCaseLetter( leftStr[ index ] ) 
                                       - toLowerCaseLetter( rightStr[ index ] );

        if( diff != 0 )
           {
            return diff;
           }

        index = index + 1;
       }

    return leftStrLen - rightStrLen;
   }

/*
Name: copyString
Process: copies characters from source string to destination string
         up to NULL_CHAR
Function input/parameters: source string (const char *)
Function output/parameters: destination string (char *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: none
*/
void copyString( char *destStr, const char *srcStr )
   {
    int index = 0;

    while( srcStr[ index ] != NULL_CHAR )
       {
        destStr[ index ] = srcStr[ index ];

        index++;

        destStr[ index ] = NULL_CHAR;
       }
   }

/*
Name: getStringLength
Process: finds the number of characters in (length of) a c-style string
Function input/parameters: string to be processed (const char *)
Function output/parameters: none
Function output/returned: length of string (int)
Device input/---: none
Device output/---: none
Dependencies: none
*/
int getStringLength( const char *str )
   {
    int index = 0;

    while( str[ index ] != NULL_CHAR )
       {
        index = index + 1;
       }

    return index;
   }

/*
Name: printSpaces
Process: recursively prints the given number of spaces to the screen
Function input/parameters: number of spaces to print (int)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/monitor: spaces printed as specified
Dependencies: none
*/
void printSpaces( int numSpaces )
   {
    if( numSpaces > 0 )
       {
        printf( "%c", SPACE );

        printSpaces( numSpaces - 1 );
       }
   }

/*
Name: toLowerCaseLetter
Process: if character is upper case letter, 
         returns associated lower case letter,
         otherwise has no effect
Function input/parameters: character to be processed (char)
Function output/parameters: none
Function output/returned: character processed as specified (char)
Device input/---: none
Device output/---: none
Dependencies: none
*/
char toLowerCaseLetter( char testChar )
   {
    if( testChar >= 'A' && testChar <= 'Z' )
       {
        return testChar - 'A' + 'a';
       }

    return testChar;
   }


