#pragma comment(lib, "ws2_32")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include <WS2tcpip.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>




void err_display(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

BOOL GetIPAddr(char *name, IN_ADDR *addr)
{
	HOSTENT *ptr = gethostbyname(name);
	if (ptr == NULL) {
		err_display("gethostbyname()");
		return FALSE;
	}
	if (ptr->h_addrtype != AF_INET)
		return FALSE;
	memcpy(addr, ptr->h_addr, ptr->h_length);
	return TRUE;
}

// IPv4 주소 -> 도메인 이름
BOOL GetDomainName(IN_ADDR addr, char *name, int namelen)
{
	HOSTENT *ptr = gethostbyaddr((char *)&addr, sizeof(addr), AF_INET);
	if (ptr == NULL) {
		err_display("gethostbyaddr()");
		return FALSE;
	}
	if (ptr->h_addrtype != AF_INET)
		return FALSE;
	strncpy(name, ptr->h_name, namelen);
	return TRUE;
}



int main(int argc, char*argv[])
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;
	
	int i, j;
	int key;
	char hostname[NI_MAXHOST];
	char KeyDomain[256];
	char KeyIpAddr[20][20];
	void *ptr; //사용 포인터 아래 servinfo와 함께
	IN_ADDR addr;
	IN6_ADDR addr6;

	struct hostent *host;
	//gethostbyname 함수를 이용해서 도메인 주소의 정보를 얻어와 hostent 구조체형식으로 반환한다.
	host = gethostbyname(argv[1]);

	//int getaddrinfo(const char *hostname, const char *service, const struct addrinfo *hints, struct addrinfo **result);
	int status;
	struct addrinfo hints;
	struct addrinfo *servinfo;//결과저장

	memset(&hints, 0, sizeof(hints)); //hints 구조체의 모든 값을 0으로
	hints.ai_family = AF_UNSPEC; //버전에 상관없이 모든 결과 수렴
	hints.ai_socktype = SOCK_STREAM; //TCP stream 소켓
	hints.ai_flags = AI_ALL;//사용된 옵션을 나타내는 플래그



	/*===========================↓어플 시작지점==================================*/

	printf("어떤정보를 입력?\n1 : 도메인이름\n2 : ipv4주소\n3 : ipv6주소\n요청값:");
	scanf("%d", &key);

	switch (key) { //메인 탐색/입력 기능을 위한 스위치문
	case 1:
		printf("\n도메인이름 입력:");
		scanf("%s", &KeyDomain);	
		host = gethostbyname(KeyDomain);//별칭탐색용
		status = getaddrinfo(KeyDomain, "80", &hints, &servinfo);
		GetIPAddr(KeyDomain, &addr);
		
	
		while (servinfo)
		{
			char saddr[INET6_ADDRSTRLEN];

			SOCKADDR_IN* soin = NULL;
			SOCKADDR_IN6* soin6 = NULL;
			soin6->sin6_addr;
			switch (servinfo->ai_family)//keydomain과 포인터에 ipv6자료 초기화를 위함
			{
			case AF_INET6:
				soin6 = (sockaddr_in6 *)servinfo->ai_addr;
				inet_ntop(servinfo->ai_family, &soin6->sin6_addr, saddr, sizeof(saddr));
				printf("ipv6 주소 = %s\n", saddr);
				break;

			case AF_INET:
				soin = (sockaddr_in *)servinfo->ai_addr;
				inet_ntop(servinfo->ai_family, &soin->sin_addr, saddr, sizeof(saddr));
				printf("ipv4 주소 = %s\n", saddr);
				break;
			}

			servinfo = servinfo->ai_next;
			
		}
		
		printf("\n");
		for (int i = 0; host->h_aliases[i]; i++)
			printf("별칭 %d번: %s\n", i + 1, host->h_aliases[i]);

		break;


	case 2:
		printf("\nipv4주소 입력:");
		scanf("%s", &KeyIpAddr);	
		status = getaddrinfo((char *)&KeyIpAddr,NULL, &hints, &servinfo);

		
		while (servinfo)
		{
			char saddr[INET6_ADDRSTRLEN];

			SOCKADDR_IN* soin = NULL;
			SOCKADDR_IN6* soin6 = NULL;
			soin6->sin6_addr;
			switch (servinfo->ai_family)//keydomain과 포인터에 ipv6자료 초기화를 위함
			{
			case AF_INET6:
				soin6 = (sockaddr_in6 *)servinfo->ai_addr;
				inet_ntop(servinfo->ai_family, &soin6->sin6_addr, saddr, sizeof(saddr));
				printf("ipv6 주소 = %s\n", saddr);
				break;

			case AF_INET:
				soin = (sockaddr_in *)servinfo->ai_addr;
				inet_ntop(servinfo->ai_family, &soin->sin_addr, saddr, sizeof(saddr));
				printf("ipv4 주소 = %s\n", saddr);
				break;
			}

			servinfo = servinfo->ai_next;
		}

		printf("\n");
		for (int i = 0; host->h_aliases; i++)
			printf("별칭 %d번: %s\n", i + 1, host->h_aliases[i]);
		printf("도메인 이름 = %s\n", host->h_addr_list[0]);
	}
	



	WSACleanup();

	return 0;
}


