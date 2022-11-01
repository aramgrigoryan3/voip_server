#ifndef __SERVER__H__ 
#define __SERVER__H__


#define VOIP_SERVER_SUCCESS 0
#define VOIP_SERVER_FAIL    1
#define VOIP_SERVER_BACKLOG 255
#define VOIP_SERVER_DOMAIN  AF_INET    // Network connections via IPv4
#define VOIP_SERVER_TYPE    SOCK_STREAM //Specifies UDP-family 
#define VOIP_SERVER_PROTOCOL 0 //Internet Protocol
#define VOIP_SERVER_INFO_PORT 10001
struct server_ctx {
    int listen_port;
    int running;
    int active_users;
    int server_fd;
    int users[VOIP_SERVER_BACKLOG];
    struct sockaddr_in* address;
    int opt;
};

int init_server         (struct server_ctx** srvr);

int prepare_server      (struct server_ctx** srvr, int port);

int bind_server         (struct server_ctx** server_ctx);

int set_socket_listen   (struct server_ctx** server_ctx, unsigned long backlog);

int set_socket_accept   (struct server_ctx** server_ctx, int* newfd, int (*callback)(int,char*));

int open_socket         (struct server_ctx**  server_ctx);

int stop_server         (struct server_ctx**  server_ctx);

int clean_server        (struct server_ctx**  server_ctx);


#endif /* __SERVER__H__ */