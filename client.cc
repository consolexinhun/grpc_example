#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "gen_code/test.grpc.pb.h"

#include <iostream>
#include <memory>
#include <string>

class TestClient {
public:
    TestClient(std::shared_ptr<grpc::Channel> channel) : stub_(test::TestService::NewStub(channel)) {

    }

    void GetReplyMsg() {
        test::Data data;
        test::MsgReply msg_reply;
        data.set_data(123);
        GetOneData(data, &msg_reply);
    }

private:
    bool GetOneData(const test::Data& data, test::MsgReply* msg_reply) {
        grpc::ClientContext context;
        grpc::Status status = stub_->getData(&context, data, msg_reply);

        if (!status.ok()) {
            std::cout << "get data rpc failed" << std::endl;
            return false;
        }
        if (msg_reply->message().empty()) {
            std::cout << "message empty" << std::endl;
            return false;
        }
        std::cout << "MsgReply: " << msg_reply->message();
        return true;
    }
    std::unique_ptr<test::TestService::Stub> stub_;
};

int main(int argc, char** argv) {
    TestClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    std::cout << "-------------------------" << std::endl;

    client.GetReplyMsg();
    return 0;
}