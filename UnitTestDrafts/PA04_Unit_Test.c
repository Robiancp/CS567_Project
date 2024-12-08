#include <string.h>
#include <stdio.h>
#include <string.h>
#include <deepstate/DeepState.hpp>
#include "project_5.c"
#include "Console_IO_Utility.h"

TEST(Project4, PA04LowerCase) {

    char test_letter = DeepState_Char();
    ASSUME((int(test_letter) >= 97 && int(test_letter) <= 122) || (int(test_letter) >= 65 && int(test_letter) <= 90));

    char lowercase_letter = toLowerCaseLetter(test_letter);
    ASSERT(lowercase_letter == tolower(test_letter)) << "Letter must be converted to lowercase counterpart";

}

Test(Project4, PA04StringMatch) {

    int string_position;
    int comparison_result;

    int match_vs_mismatch = DeepState_Int();
    ASSUME(match_vs_mismatch >= 0 && match_vs_mismatch <= 100);

    int string_size_1 = DeepState_Int();
    ASSUME(string_size_1 >= 3 && string_size_1 <= 60);

    int string_size_2 = DeepState_Int();
    ASSUME(string_size_2 >= 3 && string_size_2 <= 60);

    if(match_vs_mismatch <= 50) {

        string_size_2 = string_size_1;

        char word_one[string_size_1];
        char word_two[string_size_2];

        for(string_position = 0; string_position < string_size_1; string_position++ ) {
            
            char rand_char = DeepState_Char()

            word_one[string_position] = rand_char;
            word_two[string_position] = rand_char;

        }

        comparison_result = compareStrings( word_one, word_two );
        ASSERT( comparison_result == 0 ) << "The strings are equal and should return 0";
    }
        
    else {

        char word_one[string_size_1];
        char word_two[string_size_2];

        for(string_position = 0; string_position < string_size_1; string_position++ ) {

            word_one[string_position] = DeepState_Char();

        }

        for(string_position = 0; string_position < string_size_2; string_position++ ) {

            word_two[string_position] = DeepState_Char();
        
        }

        comparison_result = compareStrings( word_one, word_two );
        ASSERT( comparison_result != 0 ) << "The strings aren't equal and should not return 0";

    }
}

Test(Project4, PA04StringCopy) {

    int string_position;

    int string_size = DeepState_Int();
    ASSUME(string_size >= 3 && string_size <= 60);

    char string_to_copy[string_size];
    char copied_string[string_size];
    
    for( string_position = 0; string_position < string_size; string_position++ ) {

            string_to_copy[string_position] = DeepState_Char();

        }

    copyString( copied_string, string_to_copy );
    ASSERT( strcmp( copied_string, string_to_copy ) == 0 ) << "Original and copied strings mus match";
}

Test(Project4, PA04CourseArrayComplete) {

    courses = createCourseArray( 25 );

    char course_array[18][10] = { "EE 110", "CS 105", "CS 205", "CS 305", 
                                "CS 122", "CS 126", "CS 249", "CS 567",
                                "EE 222", "EE 348", "EE 380", "EE 476C",
                                "MAT 136", "MAT 137", "MAT 238", "PHY 161",
                                "PHY 262", "PHY 363" }

    int curr_cycle;
    int Max_Num_Courses = 25;

    int course_add_cycles = DeepState_Int();
    ASSUME( course_add_cycles >= 0 && course_add_cycles <= 25 );

    for( curr_cycle = 1; curr_cycle <= course_add_cycles; curr_cycle++ ) {

        int rand_course_choice = DeepState_Int();
        ASSUME( rand_course_choice >= 0 && rand_course_choice <= 17 );

        int course_size = DeepState_Int();
        ASSUME( course_size >= 10 && course_size <= 120 );

        bool course_availability = DeepState_Bool();

        addCourseWithData( courses, course_array[rand_course_choice], 
                                            course_size, availability );
        
        ASSERT( strcmp(courses->array[curr_cycle - 1].courseName, course_array[rand_course_choice]) == 0 ) << "course name must stay the same";
        ASSERT( course->array[curr_cycle - 1].size == course_size ) << "course size must stay the same";
        ASSERT( course->array[curr_cycle - 1].available == course_availability ) << "course availability must stay the same";

    }

    courses = createCourseArray( courses );
    ASSERT( courses == NULL ) << "course array type must be NULL if freed correctly";

}

Test(Project4, PA04RoomArrayComplete) {

    rooms = createRoomArray( 25 );

    char building_array[8][25] = { "Health & Learning Center", "Bio Sciences", 
                                "Arts and Letters", "Education", "Health and Human Services", 
                                "Social and Behavoral Sciences", "W.A. Franke Business", 
                                "Forestry and Natural Sciences" }

    int curr_cycle;
    int Max_Num_Rooms = 25;

    int room_add_cycles = DeepState_Int();
    ASSUME( room_add_cycles >= 0 && room_add_cycles <= 25 );

    for( curr_cycle = 1; curr_cycle <= room_add_cycles; curr_cycle++ ) {

        int curr_room_index = (curr_cycle - 1);

        int rand_room_choice = DeepState_Int();
        ASSUME( rand_room_choice >= 0 && rand_room_choice <= 7 );

        int rand_room_num = DeepState_Int();
        ASSUME( rand_room_num > 100 && rand_room_num <= 3500 );

        int room_capacity = DeepState_Int();
        ASSUME( room_capacity >= 10 && room_capacity <= 120 );

        bool room_availability = DeepState_Bool();

        addRoomWithData( rooms, building_array[rand_room_choice], rand_room_num, room_capacity, curr_room_index );
        
        ASSERT( strcmp(rooms->array[curr_cycle - 1].buildingName, building_array[rand_course_choice]) == 0 ) << "building name must stay the same";
        ASSERT( rooms->array[curr_cycle - 1].roomNumber == rand_room_num ) << "room number must stay the same";
        ASSERT( rooms->array[curr_cycle - 1].roomCapacity == room_capacity ) << "room capacity must stay the same";
        ASSERT( rooms->array[curr_cycle - 1].associatedIndex == curr_room_index ) << "room index must stay the same";

    }

    courses = createCourseArray( courses );
    ASSERT( courses == NULL ) << "room array type must be NULL if freed correctly";

}

Test(Project4, StringLength) {

    int string_len = DeepState_Int();
    ASSUME(string_len >= 0 && string_len <= 50);

    char test_string[string_len];
    int string_pos;
    int str_len_output;
    int get_str_len_output;

    for( string_pos = 0; string_pos < string_len; string_pos++ ) {

        test_string[string_pos] = DeepState_Char;

    }

    str_len_output = strlen(test_string);

    get_str_len_output = getStringLength(test_string);

    ASSERT( strcmp(str_len_output, get_str_len_output) == 0 ) << "string length must not change";
    
}