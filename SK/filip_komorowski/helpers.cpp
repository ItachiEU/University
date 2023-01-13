// Filip Komorowski 315373
#include "helpers.hpp"

u_int16_t compute_icmp_checksum(const void *buff, int length)
{
   u_int32_t sum;
   const u_int16_t *ptr = (const u_int16_t *)buff;
   assert(length % 2 == 0);
   for (sum = 0; length > 0; length -= 2)
      sum += *ptr++;
   sum = (sum >> 16) + (sum & 0xffff);
   return (u_int16_t)(~(sum + (sum >> 16)));
}

int getTimeDifferenceInMilliseconds(std::chrono::steady_clock::time_point a, std::chrono::steady_clock::time_point b)
{
   return std::chrono::duration_cast<std::chrono::duration<int, std::milli>>(a - b).count();
}