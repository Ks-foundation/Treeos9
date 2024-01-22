// Snetwork.h
#ifndef _SNETWORK_H_
#define _SNETWORK_H_

// 플랫폼별 헤더 포함
#ifdef _WIN32
#include "winsock2.h"
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

// 공통 함수 프로토타입
int network_init();
int create_socket();
int connect_to_server(int socket, const char *server_ip, int port);
int send_data(int socket, const char *data);
int receive_data(int socket, char *buffer, size_t size);
void network_cleanup(int socket);

#endif
