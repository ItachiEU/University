// Filip Komorowski 315373
#include "receiver.hpp"

// public

Receiver::Receiver(int sockfd, fd_set *descriptors, int pid)
{
   this->sockfd = sockfd;
   this->descriptors = descriptors;
   this->pid = pid;
}

std::vector<Packet> Receiver::receivePackets(int ttl, int count)
{
   auto startTime = std::chrono::steady_clock::now();
   int packetsReceived = 0;
   std::vector<Packet> receivedPackets;

   timeval tv;
   tv.tv_sec = 0;
   tv.tv_usec = 1000000;

   for (int t = 0; t < 1000 and packetsReceived < count; t = getTimeDifferenceInMilliseconds(std::chrono::steady_clock::now(), startTime))
   {
      FD_ZERO(this->descriptors);
      FD_SET(this->sockfd, this->descriptors);
      int ready = select(this->sockfd + 1, this->descriptors, NULL, NULL, &tv);
      tv.tv_usec = 1000000 - t * 1000; // make sure the whole process doesn't take more than 1 sec

      switch (ready)
      {
      case -1:
         throw "Something went wrong when selecting descriptor.";
         break;
      case 0: // no descriptor ready yet
         break;
      case 1:
         Packet packet;
         try
         {
            packet = this->getPacket();
         }
         catch (std::string err)
         {
            std::cerr << "Error in getPacket()." << std::endl;
            throw err;
         }
         if (packet.getID() == this->pid and packet.getTTL() == ttl)
         {
            receivedPackets.push_back(packet);
            packetsReceived++;
         }
      }
   }
   return receivedPackets;
}

int Receiver::getPID()
{
   return this->pid;
}

// private

Packet Receiver::getPacket()
{
   sockaddr_in sender;
   socklen_t sender_len = sizeof(sender);
   u_int8_t buffer[IP_MAXPACKET];
   ssize_t packet_len = recvfrom(sockfd, buffer, IP_MAXPACKET, 0, (sockaddr *)&sender, &sender_len);
   if (packet_len < 0)
      throw "Recvrom threw an error.";

   auto receiptTime = std::chrono::steady_clock::now();

   char sender_ip_str[20];
   inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, sizeof(sender_ip_str));
   ip *ip_header = (ip *)buffer;
   ssize_t ip_header_len = 4 * ip_header->ip_hl;
   auto *icmp_packet = buffer + ip_header_len;
   icmp *icmp_header = (icmp *)icmp_packet;

   if (icmp_header->icmp_type == ICMP_TIME_EXCEEDED)
   {
      icmp_packet += 1 + 1 + 2 + 4; // type, code, checksum, unused
      ip_header_len = ((ip *)icmp_packet)->ip_hl * 4;
      icmp_packet += ip_header_len; // ip header in original icmp message

      icmp *icmp_texc = (icmp *)icmp_packet;
      return Packet(sender_ip_str, icmp_texc->icmp_id, icmp_header->icmp_type, icmp_texc->icmp_seq, icmp_texc->icmp_seq / 3 + 1, receiptTime);
   }
   else if (icmp_header->icmp_type == ICMP_ECHOREPLY)
   {
      return Packet(sender_ip_str, icmp_header->icmp_id, icmp_header->icmp_type, icmp_header->icmp_seq, icmp_header->icmp_seq / 3 + 1, receiptTime);
   }
   return Packet();
}