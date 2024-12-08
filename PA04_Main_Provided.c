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

    printf( "\nCourse/Classroom Fit Program\n" );
    printf( "============================\n" );

    rooms = createRoomArray( MAX_NUM_ROOMS );
    courses = createCourseArray( MAX_NUM_COURSES );
 
    if( uploadData( "in_1.txt", courses, rooms ) ) 
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
    // TODO: Create recursive backtracking function
    //       to find correct assignment of specified courses to available c Rooms
    
    // declare and initalize variables
    int courseIndex;
    bool success;
    
    // check if verbose is true and display recursion message if so
    if( verboseFlag )
       {

        // print recursion title
           // functions: printSpaces, printf
        printSpaces( roomLevel );
        printf( "Recursion Level %d: ", roomLevel );
        printf( "Seeking a fit for Building Name: %s, ", 
                    rooms->array[roomLevel].buildingName );
        printf( "Room Number: %3d, ", 
                    rooms->array[roomLevel].roomNumber );
        printf( "Room Capacity: %3d\n\n",
                    rooms->array[roomLevel].roomCapacity);
       }

    // create loop to go through and test each rooms for a fit
    for( courseIndex = 0; courseIndex < rooms->size; roomIndex++ )
       {
        
        // compare the current course capacity to 
        // room capacity only if the course is available
        if( course->array[courseIndex].available 
               && course->array[courseIndex].size 
               <= room->array[roomlevel].roomCapacity )
           {

            // set current course number to room this rooms associted index
            room->array[roomlevel].associatedIndex;

            // mark course as unavailable
            course->array[courseIndex].available = false;

            // check if verbose flag is true, printing success 
            // and course fit summary if true
            if( verboseFlag )
               {

                // print that the current test was a success
                   // functions: printSpaces, printf
            
                printSpaces( roomLevel + 2 );
                printf( "Trying Course Name: %s, ",
                            course->array[courseIndex].courseName );
                printf( "Course Size: %3d - Success!\n", 
                            course->array[courseIndex].size );

                // print that the the course size will fit
                   // functions: printSpaces, printf
                printSpaces( roomLevel + 4 );
                printf( "Course Name: %s, Course Size: %3d, ", 
                            course->array[courseIndex].courseName,
                            course->array[courseIndex].size );
                printf( "will fit in Building Name: %s, Room Number: %4d, ",
                            room->array[roomlevel].buildingName,
                            room->array[roomlevel].roomNumber );
                printf( "Room Capacity: %3d\n\n", 
                            course->array[courseIndex].size );
               }

            // check if past room count and return true if so because that
            // means a valid room was found for every iteration before as well
            if( roomLevel == rooms->size )
               {

                // return true
                return true;

               }

            // recall function recursively to test next room
               // functions: fitClassRooms
            success = fitClassRooms( courses, rooms, roomLevel + 1, 
                                                        verboseFlag );

            // if last test is successful, all other iteractions will be too
            if( success )
               {

                // return true
                return true;

	       }

           }

        // increase course index to move to check the next course
        courseIndex++;

	if( verboseFlag )
           {

            // print that the current test failed
               // functions: printSpaces, printf
	    printSpaces( roomLevel + 2 );
            printf( "Trying Course Name: %s, Course Size: %3d - Failed!\n", 
                        course->array[courseIndex].courseName,
                        course->array[courseIndex].size );

            // print recursion fallback message
               // functions: printSpaces, printf
            printSpaces( roomLevel );
            printf( "Course Name: %s, Course Size: %3d - ", 
                        course->array[courseIndex].courseName,
                        course->array[courseIndex].courseSize );
            printf( "recursion fell back to Recursion Level - %d!\n\n",
                        roomLevel - 1 );
           }

       }

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


