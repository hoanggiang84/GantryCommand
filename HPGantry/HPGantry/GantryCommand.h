#pragma once
using namespace System;
using namespace System::Collections::Generic;

namespace HPGantry
{
	public ref class GantryCommand
	{
	private:

		List<Byte>^ getTwoHexBytes(Byte aByte);

		List<Byte>^ calculateChecksum(List<Byte>^ bytes);

		List<Byte>^ createCommandPacket(List<Byte>^ commandBytes);

		List<Byte>^ getByteList(String^ str);

		List<Byte>^ makeJogParameter(Byte Xfeed, Byte Yfeed, Byte Zfeed);

		Byte validateFeedRate(Byte feed);

	public:
		List<Byte>^ GetStatusCommand()
		{	
			String^ cmd = "0164000000";
			return createCommandPacket(getByteList(cmd));
		};
			
		List<Byte>^ SetZeroAbsolute_X()
		{
			String^ cmd = "01B100";
			return createCommandPacket(getByteList(cmd));
		}

		List<Byte>^ SetZeroAbsolute_Y()
		{
			String^ cmd = "01B101";
			return createCommandPacket(getByteList(cmd));
		}

		List<Byte>^ SetZeroAbsolute_Z()
		{
			String^ cmd = "01B102";
			return createCommandPacket(getByteList(cmd));
		}

		List<Byte>^ GoHome()
		{
			String^ cmd = "0174";
			return createCommandPacket(getByteList(cmd));
		}

		List<Byte>^ Reset()
		{
			String^ cmd = "0171";
			return createCommandPacket(getByteList(cmd));
		}

		List<Byte>^ Jog_X_Plus(Byte feedRateInHundredPercent)
		{
			Byte validFeed = validateFeedRate(feedRateInHundredPercent);
			String^ cmd = "0164";
			List<Byte>^ cmdPacket = getByteList(cmd);
			List<Byte>^ jogParams = makeJogParameter(validFeed,0,0);
			cmdPacket->AddRange(jogParams);
			return createCommandPacket(cmdPacket);
		}

		List<Byte>^ Jog_X_Minus(Byte feedRateInHundredPercent)
		{
			Byte validFeed = - validateFeedRate(feedRateInHundredPercent);
			String^ cmd = "0164";
			List<Byte>^ cmdPacket = getByteList(cmd);
			List<Byte>^ jogParams = makeJogParameter(validFeed,0,0);
			cmdPacket->AddRange(jogParams);
			return createCommandPacket(cmdPacket);
		}

		List<Byte>^ Jog_Y_Plus(Byte feedRateInHundredPercent)
		{
			Byte validFeed = validateFeedRate(feedRateInHundredPercent);
			String^ cmd = "0164";
			List<Byte>^ cmdPacket = getByteList(cmd);
			List<Byte>^ jogParams = makeJogParameter(0,validFeed,0);
			cmdPacket->AddRange(jogParams);
			return createCommandPacket(cmdPacket);
		}

		List<Byte>^ Jog_Y_Minus(Byte feedRateInHundredPercent)
		{
			Byte validFeed = - validateFeedRate(feedRateInHundredPercent);
			String^ cmd = "0164";
			List<Byte>^ cmdPacket = getByteList(cmd);
			List<Byte>^ jogParams = makeJogParameter(0,validFeed,0);
			cmdPacket->AddRange(jogParams);
			return createCommandPacket(cmdPacket);
		}

		List<Byte>^ Jog_Z_Plus(Byte feedRateInHundredPercent)
		{
			Byte validFeed = validateFeedRate(feedRateInHundredPercent);
			String^ cmd = "0164";
			List<Byte>^ cmdPacket = getByteList(cmd);
			List<Byte>^ jogParams = makeJogParameter(0,0,validFeed);
			cmdPacket->AddRange(jogParams);
			return createCommandPacket(cmdPacket);
		}

		List<Byte>^ Jog_Z_Minus(Byte feedRateInHundredPercent)
		{
			Byte validFeed = - validateFeedRate(feedRateInHundredPercent);
			String^ cmd = "0164";
			List<Byte>^ cmdPacket = getByteList(cmd);
			List<Byte>^ jogParams = makeJogParameter(0,0,validFeed);
			cmdPacket->AddRange(jogParams);
			return createCommandPacket(cmdPacket);
		}

		List<Byte>^ GCode(String^ gcode, Byte feedRateInHundredPercent)
		{
			List<Byte>^ gCodeBytes = getByteList(gcode);
			List<Byte>^ gCodeLength = getTwoHexBytes(gCodeBytes->Count);
			Byte validFeed = validateFeedRate(feedRateInHundredPercent);
			List<Byte>^ feedRate = getTwoHexBytes(validFeed);

			String^ cmd ="01C8";
			List<Byte>^ cmdPacket = getByteList(cmd);
			cmdPacket->AddRange(feedRate);
			cmdPacket->AddRange(gCodeLength);
			cmdPacket->AddRange(gCodeBytes);
			
			return createCommandPacket(cmdPacket);
		}
	};
}
