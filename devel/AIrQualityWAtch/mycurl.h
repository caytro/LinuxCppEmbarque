#ifndef MYCURL_H
#define MYCURL_H

#include <iostream>
#include <curl/curl.h>
#include <memory.h>
#include <string>
#include "myoptions.h"

using namespace std;

struct memory {
  char *response;
  size_t size;
};

///
/// \brief The myCurl class
/// \brief Manage __API access__
/// \details includes _curl/curl.h_ library
/// \details includes _myoptions.h_ library
/// \details Requires _-lcurl_ flag
///
///
class myCurl
{

    CURL *hnd;



    ///
    /// \brief mem_cb
    /// \details Call back method required by _curl_easy_perform()_ method to store read datas in buffer
    /// \param void* contents
    /// \param size_t size
    /// \param size_t nmemb
    /// \param void* userp
    /// \return static size_t
    ///
    ///
    static size_t mem_cb(void *contents, size_t size, size_t nmemb, void *userp);



public:
    ///
    /// \brief myCurl
    /// \details constructor
    ///
    myCurl();


    ///
    /// \brief getData
    /// \details Allows to recover downloaded data
    /// \param char** response
    ///
    void getData(char** response);

    ///
    /// \brief exec
    /// \param myOption* options
    /// \return CURLcode
    /// \details Prepare and execute curl request using parameters in options
    /// \details Downloaded data can be retrieved by a call to the method getData()
    ///
    CURLcode exec(myOptions *options, char** data);
};

#endif // MYCURL_H
