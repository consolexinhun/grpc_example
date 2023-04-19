#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include <grpcpp/security/server_credentials.h>

#include "gen_code/test.grpc.pb.h"

#include <string>
#include <iostream>
#include <memory>

class Test final: public test::TestService::Service {
public:
    grpc::Status getData(grpc::ServerContext* context, const test::Data* data, test::MsgReply* msg) override {
        std::cout << "get data : " << data->data() << std::endl;
        std::string tmp {"data received 12345"};
        msg->set_message(tmp);
        return grpc::Status::OK;
    }
};

void RunServer();

int main(int argc, char** argv) {
    RunServer();
    return 0;
}

void RunServer() {
    std::string server_addr {"0.0.0.0:50051"};
    Test service;
    grpc::ServerBuilder builder;

    builder.AddListeningPort(server_addr, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    std::cout << "Server listening on" << server_addr << std::endl;
    server->Wait();
}
