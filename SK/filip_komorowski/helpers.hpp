#pragma once
#include <bits/stdc++.h>
#include <arpa/inet.h>

u_int16_t compute_icmp_checksum(const void *buff, int length);

int getTimeDifferenceInMilliseconds(std::chrono::steady_clock::time_point a, std::chrono::steady_clock::time_point b);