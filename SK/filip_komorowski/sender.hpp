#pragma once
#include <bits/stdc++.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <unistd.h>

class Sender
{
public:
   Sender(int sockfd, std::string target_ip, int pid);

   int sendPackets(int ttl, int count = 3);
   int getPID();

private:
   int sockfd;
   int pid;
   std::string target_ip;
   int sendPacket(int ttl, int seq);
   icmp constructHeaderICMP(int seq);
};