#include<string.h>
#include "curl_redmine.h"
#include<jansson.h>
int curl_redmine_init(char* api_key)
{
   _CURL_REDMINE_HANDLER = curl_easy_init();
    if(!_CURL_REDMINE_HANDLER)
        return -1;
    char key_header[64];
    sprintf(key_header,"X-Redmine-API-Key: %s", api_key);
    struct curl_slist *headers = NULL;
//    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, key_header);
    headers = curl_slist_append(headers, "Marcin: 123");
    curl_easy_setopt(_CURL_REDMINE_HANDLER, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(_CURL_REDMINE_HANDLER, CURLOPT_WRITEFUNCTION, write_data);

//    curl_slist_free_all(headers);
    
    return 0;    
}
json_t* curl_redmine_get_issues()
{
    json_t *result = curl_redmine_perform("http://redmine.exphost.pl/issues.json");
    if((!(result=json_object_get(result, "issues"))) || (!json_is_array(result)))
    {
        fprintf(stderr, "Blad pobierania danych\n");
        return 0;
    }
    return result;
} 
json_t* curl_redmine_perform(char* url)
{
    CURLcode res;
    struct message recv_msg = {NULL, 0};

    curl_easy_setopt(_CURL_REDMINE_HANDLER, CURLOPT_URL, url);
    curl_easy_setopt(_CURL_REDMINE_HANDLER, CURLOPT_WRITEDATA, &recv_msg);
    res = curl_easy_perform(_CURL_REDMINE_HANDLER);
    if(res != CURLE_OK)
    {
        fprintf(stderr, "curl perform error: %s\n", curl_easy_strerror(res));
        return NULL;
    }
    json_error_t error;
    json_t *result = json_loads(recv_msg.str, 0, &error);
    if(!result)
    {
        fprintf(stderr, "Problem z json loads\n%d\t%s\n", error.line, error.text);
        return 0;
    }

    if(recv_msg.str && recv_msg.len)
    {
        printf("%s\n", recv_msg.str);
        printf("%d\n", recv_msg.len);
    }
    else
    {
        printf("Nic do wypisania\n");
    }

    free_msg(&recv_msg);
    return result;

}
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *usrptr)
{
    struct message *data = (struct message*)usrptr;
    int start = data->len;
    data->len += size * nmemb;
    data->str = realloc(data->str, data->len);
    strncpy(&data->str[start], ptr, size*nmemb);
    return size * nmemb;
}
void free_msg(struct message* msg)
{
    if(msg->str)
    {
        free(msg->str);
    }
    msg->str = NULL;
    msg->len = 0;
}
void curl_redmine_cleanup()
{
    curl_easy_cleanup(_CURL_REDMINE_HANDLER);
}
