//-------------------------------------------------------------
// CSCE 438: Distributed objects programming
// HW2: An Improved Chat Room Service
// 
// Chat Server
// Vincent Velarde, Kyle Rowland
// February 2017
//
// NOTES:
// 	-Expands upon previous homework in functionality and by
// 		introducing RPCs and Protocol Buffers
//
//	-Project roughly mimicks functionality of Twitter
//
//	-This code is still UNDER CONSTRUCTION
//
//-------------------------------------------------------------

#include <iostream>
#include <memory>
#include <string>
#include <grpc++/grpc++.h>

#include "fb.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerWriter;
using grpc::Status;
using HW2::User;
using HW2::Action;
using HW2::SendMsg;
using HW2::Tweeter;

//this class handles the RPCs
class masterServer final : public Tweeter::Service {
	//LIST command
	//UNDER CONSTRUCTION
	//Sends the client a list of all users indicating which ones
	//	the client is currently following
	Status List(ServerContext* context, const HW2::User* user,
				ServerWriter<User>* writer) override {
		User u;
		u.set_username("UNDER CONSTRUCTION");
		writer->Write(u);
		
		return Status::OK;
	}
	
	//JOINT and LEAVE commands
	//UNDER CONSTRUCTION
	//Follows or unfollows a user for the client
	Status Following(ServerContext* context, const Action* action,
							SendMsg* msg) override {
		msg->set_sender("SERVER: ");
		msg->set_message("UNDER CONSTRUCTION");
		return Status::OK;
	}
	
	//Used for sending client or server messages
	//UNDER CONSTRUCTION
	Status Msg(ServerContext* context, const SendMsg* msg,
				SendMsg* confirm) override {
		confirm->set_sender("SERVER: ");
		confirm->set_message("UNDER CONSTRUCTION");
		return Status::OK;
	}
};

//setup and run the server
void runServer(char* p) {
	//server address and port number from command line argument
	std::string server_address("0.0.0.0:");
	server_address += p;
	
	masterServer service;
	
	ServerBuilder builder;
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);
	std::unique_ptr<Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << server_address << std::endl;
	
	server->Wait();
}

int main(int argc, char** argv) {
	//user must provide port number as command line argument
	if(argc < 2) {
		fprintf(stderr, "USAGE: %s <port>\n", argv[0]);
		exit(1);
	}
	
	runServer(argv[1]);
	
	return 0;
}
