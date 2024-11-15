
#ifndef MyApiTestClient_hpp
#define MyApiTestClient_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/web/client/ApiClient.hpp"

/* Begin Api Client code generation */
#include OATPP_CODEGEN_BEGIN(ApiClient)

/**
 * Test API client.
 * Use this client to call application APIs.
 */
class MyApiTestClient : public oatpp::web::client::ApiClient {
  API_CLIENT_INIT(MyApiTestClient)

  API_CALL("GET", "/selene", getSelene)
  API_CALL("GET", "/SE/MC", getMCQuestion)
  API_CALL("GET", "/OOD/MC", getMCQuestion2)
};

/* End Api Client code generation */
#include OATPP_CODEGEN_END(ApiClient)

#endif  // MyApiTestClient_hpp
