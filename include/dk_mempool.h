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



#ifndef __DK_NET_MEMPOOL_H__
#define __DK_NET_MEMPOOL_H__


enum
{
    MEM_NORMAL,
    MEM_HUGEPAGE
};


typedef struct _dk_mem_chunk
{
    int mc_free_chunks;
    struct _dk_mem_chunk* next;
} dk_mem_chunk;

typedef struct _dk_mempool
{
    u_char* mp_startptr;
    dk_mem_chunk* mp_freeptr;
    int mp_free_chunks;
    int mp_total_chunks;
    int mp_chunk_size;
    int mp_type;
} dk_mempool;


dk_mempool* dk_mempool_create ( int chunk_size, size_t total_size, int is_hugepage );

void dk_mempool_destory ( dk_mempool* mp );

void* dk_mempool_alloc ( dk_mempool* mp );

void dk_mempool_free ( dk_mempool* mp, void* p );






#endif



