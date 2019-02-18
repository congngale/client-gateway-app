#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <string>
#include <curl/curl.h>

class HttpClient {
  public:
    HttpClient();
    ~HttpClient();

    long get(std::string url, std::string *response);
    long post(std::string url, std::string data, std::string *response);
};
#endif //HTTP_CLIENT_H
