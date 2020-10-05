#ifndef _SERVER_HTTP_RESPONSE_H
#define _SERVER_HTTP_RESPONSE_H

#include <map>

namespace server {

using std::string;

class HttpResponse {
public:
    enum HttpStatusCode {
        kUnknown,
        k200Ok = 200,
        k301MovedPermanently = 301,
        k400BadRequest = 400,
        k404NotFound = 404,
    };

    enum Version{
        kHttp10, kHttp11
    };

private:
    Version version_;
    std::map<string, string> headers_;
    HttpStatusCode code_;
    string body_;
};

}

#endif