#include<stdio.h>
#include<curl/curl.h>
int main()
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl)
    {
        struct curl_slist * headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/xml");
        headers = curl_slist_append(headers, "X-Redmine-API-Key: 5b1cb3c5ded0b8b2287b6609e95d9e79adc57ce4");

        curl_easy_setopt(curl, CURLOPT_URL, "http://redmine.exphost.pl/issues.xml");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
        {
            fprintf(stderr, "curl perform error: %s\n", curl_easy_strerror(res));
            return -1;
        }
    }
    else
    {
        fprintf(stderr, "Problem z curl_easy_init()");
        return -1;
    }
    curl_easy_cleanup(curl);
    return 0;
}
