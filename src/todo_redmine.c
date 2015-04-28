#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<unistd.h>
#include<errno.h>
#include<jansson.h>
#include"curl_redmine.h"
#include"interface.h"


int main()
{
    struct redmine_t *redmine;

    print_issues();
    int len=0;
    char *input = malloc(255);
    int choice;
    while(1)
    {
        printf("Podaj numer: ");
        fflush(stdout);
        len = read(0, (void*)input, (size_t)255);
        if(!len)
            continue;
        input[len]='\0';
        printf("input: %s\n", input);
        char *endptr = NULL;
        choice = strtol(input, &endptr, 10);
        if(errno || input==endptr)
        {
            fprintf(stderr, "Błędna wartość\n");
            continue;
        }
        printf("%d\n", errno);
        printf("%d\n", choice);

        json_t *obj = json_array_get(issues, choice);
        printf("id:\t%d\n\
author:\t%s\n\
subcject:\t%s\n\
desc:\t%s\n\
created:\t%s\n\n",

                (int)json_integer_value(json_object_get(obj, "id")),
                json_string_value(json_object_get(json_object_get(obj,"author"),"name")),
                json_string_value(json_object_get(obj, "subject")),
                json_string_value(json_object_get(obj, "description")),
                json_string_value(json_object_get(obj, "created_on"))
            );

    }
//    json_decref(root);
    curl_redmine_cleanup();
    return 0;
}
