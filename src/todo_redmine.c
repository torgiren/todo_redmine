#include<stdio.h>
#include<curl/curl.h>
int main()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    printf("Hello\n");
    return 0;
}
