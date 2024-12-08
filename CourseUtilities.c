// header file
#include "CourseUtilities.h"
#include "BasicUtilities.h"
#include <stdlib.h>
#include <stdio.h>

// function implementations

/*
Name: addCourseWithData
Process: adds course data struct to array and returns true,
         returns false if array is full
Function input/parameters: course data array (CourseArrayType *), 
                           course name (const char *),
                           course size (int), course availability (bool)
Function output/parameters: updated course data array (CourseArrayType *) 
Function output/returned: Boolean result of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: as needed, with copyString
*/
bool addCourseWithData( CourseArrayType *courseData, const char *courseName,
                                 int courseSize, bool courseAvailability ) 
   {
    if( courseData->size < courseData->capacity )
       {
        copyString( courseData->array[ courseData->size ].courseName, 
                                                                   courseName );
        courseData->array[ courseData->size ].size = courseSize;

        courseData->array[ courseData->size ].available = courseAvailability;

        courseData->size = courseData->size + 1;

        return true;
       }

    return false;
   }

/*
Name: addCourseWithCourse
Process: adds course data to array and returns true,
         returns false if array is full
Function input/parameters: source course data array (const CourseArrayType *)
Function output/parameters: destination course data array (CourseArrayType *) 
Function output/returned: Boolean result of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: addCourseWithData - one line of code
*/
void addCourseWithCourse( CourseArrayType *destCourse, 
                                               const CourseDataType srcCourse )
   {
    addCourseWithData( destCourse, srcCourse.courseName, 
                                          srcCourse.size, srcCourse.available );
   }

/*
Name: clearCourseArray
Process: frees CourseArrayType memory, along with array memory, returns NULL
Function input/parameters: course array structure (CourseArrayType *)
Function output/parameters: none
Function output/returned: NULL (CourseArrayType *)
Device input/---: none
Device output/---: none
Dependencies: free
*/
CourseArrayType *clearCourseArray( CourseArrayType *courseData )
   {
    free( courseData->array );

    free( courseData );

    return NULL;
   }

/*
Name: createCourseArray
Process: allocates CourseArrayType memory, along with array memory, 
         returns pointer to new course
Function input/parameters: initial capacity
Function output/parameters: none
Function output/returned: created course (CourseArrayType *)
Device input/---: none
Device output/---: none
Dependencies: malloc, with keyword sizeof
*/
CourseArrayType *createCourseArray( int initCapacity )
   {
    CourseArrayType *newCourse 
                       = (CourseArrayType *)malloc( sizeof( CourseArrayType ) );

    newCourse->array 
          = (CourseDataType *)malloc( initCapacity * sizeof( CourseDataType ) );

    newCourse->capacity = initCapacity;

    newCourse->size = 0;

    return newCourse;
   }

/*
Name: deepCopyCourse
Process: copies source course data into destination course
Function input/parameters: source course data (const CourseDataType)
Function output/parameters: destination course data (CourseDataType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: as needed, including copyString
*/
void deepCopyCourse( CourseDataType *destCourse, 
                                                const CourseDataType srcCourse )
   {
    copyString( destCourse->courseName, srcCourse.courseName );
    destCourse->size = srcCourse.size;
    destCourse->available = srcCourse.available;
   }

/*
Name: setCourseDataString
Process: course data into string, in format:
         "Course Name: <course name>, Course Size: <course size>"
Function input/parameters: course data (const CourseDataType)
Function output/parameters: loaded c-style string (char *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: sprintf
*/
void setCourseDataString( char *dataStr, const CourseDataType courseData )
   {
    sprintf( dataStr, "Course Name: %s, Course Size: %3d",
                                       courseData.courseName, courseData.size );
   }


