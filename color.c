// *beta

#include <stdio.h>
#include <string.h>
#define DEF_COLOR_MODE 0
#define COLOR_MODE 1

#define COLOR_END                   "\x1b[0m"

#define TEXT_COLOR_RED              "\x1b[31m" 
#define TEXT_COLOR_GREEN            "\x1b[32m"
#define TEXT_COLOR_YELLOW           "\x1b[33m"
#define TEXT_COLOR_BLUE             "\x1b[34m"
#define TEXT_COLOR_PURPLE           "\x1b[35m"
#define TEXT_COLOR_WHITE            "\x1b[37m"

#define BACKGROUND_COLOR_RED        "\x1b[41m"
#define BACKGROUND_COLOR_GREEN      "\x1b[42m"
#define BACKGROUND_COLOR_YELLOW     "\x1b[43m"
#define BACKGROUND_COLOR_BLUE       "\x1b[44m"
#define BACKGROUND_COLOR_PURPLE     "\x1b[45m"
#define BACKGROUND_COLOR_WHITE      "\x1b[47m"

// void getColors() 
// {
//     printf("\n%sRED     color test%s\n", TEXT_COLOR_RED,        COLOR_END);
//     printf("\n%sGREEN   color test%s\n", TEXT_COLOR_GREEN,      COLOR_END);
//     printf("\n%sYELLOW  color test%s\n", TEXT_COLOR_YELLOW,     COLOR_END);
//     printf("\n%sBLUE    color test%s\n", TEXT_COLOR_BLUE,       COLOR_END);
//     printf("\n%sPURPLE  color test%s\n", TEXT_COLOR_PURPLE,     COLOR_END);
//     printf("\n%sWHITE   color test%s\n", TEXT_COLOR_WHITE,      COLOR_END);

//     printf("\n%sBACKGROUND_RED      color test%s\n", BACKGROUND_COLOR_RED,      COLOR_END);
//     printf("\n%sBACKGROUND_GREEN    color test%s\n", BACKGROUND_COLOR_GREEN,    COLOR_END);
//     printf("\n%sBACKGROUND_YELLOW   color test%s\n", BACKGROUND_COLOR_YELLOW,   COLOR_END);
//     printf("\n%sBACKGROUND_BLUE     color test%s\n", BACKGROUND_COLOR_BLUE,     COLOR_END);
//     printf("\n%sBACKGROUND_PURPLE   color test%s\n", BACKGROUND_COLOR_PURPLE,   COLOR_END);
//     printf("\n%sBACKGROUND_WHITE    color test%s\n", BACKGROUND_COLOR_WHITE,    COLOR_END);
// }
