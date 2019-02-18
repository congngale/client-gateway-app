#include "http_client.h"

#include <iostream>

using namespace std;

//private function to receive data
size_t write_callback(char *contents, size_t size, size_t nmemb, void *result) {
  //append data to result
  ((string*)result)->append((char*)contents, size * nmemb);

  //return size
  return size * nmemb;
}

HttpClient::HttpClient() {
  //init global
  curl_global_init(CURL_GLOBAL_ALL);
}

HttpClient::~HttpClient() {
  //clean up global
  curl_global_cleanup();
}

long HttpClient::get(string url, string *response) {
  //init result
  long status = -1;

  //init curl
  CURLcode m_res;
  CURL *p_curl = curl_easy_init();
  struct curl_slist *p_headers = NULL;

  //check url
  if(p_curl) {
    //set header
    p_headers = curl_slist_append(p_headers, 
      "Content-Type: application/json;charset=UTF-8");

    //append header to curl
    curl_easy_setopt(p_curl, CURLOPT_HTTPHEADER, p_headers);

    // set timeout - 10 seconds
    curl_easy_setopt(p_curl, CURLOPT_TIMEOUT, 10L);

    //set request url
    curl_easy_setopt(p_curl, CURLOPT_URL, url.c_str());
    
    //set write callback
    curl_easy_setopt(p_curl, CURLOPT_WRITEFUNCTION, write_callback);
    
    //set data callback
    curl_easy_setopt(p_curl, CURLOPT_WRITEDATA, response);
  
    //perform request
    m_res = curl_easy_perform(p_curl);

    //check res
    if (m_res == CURLE_OK) {
      //get response code
      curl_easy_getinfo(p_curl, CURLINFO_RESPONSE_CODE, &status);
    } else {
      //log error
      cout << "Failed to get data from url = " <<  url << ", error = " 
        << curl_easy_strerror(m_res) << endl;
    }

    //log debug
    cout << "Get data from url = " << url << " with status = "
      << status << endl;

    //clean up curl
    curl_easy_cleanup(p_curl);
  } else {
    //log error
    cout << "Curl object is not initialized" << endl;
  }

  return status;
}

long HttpClient::post(string url, string data, string *response) {
  //init status
  long status = -1;

  //init curl
  CURLcode m_res;
  CURL *p_curl = curl_easy_init();
  struct curl_slist *p_headers = NULL;

  //check curl
  if (p_curl) {
    //set header
    p_headers = curl_slist_append(p_headers, 
      "Content-Type: application/json;charset=UTF-8");

    //append header to curl
    curl_easy_setopt(p_curl, CURLOPT_HTTPHEADER, p_headers);

    // set timeout - 10 seconds
    curl_easy_setopt(p_curl, CURLOPT_TIMEOUT, 10L);

    //set request url
    curl_easy_setopt(p_curl, CURLOPT_URL, url.c_str());

    //set data
    curl_easy_setopt(p_curl, CURLOPT_POSTFIELDS, data.c_str());

    //set data size
    curl_easy_setopt(p_curl, CURLOPT_POSTFIELDSIZE, (long) data.length());
    
    //set write callback
    curl_easy_setopt(p_curl, CURLOPT_WRITEFUNCTION, write_callback);
    
    //set data callback
    curl_easy_setopt(p_curl, CURLOPT_WRITEDATA, response);

    //perform request
    m_res = curl_easy_perform(p_curl);

    //check res
    if (m_res == CURLE_OK) {
      //get response code
      curl_easy_getinfo(p_curl, CURLINFO_RESPONSE_CODE, &status);
    } else {
      //log error
      cout << "Failed to post to url = " << url << " with data = " << data 
        << ", error = " << curl_easy_strerror(m_res) << endl;
    }

    //log debug
    cout << "Post data to url = " << url << " with data = " << data 
      << ", and status = " << status << endl;

    //clean up curl
    curl_easy_cleanup(p_curl);
  } else {
    //log error
    cout << "Curl object is not initialized" << endl;
  }

  return status;
}