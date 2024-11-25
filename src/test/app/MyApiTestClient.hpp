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

  API_CALL("GET", "/SE/MC", getSE_MCQuestion)
  API_CALL("GET", "/OOD/MC", getOOD_MCQuestion)
  API_CALL("GET", "/DP/MC", getDP_MCQuestion)
  API_CALL("GET", "/VC/MC", getVC_MCQuestion)

  API_CALL("GET", "/SE/MAT", getSE_MATQuestion)
  API_CALL("GET", "/OOD/MAT", getOOD_MATQuestion)
  API_CALL("GET", "/DP/MAT", getDP_MATQuestion)
  API_CALL("GET", "/VC/MAT", getVC_MATQuestion)
};

/* End Api Client code generation */
#include OATPP_CODEGEN_END(ApiClient)

#endif  // MyApiTestClient_hpp
