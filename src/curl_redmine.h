#ifndef __CURL_REDMINE_H
#define __CURL_REDMINE_H

#include<curl/curl.h>
#include<jansson.h>
static CURL* _CURL_REDMINE_HANDLER = NULL;
struct message
{
    char *str;
    int len;
};
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *userptr);
int curl_redmine_init(char* api_key);
json_t* curl_redmine_perform(char* url);
json_t* curl_redmine_get_issues();
void curl_redmine_cleanup();
void free_msg(struct message* msg);
#endif
