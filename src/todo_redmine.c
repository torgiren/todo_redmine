#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<curl/curl.h>
#include<jansson.h>
struct message
{
    char *str;
    int len;
};

int free_msg(struct message* msg);
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *usrptr);

int main()
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(!curl)
    {
        fprintf(stderr, "Problem z curl_easy_init()");
        return -1;
    }

    struct message recv_msg = {NULL, 0};

    struct curl_slist * headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "X-Redmine-API-Key: 5b1cb3c5ded0b8b2287b6609e95d9e79adc57ce4");

    curl_easy_setopt(curl, CURLOPT_URL, "http://redmine.exphost.pl/issues.json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &recv_msg);

    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
    {
        fprintf(stderr, "curl perform error: %s\n", curl_easy_strerror(res));
        return -1;
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
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    json_t* root;
    json_error_t error;
    root = json_loads(recv_msg.str, 0, &error);
    free_msg(&recv_msg);

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
        printf("%d - %s - %s - %s - %s\n",
                (int)json_integer_value(json_object_get(value,"id")),
                json_string_value(json_object_get(project,"name")),
                json_string_value(json_object_get(author,"name")),
                json_string_value(json_object_get(value,"subject")),
                json_string_value(json_object_get(value,"created_on"))
              );
    }
    json_decref(root);
    return 0;
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
int free_msg(struct message* msg)
{
    if(msg->str)
    {
        free(msg->str);
    }
    msg->str = NULL;
    msg->len = 0;
}
