#ifndef __ENGINE_H__
#define __ENGINE_H__
struct redmine_t
{
    struct CURL* curl_handler;
};
struct redmine_t* redmine_init(char* api);
#endif
