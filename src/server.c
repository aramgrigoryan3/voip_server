#include <stdio.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "server.h"

int init_server (struct server_ctx** srvr)
{
    *srvr = (struct server_ctx*)malloc(sizeof(struct server_ctx));
    if (srvr == NULL){
        printf("[DEBUG] [%d] [%s]: Server init set Error,  not valid\n", __LINE__, __FUNCTION__);
        exit(1);
    }
    return VOIP_SERVER_SUCCESS;
}

int prepare_server  (struct server_ctx** srvr, int port)
{
    (*srvr)->listen_port = port;
    (*srvr)->active_users = 0;
    long status = open_socket(srvr);
    status = bind_server(srvr);
    if (status != 0)
    {
        printf("[DEBUG] [%d] [%s]: Bind server set Error,  not valid\n", __LINE__, __FUNCTION__);
        exit(1);
    }
    return VOIP_SERVER_SUCCESS;
}   

int bind_server (struct server_ctx** server_ctx)
{
    /* Set socket option */
    (*server_ctx)->opt = 1;
    int sts = setsockopt((*server_ctx)->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &(*server_ctx)->opt, sizeof((*server_ctx)->opt));
    if (sts){
        printf("[DEBUG] [%d] [%s]: Socket options set Error,  not valid\n", __LINE__, __FUNCTION__);
        exit(1);
    }

    /* Allocate and set sockaddr struct options */
    (*server_ctx)->address = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
    if((*server_ctx)->address == NULL){
        printf("[DEBUG] [%d] [%s]: Address malloc Error,  not valid\n", __LINE__, __FUNCTION__);
        exit(1);
    }
    (*server_ctx)->address->sin_family = VOIP_SERVER_DOMAIN;
    (*server_ctx)->address->sin_addr.s_addr = INADDR_ANY;
    (*server_ctx)->address->sin_port = htons((*server_ctx)->listen_port);
    
    /* Bind newly created socket to address struct */
    socklen_t addrlen = sizeof(struct sockaddr_in); 
    sts = bind((*server_ctx)->server_fd, (struct sockaddr*)((*server_ctx)->address), addrlen);
    if (sts < 0){
        printf("[DEBUG] [%d] [%s]: Address bind Error,  not valid\n", __LINE__, __FUNCTION__);
        exit(1);        
    }

    return VOIP_SERVER_SUCCESS;
}

int set_socket_listen (struct server_ctx** server_ctx, unsigned long backlog)
{
    long sts = listen((*server_ctx)->server_fd, backlog);
    if (sts < 0){
        printf("[DEBUG] [%d] [%s]: Socket listen Error, sfd not valid\n", __LINE__, __FUNCTION__);
        exit(1);
    }
    return VOIP_SERVER_SUCCESS;
}

int set_socket_accept   (struct server_ctx** server_ctx, int* newfd, int (*callback)(int,char*))
{
    char buffer[256];
    int valread;
    socklen_t addrlen = sizeof(struct sockaddr_in);

    *newfd = accept((*server_ctx)->server_fd, (struct sockaddr*)((*server_ctx)->address), &addrlen);
    printf("Descriptor %d\n", *newfd);
    if(*newfd < 0){
        printf("[DEBUG] [%d] [%s]: Socket accept Error, sfd not valid\n", __LINE__, __FUNCTION__);
        exit(1);  
    }
    valread = read(*newfd, buffer, 256);
    (void)callback(valread, buffer);
    return VOIP_SERVER_SUCCESS;
}

int open_socket (struct server_ctx**  server_ctx)
{
    (*server_ctx)->server_fd = socket(VOIP_SERVER_DOMAIN, VOIP_SERVER_TYPE, VOIP_SERVER_PROTOCOL);
    if ((*server_ctx)->server_fd <= 0){
        printf("[DEBUG] [%d] [%s]: Socket creation Error, sfd not valid\n", __LINE__, __FUNCTION__);
        exit(1);
    }

    return VOIP_SERVER_SUCCESS;
}

int stop_server (struct server_ctx** server_ctx)
{
    long status = close((*server_ctx)->server_fd);
    if (status){
        printf("[DEBUG] [%d] [%s]: Server stop failed,  not valid\n", __LINE__, __FUNCTION__);
        exit(1);
    }
    return VOIP_SERVER_SUCCESS;
}

int clean_server(struct server_ctx** server_ctx)
{
    free((*server_ctx)->address);
    (*server_ctx)->address = NULL;
    
    free(*server_ctx);
    (*server_ctx) = NULL;

    if (*server_ctx != NULL){
        printf("[DEBUG] [%d] [%s]: Server free Error,  not valid\n", __LINE__, __FUNCTION__);
        exit(1);
    }
    return VOIP_SERVER_SUCCESS;
}



