#ifndef _SERVER_HTTP_REQUEST_H
#define _SERVER_HTTP_REQUEST_H

#include <map>
#include <string>

namespace server {

using std::string;

class HttpRequest {
public:
    enum Method {
        kInvalid, kGet, kPost, kPut, kDelete
    };

    enum Version{
        kUnknown, kHttp10, kHttp11
    };

    static HttpRequest parse(const string& req);

private:
    // request line   : GET / http/1.1
    Method method_;
    string path_;
    Version version_;

    // request header : Host: ...
    std::map<string, string> headers_;
};


}
#endif