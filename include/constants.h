#ifndef __VOIP__CONSTANTS__
#define __VOIP__CONSTANTS__

#define VOIP_SERVER_SUCCESS 0
#define VOIP_SERVER_FAIL    1
#define MESSAGE_MAX         65535
#define VOIP_SERVER_BACKLOG 255
#define VOIP_SERVER_DOMAIN  AF_INET    // Network connections via IPv4
#define VOIP_SERVER_TYPE    SOCK_STREAM //Specifies UDP-family 
#define VOIP_SERVER_PROTOCOL 0 //Internet Protocol
#define VOIP_SERVER_INFO_PORT 10001
#define VOIP_USER_INV -1

#endif //__VOIP__CONSTANTS__