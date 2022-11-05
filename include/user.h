#ifndef __USER__H__
#define __USER__H__

#include "constants.h"
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef int(*callback_t)(int, char*);

struct spawn_args_t
{
    struct user_dsc* u_desc;
    callback_t u_callback;
};

struct user_dsc
{
    int sock_fd;
    int u_uid;  
    pthread_t* th;
};

/**
 * @brief Get all user needed data, except thread_descriptor;
 * Thread for another user will be spawned here
 * 
 * @param user_dsc user descriptor user unit on server side.
 * @param callback function pointer which will be invoked apart from 
 * main thread
 * @return int sucess code or fail code
 */
int spawn_user (struct user_dsc** user_dsc, callback_t spawn_clbck);

void user_accept(void* spwn_args_v);

int free_user(struct user_dsc** user);

#endif //__USER__H__