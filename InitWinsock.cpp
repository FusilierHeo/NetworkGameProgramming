#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdio.h>



// 소켓 함수 오류 출력 후 종료
/*
void err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}
*/
float WORDtoFloat(WORD bitdata)
{
	WORD bytefront = (bitdata >> 8) & 0xff; //bitdata의 비트를 오른쪽으로 8칸 shift하고 1111 1111(0xff)와 AND연산한다. HIBYTE기능
	WORD byteback = bitdata & 0xff; //1111 1111 (0xff)와 bitdata를 AND 연산한다.

	return bytefront + byteback * 0.1f;
}

void ShowWSAData(WSADATA & p_wsdata)
{
	
	float a = WORDtoFloat(p_wsdata.wVersion); //float 형을 반환하기 때문에 float형 변수사용
	float b = WORDtoFloat(p_wsdata.wHighVersion);

	printf("자체함수로 보여진 wVersion : %.1f", a);
	printf("\n");
	printf("자체함수로 보여진 wHighVersion : %.1f", b);
	printf("\n");
	printf("%s", p_wsdata.szDescription);

	printf("\n");
	printf("LOBYTE와 HIBYTE 사용 wVersion: %d, %d", LOBYTE(p_wsdata.wVersion), HIBYTE(p_wsdata.wVersion));
	printf("\n");
	printf("LOBYTE와 HIBYTE 사용 wVersion: %d, %d", LOBYTE(p_wsdata.wHighVersion), HIBYTE(p_wsdata.wHighVersion));
}
int main(int argc, char *argv[])
{
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;
	/* 
	(a, b = 1)일떄
	a = 0000 0001
	b = 0000 0001
	b&0xff <<8 = 0000 0001 0000 0000 
	a&0xff) = 0000 0000 0000 0001
	(a|((b&0xff)<<8)) = 0000 0001 0000 0001 = 257
	*/

	WSAStartup(MAKEWORD(1, 1), &wsa);
	ShowWSAData(wsa);


	//MessageBox(NULL, "윈속 초기화 성공", "알림", MB_OK);

	//socket()
	
	SOCKET tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
	//if (tcp_sock == INVALID_SOCKET) err_quit("socket()");
	//MessageBox(NULL, "TCP 소켓 생성 성공", "알림", MB_OK);
	
	
	

	// closesocket()
	closesocket(tcp_sock);

	//윈속 종료

	WSACleanup();
	return 0;
}

