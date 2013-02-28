#include "APIFrames.h" 

std::vector<unsigned char> APIFrames::API_wrap(std::vector<unsigned char> input)
{
	std::cout << "entering encode" << std::endl;
	std::vector<unsigned char> output(input.size() + 4);
	output.at(0) = 0x7E;
	int size = input.size();
	int sizeMSB = size/256;
	int sizeLSB = size%256; //- (sizeMSB * 256);
	output.at(1) = sizeMSB;
	output.at(2) = sizeLSB;
	std::cout << "size of packet MSB: " << std::hex << sizeMSB << "LSB: " << std::hex << sizeLSB << std::endl;
	int sum = 0;
	for(int i = 0; i < size; ++i)
	{
		output.at(i + 3) = input[i];
		sum += input.at(i);
	}
	int checksum = 0xFF - sum;
	output.at(size + 3) = checksum;
	sum = 0;
	std::cout << std::endl << "control packet" << std::endl;
	for(int i = 0; i < output.size(); ++i)
	{
		std::cout << i << ": " << std::uppercase << std::setw(2) << std::setfill('0') << std::hex << (int)output.at(i) << std::endl;
		sum += output.at(i);
	}
	std::cout <<  "controle checksum: " << sum << std::endl;
	return output;
}


std::vector<unsigned char> APIFrames::ATCommand(std::vector<unsigned char> ATCommand, std::vector<unsigned char> parameter ,std::vector<unsigned char> adress)
{
	std::cout << "Sending ATCommand packet" << std::endl;
	std::vector<unsigned char> output(4, 0);
	if(ATCommand.size() == 2)
	{
		//if(adress = 0)
		{
			output.at(0) = 0x08;		// type AT command
			output.at(1) = 0x52;		// Frame ID = 0, no response will be sent
			output.at(2) = ATCommand.at(0);	// 1st character of the AT command
			//std::cout << "ATCommand char 1: " << std::hex << (int)output.at(2) << std::endl;
			output.at(3) = ATCommand.at(1);	// 2nd character of the AT command
			//std::cout << "ATCommand char 2: " << std::hex << (int)output.at(3) << std::endl;
			for(int i = 0; i < parameter.size(); ++i)
			{
				output.push_back(parameter.at(i));
			}
			output = APIFrames::API_wrap(output);
		}
	}
	else
	{
		// Length of AT command is not correct
	}
	return output;
}
