#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <net/if.h>

#define BUFFER_SIZE 4096

int getgatewayIP(char* resolve)
{
    int     received_bytes = 0, msg_len = 0, route_attribute_len = 0;
    int     sock = -1, msgseq = 0;
    struct  nlmsghdr *nlh, *nlmsg;
    struct  rtmsg *route_entry;
    struct  rtattr *route_attribute;
    char    gateway_address[INET_ADDRSTRLEN], interface[IF_NAMESIZE];
    char    msgbuf[BUFFER_SIZE], buffer[BUFFER_SIZE];
    char    *ptr = buffer;
    struct timeval tv;

    if ((sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE)) < 0) {
        perror("socket failed");
        return EXIT_FAILURE;
    }

    memset(msgbuf, 0, sizeof(msgbuf));
    memset(gateway_address, 0, sizeof(gateway_address));
    memset(interface, 0, sizeof(interface));
    memset(buffer, 0, sizeof(buffer));

    nlmsg = (struct nlmsghdr *)msgbuf;
    nlmsg->nlmsg_len = NLMSG_LENGTH(sizeof(struct rtmsg));
    nlmsg->nlmsg_type = RTM_GETROUTE; 
    nlmsg->nlmsg_flags = NLM_F_DUMP | NLM_F_REQUEST; 
    nlmsg->nlmsg_seq = msgseq++; 
    nlmsg->nlmsg_pid = getpid();
    tv.tv_sec = 1;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *)&tv, sizeof(struct timeval));
    if (send(sock, nlmsg, nlmsg->nlmsg_len, 0) < 0) {
        perror("send failed");
        return EXIT_FAILURE;
    }
    do
    {
        received_bytes = recv(sock, ptr, sizeof(buffer) - msg_len, 0);
        if (received_bytes < 0) {
            perror("Error in recv");
            return EXIT_FAILURE;
        }

        nlh = (struct nlmsghdr *) ptr;

        if((NLMSG_OK(nlmsg, received_bytes) == 0) ||
           (nlmsg->nlmsg_type == NLMSG_ERROR))
        {
            perror("Error in received packet");
            return EXIT_FAILURE;
        }

        if (nlh->nlmsg_type == NLMSG_DONE)
            break;
        else {
            ptr += received_bytes;
            msg_len += received_bytes;
        }

        if ((nlmsg->nlmsg_flags & NLM_F_MULTI) == 0)
            break;
    }
    while ((nlmsg->nlmsg_seq != msgseq) || (nlmsg->nlmsg_pid != getpid()));

    for ( ; NLMSG_OK(nlh, received_bytes); nlh = NLMSG_NEXT(nlh, received_bytes))
    {
        route_entry = (struct rtmsg *) NLMSG_DATA(nlh);

        if (route_entry->rtm_table != RT_TABLE_MAIN)
            continue;

        route_attribute = (struct rtattr *) RTM_RTA(route_entry);
        route_attribute_len = RTM_PAYLOAD(nlh);

        for ( ; RTA_OK(route_attribute, route_attribute_len);
              route_attribute = RTA_NEXT(route_attribute, route_attribute_len))
        {
            switch(route_attribute->rta_type) {
            case RTA_OIF:
                if_indextoname(*(int *)RTA_DATA(route_attribute), interface);
                break;
            case RTA_GATEWAY:
                inet_ntop(AF_INET, RTA_DATA(route_attribute),
                          gateway_address, sizeof(gateway_address));
                break;
            default:
                break;
            }
        }

        if ((*gateway_address) && (*interface)) {
			printf("Default Gateway: %s\n", gateway_address);
			sprintf(resolve,"%s", gateway_address);
            break;
        }
    }
    close(sock);
    return 0;
}

