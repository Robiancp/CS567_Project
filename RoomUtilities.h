#ifndef ROOM_UTILITIES_H
#define ROOM_UTILITIES_H

// header files
#include <string.h>
#include "StandardConstants.h"
#include "BasicUtilities.h"
#include "CourseUtilities.h"
#include <stdlib.h>
#include <stdio.h>

// data structure
typedef struct RoomDataStruct
   {
    char buildingName[ STD_STR_LEN ];
    int roomNumber;
    int roomCapacity;
    int associatedIndex;
   } RoomDataType;

typedef struct RoomArrayStruct
   {
    RoomDataType *array;

    int size, capacity;
   } RoomArrayType;

// function prototoypes

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
RoomArrayType *clearRoomArray( RoomArrayType *toClear );

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
                        int roomNumber, int roomCapacity, int associatedIndex );

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
bool addRoomFromRoom( RoomArrayType *destRoom, const RoomDataType srcRoom );

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
int compareRooms( const RoomDataType *leftRoom, const RoomDataType *rightRoom );

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
RoomArrayType *createRoomArray( int initCapacity );

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
void deepCopyRoom( RoomDataType *destRoom, const RoomDataType srcRoom );

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
void displayList( const CourseArrayType *courses, const RoomArrayType *rooms );

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
void setRoomDataString( char *dataStr, const RoomDataType roomData );


#endif   // ROOM_UTILITIES_H
