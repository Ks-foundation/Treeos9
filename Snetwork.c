// Snetwork.c
#include "Snetwork.h"

// 네트워크 초기화
int network_init() {
#ifdef _WIN32
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(2,2), &wsa_data);
#else
    return 0; // UNIX 시스템은 별도의 초기화 필요 없음
#endif
}

// 소켓 생성
int create_socket() {
    return socket(AF_INET, SOCK_STREAM, 0);
}

// 서버에 연결
int connect_to_server(int socket, const char *server_ip, int port) {
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    return connect(socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
}

// 데이터 송신
int send_data(int socket, const char *data) {
    return send(socket, data, strlen(data), 0);
}

// 데이터 수신
int receive_data(int socket, char *buffer, size_t size) {
    return recv(socket, buffer, size, 0);
}

// 네트워크 종료
void network_cleanup(int socket) {
    close(socket);
#ifdef _WIN32
    WSACleanup();
#endif
}
