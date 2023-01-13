#pragma once
#include "receiver.hpp"

bool isValidIP(std::string ip);

int handleInputValidation(int argc, char *argv[]);

int handleReceiving(Receiver *receiver, int ttl, std::vector<Packet> &packets);

void handleResult(std::vector<Packet> &packets, int ttl, std::chrono::_V2::steady_clock::time_point startTime);