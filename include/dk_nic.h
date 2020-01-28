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





#ifndef __DK_NET_NIC_H__
#define __DK_NET_NIC_H__


#include "dk_tcp.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>



#define NETMAP_WITH_LIBS

#include <net/netmap_user.h>
#pragma pack(1)




#define MAX_PKT_BURST   64
#define MAX_DEVICES     16

#define EXTRA_BUFS      512

#define ETHERNET_FRAME_SIZE     1514
#define ETHERNET_HEADER_LEN     14

#define IDLE_POLL_COUNT         10
#define IDLE_POLL_WAIT          1

typedef struct _dk_nic_context
{
    struct nm_desc* nmr;
    unsigned char snd_pktbuf[ETHERNET_FRAME_SIZE];
    unsigned char* rcv_pktbuf[MAX_PKT_BURST];
    uint16_t rcv_pkt_len[MAX_PKT_BURST];
    uint16_t snd_pkt_size;
    uint8_t dev_poll_flag;
    uint8_t idle_poll_count;
} dk_nic_context;


typedef struct _dk_nic_handler
{
    int ( *init ) ( dk_thread_context* ctx, const char* ifname );
    int ( *read ) ( dk_nic_context* ctx, unsigned char** stream );
    int ( *write ) ( dk_nic_context* ctx, const void* stream, int length );
    unsigned char* ( *get_wbuffer ) ( dk_nic_context* ctx, int nif, uint16_t pktsize );
} dk_nic_handler;

unsigned char* dk_nic_get_wbuffer ( dk_nic_context* ctx, int nif, uint16_t pktsize );
unsigned char* dk_nic_get_rbuffer ( dk_nic_context* ctx, int nif, uint16_t* len );

int dk_nic_send_pkts ( dk_nic_context* ctx, int nif );
int dk_nic_recv_pkts ( dk_nic_context* ctx, int ifidx );

int dk_nic_read ( dk_nic_context* ctx, unsigned char** stream );
int dk_nic_write ( dk_nic_context* ctx, const void* stream, int length );



int dk_nic_init ( dk_thread_context* tctx, const char* ifname );
int dk_nic_select ( dk_nic_context* ctx );


#if 0
extern dk_nic_handler dk_netmap_handler;
static dk_nic_handler* dk_current_handler = &dk_netmap_handler;


#define NTY_NIC_INIT(x, y)              dk_current_handler->init(x, y)
#define NTY_NIC_WRITE(x, y, z)          dk_current_handler->write(x, y, z)
#define NTY_NIC_READ(x, y)              dk_current_handler->read(x, y)
#define NTY_NIC_GET_WBUFFER(x, y, z)    dk_current_handler->get_wbuffer(x, y, z)
#endif


#endif



