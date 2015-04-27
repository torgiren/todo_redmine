#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<unistd.h>
#include<errno.h>
#include<jansson.h>
#include"curl_redmine.h"


int main()
{
    if(curl_redmine_init("5b1cb3c5ded0b8b2287b6609e95d9e79adc57ce4") < 0)
    {
        fprintf(stderr, "Problem z curl_init\n");
        return -1;
    }
    

    json_t* root;
    json_error_t error;
//    root = json_loads(recv_msg.str, 0, &error);
//    free_msg(&recv_msg);
    root = curl_redmine_get_issues();
    printf("%x\n", root);

    if(!root)
    {
        fprintf(stderr, "Problem z json_loads\n%d\t%s\n", error.line, error.text);
        return -1;
    }
    json_t *issues;
    if((!(issues=json_object_get(root, "issues"))) || (!json_is_array(issues)))
    {
        fprintf(stderr, "Blad pobierania danych\n");
        return -1;
    }
    size_t index;
    json_t *value;
    json_array_foreach(issues, index, value)
    {
        json_t *project, *author;
        project = json_object_get(value, "project");
        author = json_object_get(value, "author"); 
        printf("%d\t%s\t%s\t%s\t%s\n",
                (int)index,
                json_string_value(json_object_get(project,"name")),
                json_string_value(json_object_get(author,"name")),
                json_string_value(json_object_get(value,"subject")),
                json_string_value(json_object_get(value,"created_on"))
              );
    }
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
    json_decref(root);
    curl_redmine_cleanup();
    return 0;
}
