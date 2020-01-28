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
 *
 *
 *
 */


#ifndef __DK_NET_ADDR_H__
#define __DK_NET_ADDR_H__

#include "ndk_queue.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <netinet/in.h>


#define DK_MIN_PORT            1025
#define DK_MAX_PORT            65535

#ifndef INPORT_ANY
#define INPORT_ANY  (uint16_t)0
#endif


typedef struct _dk_addr_entry
{
    struct sockaddr_in addr;
    TAILQ_ENTRY ( _dk_addr_entry ) addr_link;
} dk_addr_entry;

typedef struct _dk_addr_map
{
    dk_addr_entry* addrmap[NTY_MAX_PORT];
} dk_addr_map;

typedef struct _dk_addr_pool
{
    dk_addr_entry* pool;
    dk_addr_map* mapper;

    uint32_t addr_base;

    int num_addr;
    int num_entry;
    int num_free;
    int num_used;

    pthread_mutex_t lock;
    TAILQ_HEAD (, _dk_addr_entry ) free_list;
    TAILQ_HEAD (, _dk_addr_entry ) used_list;
} dk_addr_pool;


dk_addr_pool* CreateAddressPool ( in_addr_t addr_base, int num_addr );
dk_addr_pool* CreateAddressPoolPerCore ( int core, int num_queues,
                                          in_addr_t saddr_base, int num_addr, in_addr_t daddr, in_port_t dport );

void DestroyAddressPool ( dk_addr_pool* ap );
int FetchAddress ( dk_addr_pool* ap, int core, int num_queues,
                   const struct sockaddr_in* daddr, struct sockaddr_in* saddr );

int FetchAddressPerCore ( dk_addr_pool* ap, int core, int num_queues,
                          const struct sockaddr_in* daddr, struct sockaddr_in* saddr );

int FreeAddress ( dk_addr_pool* ap, const struct sockaddr_in* addr );


int GetRSSCPUCore ( in_addr_t sip, in_addr_t dip,
                    in_port_t sp, in_port_t dp, int num_queues, uint8_t endian_check );


#endif


