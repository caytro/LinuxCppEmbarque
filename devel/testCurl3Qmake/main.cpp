#include <iostream>
#include <curl/curl.h>
#include <memory.h>
#include <nlohmann/json.hpp>



using namespace std;
using json = nlohmann::json;

struct response {
  char *memory;
  size_t size;
};

static size_t
mem_cb(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct response *mem = (struct response *)userp;

  char *ptr = (char *)realloc(mem->memory, mem->size + realsize + 1);
  if(!ptr) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}


int main()
{
    cout << "Hello World!" << endl;



    struct response chunk = {.memory = (char *)malloc(1),
                             .size = 0};
    CURL *hnd = curl_easy_init();

    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(hnd, CURLOPT_URL, "https://api.ambeedata.com/latest/by-lat-lng?lat=43.560537&lng=1.404690");

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "x-api-key: b83fcfd7137ff81d96b92a34d3488506b7d3976bda58077cab133e94efd0a240");
    headers = curl_slist_append(headers, "Content-type: application/json");
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, mem_cb);
    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, (void *)&chunk);
    printf("Before : \n");
    CURLcode ret = curl_easy_perform(hnd);
    cout << "Retour";
    printf("Retour : %d\n",ret);
    printf("Chunk : %s\n",chunk.memory);

    json ex2;
    ex2 = string(chunk.memory);
   cout << "Ozone : " <<  ex2["stations"][0]["OZONE"] <<endl;


    free(chunk.memory);
}





