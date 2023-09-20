#ifndef MYCURL_H
#define MYCURL_H

#include <iostream>
#include <curl/curl.h>
#include <memory.h>
#include <string>
#include "myoptions.h"

using namespace std;

struct response {
  char *memory;
  size_t size;
};

///
/// \brief The myCurl class
/// \abstract Manage API access
///
class myCurl
{
    CURL *hnd;
    struct response chunk ;
    string api_key;
    string longitude, latitude;
    string url;
    struct curl_slist *headers = nullptr;

    static size_t mem_cb(void *contents, size_t size, size_t nmemb, void *userp);



public:
    ///
    /// \brief myCurl
    ///
    myCurl();
    ///
    /// \brief getApi_key
    /// \return
    ///
    const string &getApi_key() const;
    ///
    /// \brief setApi_key
    /// \param newApi_key
    ///
    void setApi_key(const string &newApi_key);
    ///
    /// \brief getLongitude
    /// \return
    ///
    const string &getLongitude() const;
    ///
    /// \brief setLongitude
    /// \param newLongitude
    ///
    void setLongitude(const string &newLongitude);
    ///
    /// \brief getLatitude
    /// \return
    ///
    const string &getLatitude() const;
    ///
    /// \brief setLatitude
    /// \param newLatitude
    ///
    void setLatitude(const string &newLatitude);
    ///
    /// \brief getUrl
    /// \return
    ///
    const string &getUrl() const;
    ///
    /// \brief setUrl
    /// \param newUrl
    ///
    void setUrl(const string &newUrl);
    ///
    /// \brief getResponseSize
    /// \return
    ///
    size_t getResponseSize();
    ///
    /// \brief getData
    /// \param char** response
    ///
    void getData(char** response);
    ///
    /// \brief exec
    /// \param myOption options
    /// \return
    ///
    CURLcode exec(myOptions *options);
};

#endif // MYCURL_H
