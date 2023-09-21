#include "mycurl.h"


myCurl::myCurl(){}


void myCurl::getData(char **data)
{
    *data = (char*)malloc(chunk.size*sizeof(char));
    strncpy(*data, chunk.memory, chunk.size+1);
}

CURLcode myCurl::exec(myOptions* options)
{
    chunk = {.memory = (char *)malloc(1),.size = 0};
    CURL *hnd = curl_easy_init();

    cout << "Downloading datas from " << options->getFullUrl() << endl;

    // CURLOPT
    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(hnd, CURLOPT_URL, options->getFullUrl().c_str());
    curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYPEER, 0);

    // headers
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, options->getApiKeyHeader().c_str());
    headers = curl_slist_append(headers, "Content-type: application/json");
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

    // Callback
    curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, mem_cb);
    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, (void *)&chunk);

    CURLcode ret = curl_easy_perform(hnd);

    return ret;
}

size_t myCurl::mem_cb(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct response *mem = (struct response *)userp;

    char *ptr = (char *)realloc(mem->memory, mem->size + realsize + 1);
    if(!ptr) {
      // out of memory!
      printf("not enough memory (realloc returned NULL)\n");
      return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}
