// Filip Komorowski 315373
#include "packet.hpp"

// public

Packet::Packet()
{
   this->sender_ip = "";
   this->icmp_type = 0;
   this->id = 0;
   this->seq_number = 0;
   this->ttl = 0;
}

Packet::Packet(std::string ip, int id, uint8_t icmp_type, int seq_number, int ttl, std::chrono::steady_clock::time_point time)
{
   this->sender_ip = ip;
   this->icmp_type = icmp_type;
   this->id = id;
   this->seq_number = seq_number;
   this->ttl = ttl;
   this->time_received = time;
}
void Packet::debug()
{
   std::cout << "Packet: " << this->sender_ip << " icmp type: " << (bool)(this->icmp_type == ICMP_TIME_EXCEEDED) << " id: " << this->id << " ttl: " << this->ttl << " seq: " << this->seq_number << std::endl;
}

int Packet::getID()
{
   return this->id;
}

int Packet::getTTL()
{
   return this->ttl;
}

std::string Packet::getSenderIP()
{
   return this->sender_ip;
}

uint8_t Packet::getICMPType()
{
   return this->icmp_type;
}

std::chrono::steady_clock::time_point Packet::getTimePoint()
{
   return this->time_received;
}
// private