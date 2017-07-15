#include "stdafx.h"
#include "GantryCommand.h"

namespace HPGantry
{
	const Byte HEADER = 0x1A;

	List<Byte>^ GantryCommand::getTwoHexBytes(Byte aByte)
	{
		List<Byte>^ bytes = gcnew List<Byte>();
		String^ byte_str = Convert::ToString(aByte, 16)->ToUpper();
		if(byte_str->Length > 1)
		{
			bytes->Add((Byte)byte_str[0]);
			bytes->Add((Byte)byte_str[1]);
		}
		else if(byte_str->Length == 1)
		{
			bytes->Add('0');
			bytes->Add((Byte)byte_str[0]);
		}
		else
			return nullptr;
		return bytes;
	}

	List<Byte>^ GantryCommand::calculateChecksum(List<Byte>^ bytes)
	{
		Byte sum = 0;
		if (bytes != nullptr)
		{
			for (int i = 0; i < bytes->Count; i++)
					sum = sum + bytes[i];
		}
		else
			return nullptr;

		Byte chk_sum = 0xff - sum + 1;
		List<Byte>^ chksum_bytes = getTwoHexBytes(chk_sum);
		return chksum_bytes;
	}

	List<Byte>^ GantryCommand::createCommandPacket(List<Byte>^ commandBytes)
	{
			List<Byte>^ cmdPacket = gcnew List<Byte>();
			cmdPacket->Add(HEADER);
			cmdPacket->AddRange(commandBytes);

			List<Byte>^ chk_sum_bytes = calculateChecksum(commandBytes);
			cmdPacket->AddRange(chk_sum_bytes);

			cmdPacket->Add('\r');
			cmdPacket->Add('\n');
			return cmdPacket;
	}

	List<Byte>^ GantryCommand::getByteList(String^ str)
	{
		List<Byte>^ byteList = gcnew List<Byte>();
		for each (char c in str)
			byteList->Add(c);
		return byteList;
	}

	List<Byte>^ GantryCommand:: makeJogParameter(Byte Xfeed, Byte Yfeed, Byte Zfeed)
	{
		List<Byte>^ jogParams = gcnew List<Byte>();
		jogParams->AddRange(getTwoHexBytes(Yfeed));
		jogParams->AddRange(getTwoHexBytes(Xfeed));
		jogParams->AddRange(getTwoHexBytes(Zfeed));
		return jogParams;
	}

	Byte GantryCommand::validateFeedRate(Byte feed)
	{
		if(feed < 0)
			return 0;
		if(feed > 100)
			return 100;
		return feed;
	}
}
