// Filip Komorowski 315373
#include "receiver.hpp"
#include "sender.hpp"
#include "helpers.hpp"
#include "handlers.hpp"

int main(int argc, char *argv[])
{
   if (handleInputValidation(argc, argv) == -1)
      return EXIT_FAILURE;

   std::string target_ip = argv[1];
   int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

   if (sockfd < 0)
   {
      std::cerr << "Failed to create a socket." << std::endl;
      return EXIT_FAILURE;
   }

   fd_set descriptors;
   uint16_t pid = getpid();

   Sender sender(sockfd, target_ip, pid);
   Receiver receiver(sockfd, &descriptors, pid);

   for (int ttl = 1; ttl <= 30; ttl++)
   {
      auto startTime = std::chrono::steady_clock::now();

      int sendResult = sender.sendPackets(ttl);

      if (sendResult == -1)
         return EXIT_FAILURE;

      std::vector<Packet> packets;

      if (handleReceiving(&receiver, ttl, packets) == -1)
         return EXIT_FAILURE;

      handleResult(packets, ttl, startTime);

      if (packets.size() != 0 and packets[0].getICMPType() == ICMP_ECHOREPLY)
         break;
   }

   return EXIT_SUCCESS;
}