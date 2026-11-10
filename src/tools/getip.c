#define _POSIX_C_SOURCE 200112L
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <stdio.h>

#include <error.h>

#include <memory.h>

#include <stddef.h>

int main(int argc, char *argv[])
{
    struct addrinfo *result;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    if (getaddrinfo("google.com", NULL, &hints, &result) != 0)
    {
        perror("Failed to get address info");
        return -1;
    }

    do
    {
        char ip[INET6_ADDRSTRLEN];
        void *addr;
        if (result->ai_family == AF_INET)
            addr = &((struct sockaddr_in *)result->ai_addr)->sin_addr;
        else
            addr = &((struct sockaddr_in6 *)result->ai_addr)->sin6_addr;

        inet_ntop(result->ai_family, addr, ip, sizeof ip);
        printf("IP: %s\n", ip);
    } while ((result = result->ai_next) != NULL);
}