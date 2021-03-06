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



#ifndef __DK_NET_ARP_H__
#define __DK_NET_ARP_H__

#include "dk_header.h"

#define MAX_ARPENTRY    256

typedef struct _dk_arp_entry
{
    uint32_t ip;
    int8_t prefix;
    uint32_t ip_mask;
    uint32_t ip_masked;
    unsigned char haddr[ETH_ALEN];
} dk_arp_entry;

typedef struct _dk_arp_table
{
    dk_arp_entry* entry;
    int entries;
} dk_arp_table;

unsigned char* GetDestinationHWaddr ( uint32_t dip );
int GetOutputInterface ( uint32_t daddr );

int dk_arp_register_entry ( uint32_t ip, const unsigned char* haddr );
int dk_arp_process ( dk_nic_context* ctx, unsigned char* stream );
int dk_arp_init_table ( void );

int str2mac ( char* mac, char* str );


#endif



