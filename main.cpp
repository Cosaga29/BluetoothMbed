#include <fstream>
#include "com/BluetoothCom.h"
#include <chrono>

#define BYTES 1


int main()
{
	std::cout << sizeof(DWORD) << std::endl;

	BluetoothCom com1("COM4");
	uint8_t* message = (uint8_t*)malloc(1);
	for (int i = 0; i < 10; i++)
	{
		message[i] = i;
	}

	message[0] = 0x42;

	while (1)
	{


		com1.TimedSend(500, message);
		message[0]++;
		if (message[0] >= 0xFF)
		{
			message[0] = 0;
		}



	}



	return 0;
}