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





#ifndef __DK_NET_BUFFER_H__
#define __DK_NET_BUFFER_H__

#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <errno.h>

#include "dk_queue.h"
#include "dk_tree.h"

#include "dk_mempool.h"


enum rb_caller
{
    AT_APP,
    AT_MTCP
};


#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

/*----------------------------------------------------------------------------*/
typedef struct _dk_sb_manager
{
    size_t chunk_size;
    uint32_t cur_num;
    uint32_t cnum;
    struct _dk_mempool* mp;
    struct _dk_sb_queue* freeq;

} dk_sb_manager;

typedef struct _dk_send_buffer
{
    unsigned char* data;
    unsigned char* head;

    uint32_t head_off;
    uint32_t tail_off;
    uint32_t len;
    uint64_t cum_len;
    uint32_t size;

    uint32_t head_seq;
    uint32_t init_seq;
} dk_send_buffer;

#ifndef _INDEX_TYPE_
#define _INDEX_TYPE_
typedef uint32_t index_type;
typedef int32_t signed_index_type;
#endif


typedef struct _dk_sb_queue
{
    index_type _capacity;
    volatile index_type _head;
    volatile index_type _tail;

    dk_send_buffer* volatile* _q;
} dk_sb_queue;

#define NextIndex(sq, i)    (i != sq->_capacity ? i + 1: 0)
#define PrevIndex(sq, i)    (i != 0 ? i - 1: sq->_capacity)
#define MemoryBarrier(buf, idx) __asm__ volatile("" : : "m" (buf), "m" (idx))



/** rb frag queue **/

typedef struct _dk_rb_frag_queue
{
    index_type _capacity;
    volatile index_type _head;
    volatile index_type _tail;

    struct _dk_fragment_ctx* volatile* _q;
} dk_rb_frag_queue;


/** ring buffer **/

typedef struct _dk_fragment_ctx
{
    uint32_t seq;
    uint32_t len:31,
             is_calloc:1;
    struct _dk_fragment_ctx* next;
} dk_fragment_ctx;

typedef struct _dk_ring_buffer
{
    u_char* data;
    u_char* head;

    uint32_t head_offset;
    uint32_t tail_offset;

    int merged_len;
    uint64_t cum_len;
    int last_len;
    int size;

    uint32_t head_seq;
    uint32_t init_seq;

    dk_fragment_ctx* fctx;
} dk_ring_buffer;

typedef struct _dk_rb_manager
{
    size_t chunk_size;
    uint32_t cur_num;
    uint32_t cnum;

    dk_mempool* mp;
    dk_mempool* frag_mp;

    dk_rb_frag_queue* free_fragq;
    dk_rb_frag_queue* free_fragq_int;

} dk_rb_manager;



typedef struct _dk_stream_queue
{
    index_type _capacity;
    volatile index_type _head;
    volatile index_type _tail;

    struct _dk_tcp_stream* volatile* _q;
} dk_stream_queue;

typedef struct _dk_stream_queue_int
{
    struct _dk_tcp_stream** array;
    int size;

    int first;
    int last;
    int count;

} dk_stream_queue_int;


dk_sb_manager* dk_sbmanager_create ( size_t chunk_size, uint32_t cnum );
dk_rb_manager* RBManagerCreate ( size_t chunk_size, uint32_t cnum );


dk_stream_queue* CreateStreamQueue ( int capacity );


dk_stream_queue_int* CreateInternalStreamQueue ( int size );
void DestroyInternalStreamQueue ( dk_stream_queue_int* sq );


dk_send_buffer* SBInit ( dk_sb_manager* sbm, uint32_t init_seq );
void SBFree ( dk_sb_manager* sbm, dk_send_buffer* buf );
size_t SBPut ( dk_sb_manager* sbm, dk_send_buffer* buf, const void* data, size_t len );
int SBEnqueue ( dk_sb_queue* sq, dk_send_buffer* buf );
size_t SBRemove ( dk_sb_manager* sbm, dk_send_buffer* buf, size_t len );


size_t RBRemove ( dk_rb_manager* rbm, dk_ring_buffer* buff, size_t len, int option );
int RBPut ( dk_rb_manager* rbm, dk_ring_buffer* buff,
            void* data, uint32_t len, uint32_t cur_seq );
void RBFree ( dk_rb_manager* rbm, dk_ring_buffer* buff );

int StreamInternalEnqueue ( dk_stream_queue_int* sq, struct _dk_tcp_stream* stream );
struct _dk_tcp_stream* StreamInternalDequeue ( dk_stream_queue_int* sq );


/*** ******************************** sb queue ******************************** ***/


dk_sb_queue* CreateSBQueue ( int capacity );
int StreamQueueIsEmpty ( dk_stream_queue* sq );


dk_send_buffer* SBDequeue ( dk_sb_queue* sq );

dk_ring_buffer* RBInit ( dk_rb_manager* rbm, uint32_t init_seq );


struct _dk_tcp_stream* StreamDequeue ( dk_stream_queue* sq );
int StreamEnqueue ( dk_stream_queue* sq, struct _dk_tcp_stream* stream );

void DestroyStreamQueue ( dk_stream_queue* sq );



#endif



