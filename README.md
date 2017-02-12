# CSCE 438 - HW2: An Improved Chat Room Service
Vincent Velarde, Kyle Rowland
February 2017

Files: fb.proto, fbc.cpp, fbsd.cpp, Makefile

NOTES:
  -This project roughly mimicks the functionality of Twitter
  -Use "make all" to compile and "make clean" to clear everything but source files
  -Run server with "./server <port>"
  -Run client with "./client <hostname> <port> <username>"

##fbc.cpp - client code
Connects to server and waits for user to issue commands, then takes some action based on the command:
- If user issues LIST command, the "List (User) returns (stream user)" RPC is called.
- If the user issues JOIN or LEAVE command, the "Following (Action) returns (SendMsg)" RPC is called.
- If the user issues CHAT command, the client leaves command mode and enters chat mode. In chat mode the "Msg (SendMSG) returns (SendMSG)"    RPC is called for any input.
