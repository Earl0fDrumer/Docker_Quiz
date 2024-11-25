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

  //Multiple Choice
  API_CALL("GET", "/selene", getSelene)
  API_CALL("GET", "/DP/MC", getDP_MCQuestion)
  API_CALL("GET", "/OOD/MC", getOOD_MCQuestion)
  API_CALL("GET", "/SE/MC", getSE_MCQuestion)
  API_CALL("GET", "/VC/MC", getVC_MCQuestion)
  //True or Flase
  API_CALL("GET", "/DP/TF", getDP_TFQuestion)
  API_CALL("GET", "/OOD/TF", getOOD_TFQuestion)
  API_CALL("GET", "/SE/TF", getSE_TFQuestion)
  API_CALL("GET", "/VC/TF", getVC_TFQuestion)
};

/* End Api Client code generation */
#include OATPP_CODEGEN_END(ApiClient)

#endif  // MyApiTestClient_hpp
