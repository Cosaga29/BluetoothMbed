#include <fstream>
#include "com/BluetoothCom.h"
#include <chrono>

#define BYTES 1
#define DELAY_FACTOR 100000

#define DELAY 500


typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::microseconds mcs;
typedef std::chrono::nanoseconds ncs;
typedef std::chrono::duration<double> duration;


int main()
{
	std::cout << sizeof(DWORD) << std::endl;

	BluetoothCom com1("COM4");
	uint8_t* message = (uint8_t*)malloc(BYTES);

	message[0] = 0x42;

	auto t0 = Time::now();
	auto t1 = Time::now();
	duration fElapsedTime;
	auto nanoseconds = std::chrono::duration_cast<ncs>(fElapsedTime);

	float accumulated_time = 0;

	while (1)
	{
		com1.TimedSend(500, message, BYTES);
		message[0]++;
		if (message[0] >= 0xFF)
		{
			message[0] = 0;
		}
	}

	//while (1)
	//{
	//	t0 = Time::now();
	//
	//	fElapsedTime = (t0 - t1);
	//	nanoseconds = std::chrono::duration_cast<ncs>(fElapsedTime);
	//	accumulated_time += nanoseconds.count();
	//
	//	if (accumulated_time >= DELAY * DELAY_FACTOR)
	//	{
	//		//timer = 0;
	//		accumulated_time -= DELAY * DELAY_FACTOR;
	//		if (!com1.Send(message, BYTES))
	//		{
	//			std::cout << "Error sending message\n" << std::endl;
	//		}
	//
	//		message[0]++;
	//		if (message[0] >= 0xFF)
	//		{
	//			message[0] = 0;
	//		}
	//
	//
	//	}
	//
	//
	//	t1 = Time::now();
	//}


	return 0;
}