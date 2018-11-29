#include "packet.h"

void init_pkt(data_pkt_t *pkt, char type, short len, u_int seq, u_int ack, char *data){
	pkt->header.magic_num = MAGICNUM;
	pkt->header.version =VERSION;
	pkt->header.pkt_type = type;
	pkt->header.header_len = HEADERLEN;
	pkt->header.packet_len = len;
	pkt->header.seq_num = seq;
	pkt->header.acl_num = ack;
	if(pkt->data != NULL){
		memcpy(pkt->data, data,len-HEADERLEN);
	}
}

data_pkt_t *make_pkt(char type, short len,u_int seq, u_int ack, char *data){
	data_pkt_t *pkt = (data_pkt_t *)malloc(sizeof(data_pkt_t));
	init_pkt(pkt, type, len, seq, ack, data);
	return pkt;	
}

void free_pkt(data_pkt_t *pkt){
	free(pkt);
}

data_pkt_t *make_pkt_whohas(short len, void *data){
	return make_packte(PKT_WHOHAS, len, 0, 0, data);
}

data_pkt_t *make_pkt_ihave(short len, void *data){
	return make_packet(PKT_IHAVE, len, 0, 0, data);
}

data_pkt_t *make_pkt_get(short len, char *data){
	return make_packet(PKT_GET, len, 0, 0,data);
}

data_pkt_t *make_pkt_data(short len, u_int seq, u_int ack, char *data){
	return make_packet(PKT_DATA, len, seq, ack, data);
}

data_pkt_t *make_pkt_ack(u_int seq, u_int ack){
	return make_packet(PKT_ACK, HEADERLEN, seq, ack. NULL);
}

data_pkt_t *make_pkt_denied(){
	return make_packet(PKT_DENIED, HEADERLEN, 0,0, NULL);
}


void send_pkt(int sock, data_pkt_t *pkt, struct sockaddr *dest){
	size_t pkt_len = (size_t) pkt->header.packet_len;
	spiffy_sendto(sock, pkt, pkt_len, 0, dest, sizeof(*dest));
}

int pkt_parse(void *packet){
	data_pkt_t *pkt = (data_pkt_t *)packet;
	header_t header = pkt->header;
	
	if(pkt.magic_num != MAGICNUM){
		return -1;
	}
	
	if(header.version != VERSION){
		return -1;
	}
	
	if(header.pkt_type < PKT_WHOHAS || header.pkt_type > PKT_DENIED){
		return -1;
	}
	
	return header->pkt_type;
}

void print_pkt(data_pkt_t *pkt){
	  printf("magicnum: %d\n", pkt->header.magicnum);
    printf("version: %d\n", pkt->header.version);
    printf("type: %d\n", pkt->header.packet_type);
    printf("header len: %d\n", pkt->header.header_len);
    printf("packet len: %d\n", pkt->header.packet_type);
    printf("seq: %d\n", pkt->header.seq_num);
    printf("ack: %d\n", pkt->header.ack_num);
    printf("data: %s\n", pkt->data);
}


