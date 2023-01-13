// Filip Komorowski 315373

#include "sender.hpp"
#include "helpers.hpp"

// public
Sender::Sender(int sockfd, std::string target_ip, int pid)
{
   this->sockfd = sockfd;
   this->target_ip = target_ip;
   this->pid = pid;
}

int Sender::sendPackets(int ttl, int count)
{
   for (int i = 0; i < count; i++)
   {
      int res = this->sendPacket(ttl, (ttl - 1) * 3 + i);
      if (res == -1)
         return -1;
   }
   return 0;
}

int Sender::getPID()
{
   return this->pid;
}

// private

int Sender::sendPacket(int ttl, int seq)
{
   sockaddr_in recipient;
   bzero(&recipient, sizeof(recipient));
   recipient.sin_family = AF_INET;
   inet_pton(AF_INET, this->target_ip.c_str(), &recipient.sin_addr);
   icmp header = this->constructHeaderICMP(seq);
   int setsockoptvalue = setsockopt(this->sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));
   if (setsockoptvalue == -1)
   {
      std::cerr << "Something went wrong with setting socket options." << std::endl;
      return -1;
   }
   ssize_t bytes_sent = sendto(this->sockfd, &header, sizeof(header), 0, (sockaddr *)&recipient, sizeof(recipient));
   if (bytes_sent < 0)
   {
      std::cerr << "Sending packet unsuccessful. " << std::endl;
      return -1;
   }
   return 0;
}

icmp Sender::constructHeaderICMP(int seq)
{
   icmp header;
   header.icmp_type = ICMP_ECHO;
   header.icmp_code = 0;
   header.icmp_hun.ih_idseq.icd_id = this->pid;
   header.icmp_hun.ih_idseq.icd_seq = seq;
   header.icmp_cksum = 0;
   header.icmp_cksum = compute_icmp_checksum((u_int16_t *)&header, sizeof(header));
   return header;
}