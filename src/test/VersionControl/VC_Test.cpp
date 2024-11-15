#include "VC_Test.hpp"

#include <iostream>
#include <memory>

#include "../../controller/VersionControl/VCController.hpp"
#include "../app/MyApiTestClient.hpp"
#include "../app/TestComponent.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

void VC_Test::onRun() {
    // Register test components
    TestComponent component;

    // Create client-server test runner
    oatpp::test::web::ClientServerTestRunner runner;

    // Get object mapper component
    OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);

    // Add VCController endpoints to the router of the test server
    runner.addController(std::make_shared<VCController>());

    // Run test
    runner.run([this, &runner] {
        // Get client connection provider for Api Client
        OATPP_COMPONENT(std::shared_ptr<oatpp::network::ClientConnectionProvider>, clientConnectionProvider);

        // Create Test API client
        auto client = MyApiTestClient::createShared(
            oatpp::web::client::HttpRequestExecutor::createShared(clientConnectionProvider), objectMapper
        );

        // Test 200 Success
        auto response = client->getVCQuestion();
        OATPP_ASSERT(response->getStatusCode() == 200);

        // Comment out the 500 scenario logic temporarily
        /*
        VC_MC_Question question;
        question.simulateError = true;
        auto errorResponse = client->getVCQuestion();  // Expecting 500
        OATPP_ASSERT(errorResponse->getStatusCode() == 500);
        */

    }, std::chrono::minutes(10) /* test timeout */);

    std::this_thread::sleep_for(std::chrono::seconds(1));  // wait for threads
}
