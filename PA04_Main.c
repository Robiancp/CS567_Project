// header files
#include <string.h>
#include "StandardConstants.h"
#include "File_Input_Utility.h"
#include "BasicUtilities.h"
#include "CourseUtilities.h"
#include "RoomUtilities.h"

// local constants
const int MAX_NUM_ROOMS = 25;
const int MAX_NUM_COURSES = 25;
const int NO_CLASS = -1;

// local prototypes
bool fitClassRooms( CourseArrayType *courseData, 
              RoomArrayType *roomData, int initialRoomLevel, bool verboseFlag );
bool uploadData( const char *fileName, 
                         CourseArrayType *courseData, RoomArrayType *roomData );

// main function
int main( int argc, char **argv )
   {
    int initialRoomLevel = 0;
    RoomArrayType *rooms;
    CourseArrayType *courses;
    bool verboseSetting = true;

    // Check if filename is provided
    if (argc < 2)
    {
        printf("Usage: %s <input_filename>\n", argv[0]);
        return 1; // Exit with error code
    }

    const char *inputFilename = argv[1]; // Take the filename from the command line


    printf( "\nCourse/Classroom Fit Program\n" );
    printf( "============================\n" );

    rooms = createRoomArray( MAX_NUM_ROOMS );
    courses = createCourseArray( MAX_NUM_COURSES );
 
    if( uploadData( inputFilename, courses, rooms ) ) 
       {
        printf( "Start Solution Search\n" );
      
        if( fitClassRooms( courses, rooms, initialRoomLevel, verboseSetting ) )
           {
            printf( "\nFit Classroom Success: Solution Found.\n");
          
            displayList( courses, rooms );
           }
      
        else
           {
            printf( "\nFit Classroom Failure: Solution not found.\n");
           }               
       }
  
    else
       {
        printf( "Upload failure\n" );
       }

    // end program

       // clear data 
       rooms = clearRoomArray( rooms );
       courses = clearCourseArray( courses );

       // show program end
       printf( "\nEnd Course/Classroom Fit Program\n" );
       
       // return success
       return 0;
   }

/*
Name: fitClassRooms
Process: implements brute force recursive backtracking strategy
         to fit specified courses with their specified student size
         into classrooms with their specified capacity
Function input/parameters: pointer to a courses array type (CourseArrayType *),
                           pointer to a room array type (RoomArrayType *),
                           room level shows which room is seeking a course
                           and indicates the recursion level (int),
                           verbose flag that specifies whether 
                           to display the recursive backtracking process (bool)
Function output/parameters: updated courses file (CourseArrayType *),
                            updated rooms file (RoomArrayType *)
Function output/returned: Boolean result of the process (bool)
Device input/---: none
Device output/---: none
Dependencies: available tools as needed
*/
bool fitClassRooms( CourseArrayType *courses, 
                         RoomArrayType *rooms, int roomLevel, bool verboseFlag )
   {

    // declare and initalize variables
    RoomDataType localRoom;
    CourseDataType localCourse;
    int courseIndex;
    char dataString[ MAX_STR_LEN ];

    // set local room to the current room data
       // functions: deepCopyRoom
    deepCopyRoom( &localRoom, rooms->array[roomLevel] );
    
    // check if verbose is true and display recursion message if so
    if( verboseFlag )
       {

        // print recursion title
           // functions: printf, printSpaces, setRoomDataString
        printf( "\n" );
        printSpaces( roomLevel );
        printf( "Recursion Level %d: Seeking a fit for ", roomLevel );
        setRoomDataString( dataString, localRoom );
        printf( "%s\n", dataString );

       }

    // create loop to go through and test each course for a fit
    for( courseIndex = 0; courseIndex < courses->size; courseIndex++ )
       {

        // set local cousre to the course currently being tested
           // functions: deepCopyCourse
        deepCopyCourse( &localCourse, courses->array[ courseIndex ] );

        // compare the current course capacity to 
        // room capacity only if the course is available
        if( localCourse.available && 
               localCourse.size <= localRoom.roomCapacity )
           {

            // set current course number the current room's associted index
            rooms->array[roomLevel].associatedIndex = courseIndex;

            // mark course as unavailable
            courses->array[courseIndex].available = false;

            // check if verbose flag is true, printing success 
            // and course fit summary if true
            if( verboseFlag )
               {

                // print that the current test was a success
                   // functions: printSpaces, printf, setCourseDataString
                printSpaces( roomLevel + 2 );
                printf( "Trying " );
                setCourseDataString( dataString, localCourse );
                printf( "%s ", dataString );
                printf( "- Success!\n" );

                // print that the the course size will fit
                   // functions: printSpaces, setCourseDataString, 
                   // printf, setRoomDataString
                printSpaces( roomLevel + 4 );
                setCourseDataString( dataString, localCourse );
                printf( "%s ", dataString );
                printf( "will fit in " );
                setRoomDataString( dataString, localRoom );
                printf( "%s\n", dataString );

               }

            // check if a successful fit was found at the max room level
            if( roomLevel == rooms->size - 1 )
               {

                // return true to cause a chain 
                // reaction and finish the program
                return true;

               }

            // else move to the next level and search for a fit
            else
               {

                // check if fitClassRooms failed
                   // functions: fitClassRooms
                if( fitClassRooms( courses, rooms, roomLevel + 1,
                                                            verboseFlag ) )
                   {

                    // return true to coninue chain reation and complete task
                    return true;

                   }

                // if verboseFlag is true and the porgram isn't 
                // finished, print recursion fallback message
                if( verboseFlag )
                   {

                    // print recursion fallback message
                       // functions: printf, printSpaces, setCourseDataString
                    printf("\n");
                    printSpaces( roomLevel );
                    setCourseDataString( dataString, localCourse );
                    printf( "%s ", dataString );
                    printf( "- recursion fell back to Recursion Level %d!\n\n",
                                roomLevel );
                   }

                // mark course as available again and continue searching
                courses->array[courseIndex].available = true;

               }
           }

        // else, not a matching fit, print out failed message
        else
           {

            // if verboseFlag true, print that the current test failed
            if( verboseFlag )
               {

                // print that the current test failed
                   // functions: printSpaces, printf, setCourseDataString
	        printSpaces( roomLevel + 2 );
                printf( "Trying " );
                setCourseDataString( dataString, localCourse );
                printf( "%s ", dataString );
                printf( "- Failed!\n" );

               }
           }
       }

    // return false if no solution was found
    return false;
   }

/*
Name: uploadData
Process: uploads data file containing rooms available and courses to be fitted,
         has internal flag to show uploaded data or not
Function input/parameters: file name (const char *),
                           pointer to course array type (CourseArrayType*),
                           pointer to room array type (RoomArrayType *)
Function output/parameters: updated courses file (CourseArrayType *),
                            updated rooms file (RoomArrayType *)
Function output/returned: Boolean result of the process (bool)
Device input/---: none
Device output/---: none
Dependencies: as needed, including File Input Utilities, and strcmp
*/
bool uploadData( const char *fileName, 
                          CourseArrayType *courseData, RoomArrayType *roomData )
   {
    char tempStr[ STD_STR_LEN ];
    int tempRoomNum, tempRoomCapacity, tempRoomAssociation = NO_CLASS;
    int tempClassSize, tempClassAvailable = true;
    bool verboseFlag = true;

    roomData->size = 0;

    if( openInputFile( fileName ) )
       {
        if( verboseFlag )
           {
            printf( "\n==========Upload start\n" );
           }

        // ignore first line
        readStringToLineEndFromFile( tempStr );  

        // capture first room line - prime loop
        readStringToDelimiterFromFile( COMMA, tempStr );

        // loop to end of room data
        while( strcmp( tempStr, "End Room Data" ) != 0 
                                     && roomData->size < roomData->capacity )
           {
            tempRoomNum = readIntegerFromFile();

            readCharacterFromFile();

            tempRoomCapacity = readIntegerFromFile();

            if( verboseFlag )
               {
                printf( "Nm: %s, Num: %d, cap: %d\n", 
                                       tempStr, tempRoomNum, tempRoomCapacity );
               }

            addRoomWithData( roomData, tempStr,
                           tempRoomNum, tempRoomCapacity, tempRoomAssociation );
            // reprime - capture next building name, or end of data string
            readStringToDelimiterFromFile( COMMA, tempStr );
           }

        // initialize class size
        courseData->size = 0;
    
        // ignore first line
        readStringToLineEndFromFile( tempStr );
  
        // capture first course line - prime loop
        readStringToDelimiterFromFile( COMMA, tempStr );    

        // loop to end of course data
        while( strcmp( tempStr, "End Class Data" ) != 0 
                                 && courseData->size < courseData->capacity )
           {
            // get class size
            tempClassSize = readIntegerFromFile();

            if( verboseFlag )
               {
                printf( "Nm: %s, sz: %d\n", tempStr, tempClassSize );
               }

            addCourseWithData( courseData,
                                   tempStr, tempClassSize, tempClassAvailable );

            // reprime - get next building name, or end of data string
            readStringToDelimiterFromFile( COMMA, tempStr );
           }

        if( verboseFlag )
           {
            printf( "==========Upload end\n\n" );
           }

        return true;
       }

    return false;
   }

