#pragma once
#include <bits/stdc++.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include "packet.hpp"
#include "helpers.hpp"

class Receiver
{
public:
   Receiver(int sockfd, fd_set *descriptors, int pid);
   std::vector<Packet> receivePackets(int ttl, int count = 3);
   int getPID();

private:
   fd_set *descriptors;
   int sockfd;
   int pid;
   Packet getPacket();
};