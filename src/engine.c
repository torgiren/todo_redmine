#include"engine.h"
#include<stdio.h>
#include"curl_redmine.h"
struct redmine_t* redmine_init(char* api)
{
    if(curl_redmine_init("5b1cb3c5ded0b8b2287b6609e95d9e79adc57ce4") < 0)
    {
        fprintf(stderr, "Problem z curl_init\n");
        return 0;
    }
    return 0;
}
