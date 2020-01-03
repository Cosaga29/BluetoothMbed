#include <fstream>
#include "com/Com.h"


bool WriteComPort(const uint8_t* data, const unsigned size)
{
	DWORD bytesWritten = 0;

	HANDLE hPort = CreateFile(
		"COM3",
		GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr
	);

	if (hPort == nullptr) 
	{
		return false;
	}

	DCB dcb = { 0 };

	GetCommState(hPort, &dcb);

	dcb.BaudRate = CBR_9600;
	dcb.ByteSize = 8;
	dcb.StopBits = ONESTOPBIT;
	dcb.Parity = NOPARITY;

	SetCommState(hPort, &dcb);

	//timing for output

	WriteFile(hPort, data, size, &bytesWritten, 0);



	return true;

}


int main()
{
	std::cout << sizeof(DWORD) << std::endl;

	uint8_t* m_Buffer = (unsigned char*)malloc(10);
	std::cout << WriteComPort(m_Buffer, 10);






	return 0;
}