#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdio.h>



// ���� �Լ� ���� ��� �� ����
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
	WORD bytefront = (bitdata >> 8) & 0xff; //bitdata�� ��Ʈ�� ���������� 8ĭ shift�ϰ� 1111 1111(0xff)�� AND�����Ѵ�. HIBYTE���
	WORD byteback = bitdata & 0xff; //1111 1111 (0xff)�� bitdata�� AND �����Ѵ�.

	return bytefront + byteback * 0.1f;
}

void ShowWSAData(WSADATA & p_wsdata)
{
	
	float a = WORDtoFloat(p_wsdata.wVersion); //float ���� ��ȯ�ϱ� ������ float�� �������
	float b = WORDtoFloat(p_wsdata.wHighVersion);

	printf("��ü�Լ��� ������ wVersion : %.1f", a);
	printf("\n");
	printf("��ü�Լ��� ������ wHighVersion : %.1f", b);
	printf("\n");
	printf("%s", p_wsdata.szDescription);

	printf("\n");
	printf("LOBYTE�� HIBYTE ��� wVersion: %d, %d", LOBYTE(p_wsdata.wVersion), HIBYTE(p_wsdata.wVersion));
	printf("\n");
	printf("LOBYTE�� HIBYTE ��� wVersion: %d, %d", LOBYTE(p_wsdata.wHighVersion), HIBYTE(p_wsdata.wHighVersion));
}
int main(int argc, char *argv[])
{
	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;
	/* 
	(a, b = 1)�ϋ�
	a = 0000 0001
	b = 0000 0001
	b&0xff <<8 = 0000 0001 0000 0000 
	a&0xff) = 0000 0000 0000 0001
	(a|((b&0xff)<<8)) = 0000 0001 0000 0001 = 257
	*/

	WSAStartup(MAKEWORD(1, 1), &wsa);
	ShowWSAData(wsa);


	//MessageBox(NULL, "���� �ʱ�ȭ ����", "�˸�", MB_OK);

	//socket()
	
	SOCKET tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
	//if (tcp_sock == INVALID_SOCKET) err_quit("socket()");
	//MessageBox(NULL, "TCP ���� ���� ����", "�˸�", MB_OK);
	
	
	

	// closesocket()
	closesocket(tcp_sock);

	//���� ����

	WSACleanup();
	return 0;
}

