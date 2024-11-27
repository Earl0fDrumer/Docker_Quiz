#ifndef CustomErrorHandler_hpp
#define CustomErrorHandler_hpp

#include <sstream>
#include <memory>
#include "oatpp/web/server/handler/ErrorHandler.hpp"
#include "oatpp/web/protocol/http/outgoing/BufferBody.hpp"
#include "oatpp/core/Types.hpp"

class CustomErrorHandler : public oatpp::web::server::handler::ErrorHandler {
 public:
  std::shared_ptr<oatpp::web::protocol::http::outgoing::Response>
  handleError(const oatpp::web::protocol::http::Status& status,
              const oatpp::String& message,
              const Headers& headers) override {
    oatpp::String funMessage;
    if (status.code == 404) {
      funMessage = "Oops! We couldn't find that page. Are you lost? 🚀";
    } else if (status.code == 400) {
      funMessage = "Hmm... Your request seems a bit off. Check it out! 🔍";
    } else {
      funMessage = "Something went wrong,"
      " but don't worry! We're working on it. 🛠️";
    }

    // Use a string stream to build the JSON response
    std::ostringstream bodyStream;
    bodyStream << "{\n"
               << "  \"status\": " << status.code << ",\n"
               << "  \"error\": \"" << status.description << "\",\n"
               << "  \"message\": \"" << funMessage->c_str() << "\"\n"
               << "}";

    // Wrap the body in a BufferBody
    auto bufferBody = oatpp::web::protocol::http::outgoing::
    BufferBody::createShared(bodyStream.str());

    // Return the response
    return oatpp::web::protocol::http::outgoing::
    Response::createShared(status, bufferBody);
  }
};

#endif /* CustomErrorHandler_hpp */
