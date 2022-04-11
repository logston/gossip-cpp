#include <iostream>
#include <vector>
#include <string>

#include <grpcpp/grpcpp.h>
#include "protos/gossip.pb.h"
#include "protos/gossip.grpc.pb.h"

class Node {
 public:
  std::string location;
};

class State {
 public:
  Node* self;
  std::vector<Node*> nodes;
};

int send(State* state) {
  gossippb::Status* status = new gossippb::Status();

  for (int i = 0; i < state->nodes.size(); i++) {
    gossippb::Node* n = status->add_nodes();
    n->set_location(state->nodes[i]->location);
  }

  google::protobuf::Timestamp* ts = new google::protobuf::Timestamp();
  ts->set_seconds(time(NULL));
  ts->set_nanos(0);
  status->set_allocated_timestamp(ts);

  std::cout << status->DebugString() << std::endl;

  return 0;
}

class GossipImpl final : public gossippb::Gossip::Service {
	grpc::Status GetStatus(
		grpc::ServerContext* context, 
		const gossippb::Status* inStatus, 
		gossippb::Status* outStatus) override {

		return grpc::Status::OK;
	}
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  GossipImpl service;

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}

int main(int argc, char* argv[]) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  State* state = new State();
  state->self = new Node();
  state->self->location = "1.2.3.4";

  Node* n1 = new Node();
  n1->location = "5.6.7.8";
  state->nodes.push_back(n1);
  state->nodes.push_back(state->self);

  send(state);

  RunServer();

  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
