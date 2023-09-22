#include "mycurl.h"


myCurl::myCurl(){}


//void myCurl::getData(char **data)
//{
//    *data = (char*)malloc((chunk.size+1)*sizeof(char));
//    strncpy(*data, chunk.memory, chunk.size+1);
//}

CURLcode myCurl::exec(myOptions* options, char** data)
{
    struct memory chunk;
    chunk.response = (char*) nullptr;
    chunk.size= 0;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL *hnd = curl_easy_init();
    //cout << "Downloading datas from " << options->getFullUrl() << endl;

    // CURLOPT
    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(hnd, CURLOPT_URL, options->getFullUrl().c_str());
    curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYPEER, 0);

    // headers
    struct curl_slist *headers = (struct curl_slist*)nullptr;
    headers = curl_slist_append(headers, options->getApiKeyHeader().c_str());
    headers = curl_slist_append(headers, "Content-type: application/json");
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

    // Callback
    curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, mem_cb);
    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, (void *)&chunk);

    CURLcode ret = curl_easy_perform(hnd);
    curl_slist_free_all(headers);
    *data = (char*)malloc(((chunk.size)+1)*sizeof(char));
    strncpy(*data, chunk.response, chunk.size);
    curl_easy_cleanup(hnd);
    curl_global_cleanup();
    free(chunk.response);
    return ret;
}

size_t myCurl::mem_cb(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct memory  *mem = (struct memory *)userp;

    char *ptr = (char*)realloc(mem->response, (mem->size) + realsize + 1);
    if(ptr == nullptr) {
      // out of memory!
      printf("not enough memory (realloc returned NULL)\n");
      return 0;
    }
    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;
    return realsize;
}
