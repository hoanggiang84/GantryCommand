#include "stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace HPGantry;

namespace GanTryModuleTest
{
	[TestClass]
	public ref class GantryCommandTest
	{
	public: 
		[TestMethod]
		void CreateGetStatusCommand()
		{
			GantryCommand^ cmd = gcnew GantryCommand();
			List<Byte>^ cmdBytes = cmd->GetStatusCommand();
			Assert::AreEqual(15, cmdBytes->Count);

			// Assert header and command
			Assert::AreEqual((Byte)0x1A, cmdBytes[0]);
			Assert::AreEqual((Byte)'0', cmdBytes[1]);
			Assert::AreEqual((Byte)'1', cmdBytes[2]);
			Assert::AreEqual((Byte)'6', cmdBytes[3]);
			Assert::AreEqual((Byte)'4', cmdBytes[4]);

			// Assert check sum
			Assert::AreEqual((Byte)'1', cmdBytes[11]);
			Assert::AreEqual((Byte)'5', cmdBytes[12]);
		}

		[TestMethod]
		void set_zero_absolute_X()
		{
			GantryCommand^ cmd = gcnew GantryCommand();
			List<Byte>^ cmdBytes = cmd->SetZeroAbsolute_X();
			Assert::AreEqual(11, cmdBytes->Count);

			// Assert header and command
			Assert::AreEqual('B', (char)cmdBytes[3]);
			Assert::AreEqual('1', (char)cmdBytes[4]);
			Assert::AreEqual('0', (char)cmdBytes[5]);
			Assert::AreEqual('0', (char)cmdBytes[6]);

			// Assert check sum
			Assert::AreEqual((Byte)'C', cmdBytes[7]);
			Assert::AreEqual((Byte)'C', cmdBytes[8]);
		}

		[TestMethod]
		void set_zero_absolute_Y()
		{
			GantryCommand^ cmd = gcnew GantryCommand();
			List<Byte>^ cmdBytes = cmd->SetZeroAbsolute_Y();
			Assert::AreEqual(11, cmdBytes->Count);

			// Assert check sum
			Assert::AreEqual((Byte)'C', cmdBytes[7]);
			Assert::AreEqual((Byte)'B', cmdBytes[8]);
		}

		[TestMethod]
		void set_zero_absolute_Z()
		{
			GantryCommand^ cmd = gcnew GantryCommand();
			List<Byte>^ cmdBytes = cmd->SetZeroAbsolute_Z();
			Assert::AreEqual(11, cmdBytes->Count);

			// Assert check sum
			Assert::AreEqual((Byte)'C', cmdBytes[7]);
			Assert::AreEqual((Byte)'A', cmdBytes[8]);
		}

		[TestMethod]
		void GoHome()
		{
			GantryCommand^ cmd = gcnew GantryCommand();
			List<Byte>^ cmdBytes = cmd->GoHome();
			int cnt = cmdBytes->Count;
			// Assert command
			Assert::AreEqual('7', (char)cmdBytes[3]);
			Assert::AreEqual('4', (char)cmdBytes[4]);

			// Assert check sum
			Assert::AreEqual((Byte)'3', cmdBytes[cnt - 4]);
			Assert::AreEqual((Byte)'4', cmdBytes[cnt - 3]);
		}

		[TestMethod]
		void Reset()
		{
			GantryCommand^ cmd = gcnew GantryCommand();
			List<Byte>^ cmdBytes = cmd->Reset();
			int cnt = cmdBytes->Count;
			// Assert command
			Assert::AreEqual('7', (char)cmdBytes[3]);
			Assert::AreEqual('1', (char)cmdBytes[4]);

			// Assert check sum
			Assert::AreEqual((Byte)'3', cmdBytes[cnt - 4]);
			Assert::AreEqual((Byte)'7', cmdBytes[cnt - 3]);
		}

		[TestMethod]
		void JogPlusX_50feed()
		{
			GantryCommand^ cmd = gcnew GantryCommand();
			List<Byte>^ cmdBytes = cmd->Jog_X_Plus(50);
			int cnt = cmdBytes->Count;
			// Assert command
			Assert::AreEqual('6', (char)cmdBytes[3]);
			Assert::AreEqual('4', (char)cmdBytes[4]);

			// Y Feedrate 0
			Assert::AreEqual('0', (char)cmdBytes[5]);
			Assert::AreEqual('0', (char)cmdBytes[6]);

			// X Feedrate 50 = 0x32
			Assert::AreEqual('3', (char)cmdBytes[7]);
			Assert::AreEqual('2', (char)cmdBytes[8]);

			// Z Feedrate 0
			Assert::AreEqual('0', (char)cmdBytes[9]);
			Assert::AreEqual('0', (char)cmdBytes[10]);

			// Assert check sum
			Assert::AreEqual((Byte)'1', cmdBytes[cnt - 4]);
			Assert::AreEqual((Byte)'0', cmdBytes[cnt - 3]);
		}

		[TestMethod]
		void JogPlusX_Minus50feed()
		{
			GantryCommand^ cmd = gcnew GantryCommand();
			List<Byte>^ cmdBytes = cmd->Jog_X_Minus(50);
			int cnt = cmdBytes->Count;
			// Assert command
			Assert::AreEqual('6', (char)cmdBytes[3]);
			Assert::AreEqual('4', (char)cmdBytes[4]);

			// Feedrate -50 = 0xCE
			Assert::AreEqual('C', (char)cmdBytes[7]);
			Assert::AreEqual('E', (char)cmdBytes[8]);

			// Assert check sum
			Assert::AreEqual((Byte)'E', cmdBytes[cnt - 4]);
			Assert::AreEqual((Byte)'D', cmdBytes[cnt - 3]);
		}

		[TestMethod]
		void JogPlusY_100feed()
		{
			GantryCommand^ cmd = gcnew GantryCommand();
			List<Byte>^ cmdBytes = cmd->Jog_Y_Plus(100);
			int cnt = cmdBytes->Count;

			// Assert command
			Assert::AreEqual('6', (char)cmdBytes[3]);
			Assert::AreEqual('4', (char)cmdBytes[4]);

			// Y Feedrate 100 = 0x64
			Assert::AreEqual('6', (char)cmdBytes[5]);
			Assert::AreEqual('4', (char)cmdBytes[6]);

			// X Feedrate 0
			Assert::AreEqual('0', (char)cmdBytes[7]);
			Assert::AreEqual('0', (char)cmdBytes[8]);

			// Z Feedrate 0
			Assert::AreEqual('0', (char)cmdBytes[9]);
			Assert::AreEqual('0', (char)cmdBytes[10]);

			// Assert check sum
			Assert::AreEqual((Byte)'0', cmdBytes[cnt - 4]);
			Assert::AreEqual((Byte)'B', cmdBytes[cnt - 3]);
		}

		[TestMethod]
		void JogPlusZ_Minus100feed()
		{
			GantryCommand^ cmd = gcnew GantryCommand();
			List<Byte>^ cmdBytes = cmd->Jog_Z_Minus(100);
			int cnt = cmdBytes->Count;
			// Assert command
			Assert::AreEqual('6', (char)cmdBytes[3]);
			Assert::AreEqual('4', (char)cmdBytes[4]);

			// Y Feedrate 0
			Assert::AreEqual('0', (char)cmdBytes[5]);
			Assert::AreEqual('0', (char)cmdBytes[6]);

			// X Feedrate 0
			Assert::AreEqual('0', (char)cmdBytes[7]);
			Assert::AreEqual('0', (char)cmdBytes[8]);

			// Z Feedrate -100 = 0x9C
			Assert::AreEqual('9', (char)cmdBytes[9]);
			Assert::AreEqual('C', (char)cmdBytes[10]);

			// Assert check sum
			Assert::AreEqual((Byte)'F', cmdBytes[cnt - 4]);
			Assert::AreEqual((Byte)'9', cmdBytes[cnt - 3]);
		}

		[TestMethod]
		void GcodeCommandPacket()
		{
			GantryCommand^ cmd = gcnew GantryCommand();
			List<Byte>^ cmdBytes = cmd->GCode("G0X10X200F1000", 100);
			int cnt = cmdBytes->Count;
			// Assert command
			Assert::AreEqual('C', (char)cmdBytes[3]);
			Assert::AreEqual('8', (char)cmdBytes[4]);

			// Feedrate 100
			Assert::AreEqual('6', (char)cmdBytes[5]);
			Assert::AreEqual('4', (char)cmdBytes[6]);

			// Gcode length
			Assert::AreEqual('0', (char)cmdBytes[7]);
			Assert::AreEqual('E', (char)cmdBytes[8]);

			// Assert check sum
			Assert::AreEqual((Byte)'2', cmdBytes[cnt - 4]);
			Assert::AreEqual((Byte)'4', cmdBytes[cnt - 3]);
		}
	};
}
