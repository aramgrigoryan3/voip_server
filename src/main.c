#include "server.h"
#include <stdio.h>

int print_buffer (int buflen, char* buffer)
{
    printf("Length of buffer: %d\n", buflen);
    printf("Buffer : %s", buffer);
    return 0;
}

int main(int argc, char* argv[])
{
    struct server_ctx* ctx;
    int fd;
    int status;

    status = init_server(&ctx);
    status = prepare_server(&ctx, VOIP_SERVER_INFO_PORT);
    status = set_socket_listen(&ctx, VOIP_SERVER_BACKLOG);
    status = set_socket_accept(&ctx, &ctx->users[ctx->active_users], print_buffer);
    status = stop_server(&ctx);
    status = clean_server(&ctx);

    return 0;
}