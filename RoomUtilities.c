// header file
#include "RoomUtilities.h"

// function implementations

/*
Name: clearRoomArray
Process: frees RoomArrayType memory, along with array memory, returns NULL
Function input/parameters: room array structure (const RoomArrayType *)
Function output/parameters: none
Function output/returned: NULL (RoomArrayType *)
Device input/---: none
Device output/---: none
Dependencies: free
*/
RoomArrayType *clearRoomArray( RoomArrayType *toClear )
   {
    free( toClear->array );

    free( toClear );

    return NULL;
   }

/*
Name: addRoomWithData
Process: adds room data to array and returns true,
         returns false if array is full
Function input/parameters: room data array (RoomArrayType *), 
                           building name (const char *),
                           room number, room capacity, associated index (int)
Function output/parameters: updated room data array(RoomArrayType *) 
Function output/returned: Boolean result of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: as needed, with copyString
*/
bool addRoomWithData( RoomArrayType *roomData, const char *buildingName,
                         int roomNumber, int roomCapacity, int associatedIndex )
   {
    if( roomData->size < roomData->capacity )
       {
        copyString( roomData->array[ roomData->size ].buildingName, 
                                                                 buildingName );
        roomData->array[ roomData->size ].roomNumber = roomNumber;
        roomData->array[ roomData->size ].roomCapacity = roomCapacity;
        roomData->array[ roomData->size ].associatedIndex = associatedIndex;

        roomData->size = roomData->size + 1;

        return true;
       }

    return false;
   }

/*
Name: addRoomFromRoom
Process: adds room data to array from other room and returns true,
         returns false if array is full
Function input/parameters: room data array (RoomArrayType *)
Function output/parameters: updated room data (RoomArrayType *) 
Function output/returned: Boolean result of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: setRoomWithData - one line of code
*/
bool addRoomFromRoom( RoomArrayType *destRoom, const RoomDataType srcRoom )
   {
    return addRoomWithData ( destRoom, srcRoom.buildingName, srcRoom.roomNumber,
                                srcRoom.roomCapacity, srcRoom.associatedIndex );
   }

/*
Name: compareRooms
Process: compares two rooms first alphabetically by building name,
         and then numerically by room number, with the following results:
         - if left room is greater than right room, returns positive number
         - if left room is less than right room, returns negative number
         - if rooms are the same, returns zero
Function input/parameters: room data to be compared(const RoomDataType *)
Function output/parameters: none
Function output/returned: result of specified comparison (int)
Device input/---: none
Device output/---: none
Dependencies: as needed, with compareStrings
*/
int compareRooms( const RoomDataType *leftRoom, const RoomDataType *rightRoom )
   {
    int strDiff 
            = compareStrings( leftRoom->buildingName, rightRoom->buildingName );

    if( strDiff == 0 )
       {
        return leftRoom->roomNumber - rightRoom->roomNumber;
       }

    return strDiff;
   }

/*
Name: createRoomArray
Process: allocates memory for RoomArrayType, and internal array,
         returns pointer to array type
Function input/parameters: array capacity (int)
Function output/parameters: none
Function output/returned: pointer to room array (RoomArrayType *)
Device input/---: none
Device output/---: none
Dependencies: malloc, with keyword sizeof
*/
RoomArrayType *createRoomArray( int initCapacity )
   {
    RoomArrayType *newArray 
                           = (RoomArrayType *)malloc( sizeof( RoomArrayType ) );

    newArray->array 
               = (RoomDataType *)malloc( initCapacity * sizeof( RoomDataType ) );

    newArray->capacity = initCapacity;

    newArray->size = 0;

    return newArray;
   }

/*
Name: deepCopyRoom
Process: copies source room data into destination room
Function input/parameters: source room data (const RoomDataType)
Function output/parameters: destination room data (RoomDataType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: as needed, with copyString
*/
void deepCopyRoom( RoomDataType *destRoom, const RoomDataType srcRoom )
   {
    copyString( destRoom->buildingName, srcRoom.buildingName );
    destRoom->roomNumber = srcRoom.roomNumber;
    destRoom->roomCapacity = srcRoom.roomCapacity;
    destRoom->associatedIndex = srcRoom.associatedIndex;
   }

/*
Name: displayList
Process: displays rooms with associated courses
Function input/parameters: pointer to course array (const CourseArrayType *)
Function output/parameters: pointer to room array (const RoomArrayType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: as needed, including printf, setCourseDataString
*/
void displayList( const CourseArrayType *courses, const RoomArrayType *rooms )
   {
    int roomIndex, courseIndex;
    char roomStr[ MAX_STR_LEN ], courseStr[ STD_STR_LEN ];

    printf( "\nClassroom/Course Request Fit List\n" );
    printf( "=================================\n" );

    for( roomIndex = 0; roomIndex < rooms->size; roomIndex++ )
       {
        setRoomDataString( roomStr, rooms->array[ roomIndex ] );
   
        courseIndex = rooms->array[ roomIndex ].associatedIndex;

        setCourseDataString( courseStr, courses->array[ courseIndex ] );

        printf( "%s - %s\n", roomStr, courseStr );   
       }
   }

/*
Name: setRoomDataString
Process: load room data into string, in format:
         "Building Name: <building name>, Room Number: <room number>,
          Room Capacity: <room capacity>"
Function input/parameters: room data (const RoomDataType)
Function output/parameters: loaded c-style string (char *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: as needed, including sprintf
*/
void setRoomDataString( char *dataStr, const RoomDataType roomData )
   {
    sprintf( dataStr, "Building Name: %s, Room Number: %d, Room Capacity: %3d",
            roomData.buildingName, roomData.roomNumber, roomData.roomCapacity );
   }

