#include "user.h"

int spawn_user (struct user_dsc** user_dsc, callback_t spawn_clbck)
{
    pthread_t user_thread;
    struct spawn_args_t spwn_args;
    
    // // if user needed data is invalid
    // // TOneverDO: add function check_user
    if ((*user_dsc)->sock_fd <= 0 || 
            (*user_dsc)->u_uid == VOIP_USER_INV)
    {
        return VOIP_SERVER_FAIL;
    }
    spwn_args.u_callback = spawn_clbck;
    spwn_args.u_desc = *user_dsc;

    pthread_create(&user_thread, NULL, user_accept, (void*)&spwn_args);
    pthread_join(user_thread, NULL);
    return VOIP_SERVER_SUCCESS;
}

void user_accept(void* spwn_args_v)
{
    struct spawn_args_t* spwn_args = (struct spawn_args_t*)spwn_args_v;
    struct user_dsc* user;
    int fd;
    char message_buf[55];
    unsigned long buflen;
    if (!spwn_args->u_desc)
    {
        perror("Invalid user\n");
        return;
    }
    if (!spwn_args->u_callback)
    {
        perror("Invalid callbackn pointer\n");
        return;
    }
    user = spwn_args->u_desc;
    printf("%p", spwn_args->u_callback);
    fd = user->sock_fd;
    while ((buflen = read(fd, message_buf, MESSAGE_MAX)) > 0)
    {
        spwn_args->u_callback(buflen, message_buf);
        memset(message_buf, 0, buflen);
    }
    
    /* when connection is closed free user_dsc memory*/
    free_user(&user);
    pthread_exit(VOIP_SERVER_SUCCESS);
}

int free_user(struct user_dsc** user)
{
    close((*user)->sock_fd);
    free(*user);
    return VOIP_SERVER_SUCCESS;
}