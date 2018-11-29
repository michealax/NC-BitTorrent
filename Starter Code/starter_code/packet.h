#ifndef PACKET_H
#define PACKET_H

#include "queue.h"
#include "chunk.h"
#include "stdio.h"
#include "stdlib.h"
#include "timer.h"
#include "spniff.h"
#include <sys/socket.h>

#define PACKETLEN 1500
#define HEADERLEN 16
#define DATALEN (PACKETLEN-HEADERLEN)
#define CHUNK_MAXNUM 74
#define BUFFERSIZE 255
#define CHUNK_SIZE (1<<19) //512Kbytes, required 19 bits.
#define MAGICNUM 15441
#define VERSION 1

enum PKT_TYPE{
	PKT_WHOHAS = 0, PKT_IHAVE, PKT_GET, PKT_DATA, PKT_ACK, PKT_DENIED
};

typedef header_s{
	short magic_num;
	char version;
	char pkt_type;
	short header_len;
	short packet_len;
	u_int seq_num;
	u_int ack_num;
} header_t;

typedef struct data_pkt_s{
	header_t header;
	char data[DATALEN];
} data_pkt_t;

void init_pkt(data_pkt_t *, char, short, short, u_int, u_int);
data_pkt_t *make_pkt(char, char, short, short, u_int, u_int);
void free_pkt(data_pkt_t *);

data_pkt_t *make_pkt_whohas(short, void *);
data_pkt_t *make_pkt_ihave(short, void *);
data_pkt_t *make_pkt_get(short, char *);
data_pkt_t *make_pkt_data(short, u_int, u_int, char *);
data_pkt_t *make_pkt_ack(u_int, u_int);
data_pkt_t *make_pkt_denied();

void send_pkt(int, data_pkt_t *, struct sockaddr *);

int pkt_parse(void *);

void print_pkt(data_pkt_t *);

#endif ///~ PACKET_H
