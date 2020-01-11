#include "BluetoothCom.h"

BluetoothCom::BluetoothCom(const std::string& comPort, unsigned BaudRate, unsigned ByteSize, unsigned StopBits, unsigned Parity, Settings settings)
	: m_comPortName(comPort), m_baudRate(BaudRate), m_byteSize(ByteSize), m_stopBits(StopBits), m_parity(Parity), m_tick(50)
{
	if (!Init(m_comPortName, settings))
	{
		std::cout << "Error setting up port." << std::endl;
	}

}


bool BluetoothCom::Send(uint8_t* data, unsigned message_size, unsigned* bytes_sent)
{

	DWORD l_bytesSent = 0;
	unsigned attempts = 0;

	while (attempts < TIMEOUT && (DWORD)message_size != l_bytesSent)
	{
		//attempt to send
		for (int i = 0; i < message_size; i++)
		{
			std::cout << std::hex << (int)data[i] << std::endl;
		}

		WriteFile(hPort, (data + l_bytesSent), (message_size - l_bytesSent), &l_bytesSent, 0);

	}

	if (attempts == TIMEOUT)
	{
		return false;
	}

	return true;

}


bool BluetoothCom::TimedSend(float ms_delay, uint8_t* data, unsigned by_size, unsigned* bytes_sent)
{
	auto t0 = Time::now();
	auto t1 = Time::now();
	duration fElapsedTime;
	auto nanoseconds = std::chrono::duration_cast<ncs>(fElapsedTime);

	float accumulated_time = 0;

	while (1)
	{
		t0 = Time::now();

		fElapsedTime = (t0 - t1);
		nanoseconds = std::chrono::duration_cast<ncs>(fElapsedTime);
		accumulated_time += nanoseconds.count();

		if (accumulated_time >= ms_delay * DELAY_FACTOR)
		{
			//timer = 0;
			accumulated_time -= ms_delay * DELAY_FACTOR;
			if (!Send(data, by_size))
			{
				std::cout << "Error sending message\n" << std::endl;
				return false;
			}

			return true;

		}

		t1 = Time::now();
	}

}

Packet BluetoothCom::Receive(unsigned* bytes_received)
{
	uint8_t* receiveBuffer = (uint8_t*)malloc(BUFFER_SIZE);
	if (!receiveBuffer)
	{
		return { 0, 0 };
	}
	memset(receiveBuffer, 0, BUFFER_SIZE);

	DWORD l_bytesReceived;

	while (ReadFile(hPort, receiveBuffer, BUFFER_SIZE, &l_bytesReceived, 0));

	return { receiveBuffer, l_bytesReceived };
}


bool BluetoothCom::Init(const std::string& comPort, Settings settings)
{
	if ((settings & Com::READ) && (settings & Com::WRITE) && (settings & Com::EXISTING))
	{
		hPort = CreateFile(
			"COM4",
			GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr
		);
	}

	if (hPort == nullptr)
	{
		return false;
	}

	m_dcb = { 0 };
	
	GetCommState(hPort, &m_dcb);

	m_dcb.BaudRate = m_baudRate;
	m_dcb.ByteSize = m_byteSize;
	m_dcb.StopBits = ONESTOPBIT;
	m_dcb.Parity = m_parity;

	SetCommState(hPort, &m_dcb);

	return true;

}