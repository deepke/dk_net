/*
 * MIT License
 *
 * Copyright (c) [2018] [WangBoJing]

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */



#ifndef __DK_NET_SOCKET_H__
#define __DK_NET_SOCKET_H__


#include "dk_buffer.h"
#include "dk_tcp.h"
#include "dk_config.h"

#include <pthread.h>


typedef struct _dk_socket_map
{
    int id;
    int socktype;
    uint32_t opts;

    struct sockaddr_in s_addr;

    union
    {
        struct _dk_tcp_stream* stream;
        struct _dk_tcp_listener* listener;
#if NTY_ENABLE_EPOLL_RB
        void* ep;
#else
        struct _dk_epoll* ep;
#endif
        //struct pipe *pp;
    };

    uint32_t epoll;
    uint32_t events;
    uint64_t ep_data;

    TAILQ_ENTRY ( _dk_socket_map ) free_smap_link;
} dk_socket_map; //__attribute__((packed))


enum dk_socket_opts
{
    NTY_TCP_NONBLOCK = 0x01,
    NTY_TCP_ADDR_BIND = 0x02,
};

dk_socket_map* dk_allocate_socket ( int socktype, int need_lock );
void dk_free_socket ( int sockid, int need_lock );
dk_socket_map* dk_get_socket ( int sockid );


/*
 * rebuild socket module for support 10M
 */
#if NTY_ENABLE_SOCKET_C10M


struct _dk_socket
{
    int id;
    int socktype;

    uint32_t opts;
    struct sockaddr_in s_addr;

    union
    {
        struct _dk_tcp_stream* stream;
        struct _dk_tcp_listener* listener;
        void* ep;
    };
    struct _dk_socket_table* socktable;
};


struct _dk_socket_table
{
    size_t max_fds;
    int cur_idx;
    struct _dk_socket** sockfds;
    unsigned char* open_fds;
    pthread_spinlock_t lock;
};

struct _dk_socket* dk_socket_allocate ( int socktype );

void dk_socket_free ( int sockid );

struct _dk_socket* dk_socket_get ( int sockid );

struct _dk_socket_table* dk_socket_init_fdtable ( void );

int dk_socket_close_listening ( int sockid );

int dk_socket_close_stream ( int sockid );



#endif

#endif


