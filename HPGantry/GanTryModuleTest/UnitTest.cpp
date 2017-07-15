#include "stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::IO::Ports;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace HPGantry;

namespace GanTryModuleTest
{
	[TestClass]
	public ref class GantryControlTest
	{
	private:
		String^ port;
		void setupSerialPort()
		{
			array<String^>^ ports = SerialPort::GetPortNames();
			port = "COM1";
			if(ports->Length >0)
				port = ports[0];
		}

	public:

		[TestMethod]
		void Connect_ExistedPort_returnTrue()
		{
			setupSerialPort();
			GantryControl^ gantryCtrl = gcnew GantryControl();
			bool connected = gantryCtrl->Connect(port);
			delete gantryCtrl;
			Assert::IsTrue(connected);
		};

		[TestMethod]
		void Connect_unavailablePort_returnFalse()
		{
			GantryControl^ gantryCtrl = gcnew GantryControl();
			String^ unavailablePort = "COMX";
			bool connected = gantryCtrl->Connect(unavailablePort);
			delete gantryCtrl;
			Assert::IsFalse(connected);
		};

		[TestMethod]
		void Connect_OpennedPort_returnFalse()
		{
			setupSerialPort();
			GantryControl^ gantryCtrl = gcnew GantryControl();
			bool connected = gantryCtrl->Connect(port);

			GantryControl^ gantryCtrl2 = gcnew GantryControl();
			connected = gantryCtrl2->Connect(port);
			delete gantryCtrl;
			delete gantryCtrl2;
			Assert::IsFalse(connected);
		};

		[TestMethod]
		void Destructor_connectSamePort_returnTrue()
		{
			setupSerialPort();
			GantryControl^ gantryCtrl = gcnew GantryControl();
			bool connected = gantryCtrl->Connect(port);
			delete gantryCtrl;

			gantryCtrl = gcnew GantryControl();
			connected = gantryCtrl->Connect(port);
			delete gantryCtrl;
			Assert::IsTrue(connected);
		};

		[TestMethod]
		void GetPortName_CannotChangePortName()
		{
			GantryControl^ gantryCtrl = gcnew GantryControl();
			bool connected = gantryCtrl->Connect("COM6");
			String^ copyOfPortname = gantryCtrl->GetPortName();
			Assert::AreEqual("COM6", copyOfPortname);

			copyOfPortname += "2";
			Assert::AreNotEqual(copyOfPortname, gantryCtrl->GetPortName());
		};
	};
}
