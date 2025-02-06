#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> // socket header file is os specific linux: <sys/socket.h>

#pragma comment(lib, "ws2_32.hlib") //Link with winsock library

/* 
your operating system dictates how the program will be.
the API is mostly the same (E.g. socket(), bind(), listen(), accept(), send(), recv(), etc.)
but the initialization is different and cleanup.

Initialization and Cleanup:
On Windows, you need to initialize Winsock with WSAStartup() before using any network functions and 
clean up with WSACleanup() when done.
On Linux, no such initialization is needed.

Error Handling:
Windows uses different error codes and you retrieve errors with WSAGetLastError(), 
whereas Linux typically uses the global variable errno.

Function and Type Names:
Some functions and types might have slightly different names or calling conventions.
For example, on Windows, socket handles are of type SOCKET (an unsigned integertype), 
while on Linux they are file descriptors (integers).
*/

#define PORT 40000

// Initialize winsocket
void init_winsock();
// Function to cleanup winsocket
void cleanup_winsock();

int main(void)
{
    init_winsock();

    // Create a socket
    SOCKET socket_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(socket_server == INVALID_SOCKET){
        printf("Socket creation failed with error %d", WSAGetLastError());
        cleanup_winsock();
        return 1;
    }

    // Set up socket address in struct
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // accept any incoming address (this is bad practice)
    server_addr.sin_port = htons(PORT); // listen on port 40000

    // bind the socket to the port and address
    if (bind(socket_server, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR){
        printf("Bind failed with error %d", WSAGetLastError());
        closesocket(socket_server);
        cleanup_winsock();
        return 1;
    }

    // Start listennig for incoming connection 
    if(listen(socket_server, SOMAXCONN) == SOCKET_ERROR){
        printf("Listen failed with error %d", WSAGetLastError());
        closesocket(socket_server);
        cleanup_winsock();
        return 1;
    }

    printf("server is listening on port %d", PORT);

    //Accept incoming connection
    SOCKET client_socket;
    struct sockaddr_in client_addr;
    int client_size = sizeof(client_addr);
    client_socket = accept(socket_server, (struct sockaddr*)&client_addr, &client_size);
    if (client_socket == INVALID_SOCKET){
        printf("Accept failed with error %d", WSAGetLastError());
        closesocket(socket_server);
        cleanup_winsock();
        return 1;
    }

    printf("Client connected/n");

    // Recieve http request from client
    char buffer[1024];
    int recv_size = recv(client_socket, buffer, sizeof(buffer), 0);
    if (recv_size > 0){
        buffer[recv_size] = '\0'; // Null teminate recieved data
        printf("Recieved request:\n %s \n", buffer);

        // Simple http response
        const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
                               "<html><body><h1>Hello, World!</h1></body></html>";
        send(client_socket, response, strlen(response), 0);

    }

    // Close the connection 
    closesocket(client_socket);
    closesocket(socket_server);
    cleanup_winsock();

    return 0;
}

void init_winsock()
{
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (result != 0){
        printf("WSAStartup Failed with error %d", result);
        exit(1);
    }
}

void cleanup_winsock()
{
    WSACleanup();
}