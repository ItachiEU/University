#pragma once
#include <bits/stdc++.h>
#include <netinet/ip_icmp.h>

class Packet
{
public:
   Packet();
   Packet(std::string ip, int id, uint8_t icmp_type, int seq_number, int ttl, std::chrono::steady_clock::time_point time);

   int getID();
   int getTTL();
   std::string getSenderIP();
   uint8_t getICMPType();
   std::chrono::steady_clock::time_point getTimePoint();
   void debug();

private:
   std::string sender_ip;
   int id;
   uint8_t icmp_type;
   int seq_number;
   int ttl;
   std::chrono::steady_clock::time_point time_received;
};