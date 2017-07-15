// HPGantry.h

#pragma once

using namespace System;
using namespace System::IO::Ports;

namespace HPGantry {

	public ref class GantryControl
	{
	private:
		SerialPort^ _serialPort;
		String^ _portName;

		void openCOM()
		{
			_serialPort->PortName = _portName;
			_serialPort->BaudRate = 115200;
			_serialPort->Parity = Parity::None;
			_serialPort->DataBits = 8;
			_serialPort->StopBits = StopBits::One;
			_serialPort->Handshake = Handshake::None;

	        // Set the read/write timeouts
			_serialPort->ReadTimeout = 500;
			_serialPort->WriteTimeout = 500;

			_serialPort->Open();
		}

		void closeCOM()
		{
			_serialPort->Close();
		}

	public:
		 String^ GetPortName()
		 {
			 return _portName;
		 }

		GantryControl()
		{
			_serialPort = gcnew SerialPort();
		}

		~GantryControl()
		{
			if(_serialPort != nullptr)
				_serialPort->Close();	
		}

		bool Connect(String^ COM)
		{
			if(COM == nullptr)
				return false;

			_portName = COM;
			try
			{
				closeCOM();
				openCOM();
			}
			catch(Exception^ ex)
			{
				return false;
			}
			return true;
		}
	};
}
