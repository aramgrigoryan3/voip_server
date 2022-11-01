#include "server.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    struct server_ctx* ctx;
    int fd;

    int status = init_server(&ctx);
    printf("status %d\n", status);
    status = prepare_server(&ctx, 9888);
    status = set_socket_listen(&ctx, VOIP_SERVER_BACKLOG);
    status = set_socket_accept(&ctx, &ctx->users[ctx->active_users]);

    status = stop_server(&ctx);
    status = clean_server(&ctx);
    return 0;
}