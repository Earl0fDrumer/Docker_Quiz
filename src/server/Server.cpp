#include "oatpp/network/Server.hpp"

#include "../controller/MultipleChoice/MC_Controller.hpp"
#include "../controller/FillInBlank/FillInBlank_Controller.hpp"
#include "../controller/TrueOrFalse/TF_Controller.hpp"
#include "../controller/Matching/MAT_Controller.hpp"
#include "../controller/TopicsController.hpp"
#include "../controller/RandomController.hpp"
#include "ServerComponents.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

void run() {
  ServerComponent components;

  /* Create Router for HTTP requests routing */
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

  /* Create FillInBlank_Controller and add all of its endpoints to the router */
  auto fillInBlankController = std::make_shared<FillInBlank_Controller>();
  router->addController(fillInBlankController);

  /* Create MCController and add all of its endpoints to router */
  auto obj_MC_Controller = std::make_shared<MC_Controller>();
  router->addController(obj_MC_Controller);

  /* Create TFController and add all of its endpoints to router */
  auto obj_TF_Controller = std::make_shared<TF_Controller>();
  router->addController(obj_TF_Controller);

  /* Create OODController and add all of its endpoints to router */
  auto obj_MAT_Controller = std::make_shared<MAT_Controller>();
  router->addController(obj_MAT_Controller);

  /* Create TopicsController and add all of its endpoints to router */
  auto obj_TOPIC_Controller = std::make_shared<TopicsController>();
  router->addController(obj_TOPIC_Controller);

  /* Create Random_Controller and add all of its endpoints to router */
  auto randomController = std::make_shared<Random_Controller>();
  router->addController(randomController);

  /* Create HTTP connection handler with router */
  auto connectionHandler = oatpp::web::server::
  HttpConnectionHandler::createShared(router);

  /* Set Custom Error Handler */
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::
  server::handler::ErrorHandler>, errorHandler);
  connectionHandler->setErrorHandler(errorHandler);

  /* Create TCP connection provider */
  OATPP_COMPONENT(std::shared_ptr<oatpp::
  network::ServerConnectionProvider>, connectionProvider);

  /* Create server which takes provided TCP connections and passes them to HTTP
   * connection handler */
  oatpp::network::Server server(connectionProvider, connectionHandler);

  /* Print info about server port */
  OATPP_LOGI("Selene Service", "Server running on port %s",
             connectionProvider->getProperty("port").toString()->c_str());

  /* Run server */
  server.run();
}

int main() {
  /* Init oatpp Environment */
  oatpp::base::Environment::init();

  /* Run App */
  run();

  /* Destroy oatpp Environment */
  oatpp::base::Environment::destroy();

  return 0;
}
