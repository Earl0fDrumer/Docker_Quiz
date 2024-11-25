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
  //Multiple Choice
  API_CALL("GET", "/DP/MC", getDP_MCQuestion)
  API_CALL("GET", "/OOD/MC", getOOD_MCQuestion)
  API_CALL("GET", "/SE/MC", getSE_MCQuestion)
  API_CALL("GET", "/VC/MC", getVC_MCQuestion)
  //Matching
  API_CALL("GET", "/DP/MAT", getDP_MATQuestion)
  API_CALL("GET", "/OOD/MAT", getOOD_MATQuestion)
  API_CALL("GET", "/SE/MAT", getSE_MATQuestion)
  API_CALL("GET", "/VC/MAT", getVC_MATQuestion)
  //True or Flase
  API_CALL("GET", "/DP/TF", getDP_TFQuestion)
  API_CALL("GET", "/OOD/TF", getOOD_TFQuestion)
  API_CALL("GET", "/SE/TF", getSE_TFQuestion)
  API_CALL("GET", "/VC/TF", getVC_TFQuestion)

  API_CALL("GET", "/SE/FIB", getSE_FIBQuestion)
  API_CALL("GET", "/OOD/FIB", getOOD_FIBQuestion)
  API_CALL("GET", "/DP/FIB", getDP_FIBQuestion)
  API_CALL("GET", "/VC/FIB", getVC_FIBQuestion)
};

/* End Api Client code generation */
#include OATPP_CODEGEN_END(ApiClient)

#endif  // MyApiTestClient_hpp
