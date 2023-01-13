// Filip Komorowski 315373
#include "handlers.hpp"

// http://www.zedwood.com/article/cpp-is-valid-ip-address-ipv4-ipv6
bool isValidIP(std::string ip)
{
   struct sockaddr_in sa;
   return inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr)) == 1;
}

int handleInputValidation(int argc, char *argv[])
{
   if (argc != 2)
   {
      std::cerr << "Traceroute accepts exactly one argument: target ip address." << std::endl;
      return -1;
   }
   if (!isValidIP(argv[1]))
   {
      std::cerr << "This isn't a valid IP address." << std::endl;
      return -1;
   }
   return 0;
}

int handleReceiving(Receiver *receiver, int ttl, std::vector<Packet> &packets)
{
   try
   {
      packets = receiver->receivePackets(ttl);
   }
   catch (std::string err)
   {
      std::cerr << err << std::endl;
      return -1;
   }
   return 0;
}

void handleResult(std::vector<Packet> &packets, int ttl, std::chrono::_V2::steady_clock::time_point startTime)
{
   switch (packets.size())
   {
   case 0:
      std::cout << ttl << ". *" << std::endl;
      break;

   case 3:
   {
      int avg_time = 0;
      for (auto p : packets)
         avg_time += getTimeDifferenceInMilliseconds(p.getTimePoint(), startTime);
      avg_time /= 3;
      std::cout << ttl << ". " << packets[0].getSenderIP() << " " << avg_time << " ms" << std::endl;
   }
   break;

   default:
      std::cout << ttl << ". " << packets[0].getSenderIP() << " ???" << std::endl;
      break;
   }
}