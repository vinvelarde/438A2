//-------------------------------------------------------------
// CSCE 438: Distributed objects programming
// HW2: An Improved Chat Room Service
// 
// Chat Client
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

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::Status;
using HW2::User;
using HW2::Action;
using HW2::SendMsg;
using HW2::Tweeter;

//this class handles RPCs
class TweeterClient {
	public:
		TweeterClient(std::shared_ptr<Channel> channel)
			: stub_(Tweeter::NewStub(channel)) {}
	
	//used for LIST command
	//UNDER CONSTRUCTION
	//Sends the client a list of all users indicating which ones
	//	the client is currently following
	std::string List(const std::string& u) {
		//set up RPC inputs
		User user, reply;
		user.set_username(u);
		ClientContext context;
		
		//loop through returning stream
		std::unique_ptr<ClientReader<User> > reader(stub_->List(&context, user));
		while(reader->Read(&reply)) {
			//print list of users from here
		}
		Status status = reader->Finish();
		
		//do something with return value
		if(status.ok()) {
			return reply.username();
		}
		else {
			std::cout << status.error_code() << ": " << status.error_message()
					<< std::endl;
			return "RPC failed";
		}
	}
	
	//used for JOIN and LEAVE commands
	//UNDER CONSTRUCTION
	//bool act represents whether to follow or unfollow
	//	true = follow, false = unfollow
	std::string Following(const std::string& currentUser, std::string& user, bool act) {
		//set up RPC inputs
		SendMsg msg;
		Action action;
		action.set_currentuser(currentUser);
		action.set_username(user);
		action.set_act(act);
		ClientContext context;
		
		//Following RPC
		Status status = stub_->Following(&context, action, &msg);
		
		//do something with the return value
		if(status.ok()) {
			return msg.message();
		}
		else {
			std::cout << status.error_code() << ": " << status.error_message()
					<< std::endl;
			return "RPC failed";
		}
	}
	
	//used for sending client or server messages
	//UNDER CONSTRUCTION
	std::string Msg(const std::string& user) {
		//set up RPC inputs
		SendMsg msg, reply;
		msg.set_sender(user);
		ClientContext context;
		
		//Msg RPC
		Status status = stub_->Msg(&context, msg, &reply);
		
		//do something with the return value
		if(status.ok()) {
			return reply.message();
		}
		else {
			std::cout << status.error_code() << ": " << status.error_message()
					<< std::endl;
			return "RPC failed";
		}
	}
		
	private:
		std::unique_ptr<Tweeter::Stub> stub_;
};

int main(int argc, char** argv) {
	//user must provide host name and port number as command line arguments
	if(argc < 4) {
		fprintf(stderr, "USAGE: %s <hostname> <port> <username>\n", argv[0]);
		exit(1);
	}
	
	//server address + port number from command line arguments
	std::string server_address(argv[1]);
	server_address += ":";
	server_address += argv[2];
	
	//create client channel
	TweeterClient tweeter(grpc::CreateChannel(
      server_address, grpc::InsecureChannelCredentials()));
	std::string user(argv[3]);
	
	//test that each RPC is working
	//-------------	List ------------------
	std::string reply = tweeter.Msg(user);
	std::cout << "List RPC response: " << reply << std::endl;
	
	//-------------	Following -------------
	reply = tweeter.Msg(user);
	std::cout << "Following RPC response: " << reply << std::endl;
	
	//-------------	Msg -------------------
	reply = tweeter.Msg(user);
	std::cout << "Msg RPC response: " << reply << std::endl;
	
	return 0;
}










