#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 7777

int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    char message[1024];
    
    // 소켓 생성
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }
    
    // 서버 주소 설정
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // IPv4 주소를 네트워크 바이트 순서로 변환
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }
    
    // 서버에 연결
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        return -1;
    }
    
    // 사용자 입력 받기
    while (true) {
        std::cout << "Enter message ('exit' to quit): ";
        std::cin.getline(message, 1024);
        
        // 'exit'를 입력하면 루프 종료
        if (strcmp(message, "exit") == 0) {
            break;
        }
        
        // 서버로 메시지 전송
        send(sock , message , strlen(message) , 0 );
        std::cout << "Message sent" << std::endl;
        
        // 서버로부터 메시지 수신
        valread = read(sock , buffer, 1024);
        std::cout << "Server response: " << buffer << std::endl;
        memset(buffer, 0, sizeof(buffer)); // 버퍼 초기화
    }
    
    // 소켓 닫기
    close(sock);
    return 0;
}

