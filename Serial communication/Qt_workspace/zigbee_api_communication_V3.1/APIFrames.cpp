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


std::vector<unsigned char> APIFrames::ATCommand(std::vector<unsigned char> ATCommand, std::vector<unsigned char> parameter, bool applyChanges)
{
	std::cout << "Sending ATCommand packet" << std::endl;
	std::vector<unsigned char> output;
	if(ATCommand.size() == 2)
	{
		if(applyChanges)
		{
			output.push_back(0x08);
		}
		else
		{
			output.push_back(0x09);
		}

		output.push_back(0x01);
		output.push_back(ATCommand.at(0));
		output.push_back(ATCommand.at(1));
		for(int i = 0; i < parameter.size(); ++i)
		{
			output.push_back(parameter.at(i));
		}
		output = APIFrames::API_wrap(output);
	}
	else
	{
		std::cout << "Length of AT command was incorrect" << std::endl;	// Length of AT command is not correct
	}
	return output;
}

std::vector<unsigned char> APIFrames::remoteATCommand(std::vector<unsigned char> ATCommand, std::vector<unsigned char> parameter, std::vector<unsigned char> destinationAddress, std::vector<unsigned char> networkAddress, bool applyChanges)
{
	std::cout << "Sending remote ATCommand packet" << std::endl;
	std::vector<unsigned char> output;
	if(ATCommand.size() == 2)
	{
		if(networkAddress.size() == 2)
		{
			if(destinationAddress.size() == 8)
			{
				output.push_back(0x17);
				output.push_back(0x51);
				for(int i = 0; i < destinationAddress.size(); ++i)
				{
					output.push_back(destinationAddress.at(i));
				}

				for(int i = 0; i < networkAddress.size(); ++i)
				{
					output.push_back(networkAddress.at(i));
				}

				if(applyChanges)
				{
					output.push_back(0x02);		//set options to apply changes (see datasheet for more info about options)
				}
				else
				{
					output.push_back(0x00);
				}

				output.push_back(ATCommand.at(0));
				output.push_back(ATCommand.at(1));
				for(int i = 0; i < parameter.size(); ++i)
				{
					output.push_back(parameter.at(i));
				}
				output = APIFrames::API_wrap(output);
			}
			else
			{
				std::cout << "destination address was incorrect" << std::endl;
			}
		}
		else
		{
			std::cout << "network address was incorrect" << std::endl;
		}
	}
	else
	{
		std::cout << "Length of AT command was incorrect" << std::endl;	// Length of AT command is not correct
	}
	return output;
}

std::vector<unsigned char> APIFrames::data(std::vector<unsigned char> data, std::vector<unsigned char> destinationAddress, std::vector<unsigned char> networkAddress, unsigned char broadcastRadius)
{
	std::cout << "Sending data packet" << std::endl;
	std::vector<unsigned char> output;
	if(data.size() != 0)
	{
		if(networkAddress.size() == 2)
		{
			if(destinationAddress.size() == 8)
			{
				output.push_back(0x10);		// Frame type identifier
				output.push_back(0x51);		// Frame ID for acknowledgement (0 is no ack)
				for(int i = 0; i < destinationAddress.size(); ++i)
				{
					output.push_back(destinationAddress.at(i));
				}
				for(int i = 0; i < networkAddress.size(); ++i)
				{
					output.push_back(networkAddress.at(i));
				}
				
				output.push_back(broadcastRadius);		// Broadcast radius, 0 = infinite (see datasheet for more info)
				output.push_back(0x00);		// Set options to none (see datasheet for more info)
				
				for(int i = 0; i < data.size(); ++i)
				{
					output.push_back(data.at(i));
				}
				output = APIFrames::API_wrap(output);
			}
			else
			{
				std::cout << "destination address was incorrect" << std::endl;
			}
		}
		else
		{
			std::cout << "network address was incorrect" << std::endl;
		}
	}
	else
	{
		std::cout << "Length of AT command was incorrect" << std::endl;	// Length of AT command is not correct
	}
	return output;
}

void APIFrames::API_unwrap(std::vector<unsigned char> input)
{
	if(input.front() != 0x7E)
	{
		return;
	}
	input.erase(input.begin());

	int size = input.front() * 256;
	input.erase(input.begin());

	size += input.front();
	input.erase(input.begin());
	if((input.size() - 1) != size)			// -1 because the checksum is not counted
	{
		std::cout << "input.size: " << input.size() << std::endl << "size: " << size << std::endl;
		std::cout << "size does not match" << std::endl;
		return;
	}	
	unsigned char type = input.front();
	
	unsigned char sum = 0;
	for(int i = 0; i < input.size(); ++i)
	{
		sum += input.at(i);
	}
	std::cout << "sum: " << std::hex <<  (int)sum << std::endl;
	if(sum != 0xFF)
	{
		std::cout << "checksum is wrong" << std::endl;
		return;
	}
	
	std::cout << "input size before pop_back()" << input.size() << std::endl;
	input.pop_back();
	std::cout << "input size after pop_back()" << input.size() << std::endl;
	switch (type)
	{	
		case 0x88:
			APIFrames::ATCommandResponse(input);
		break;		
		default:

		break;
	}		
}

void APIFrames::ATCommandResponse(std::vector<unsigned char> input)
{
	if(input.at(5) == 0)
	{
		//AT command was succesfully executed
	}
	std::cout << "ATCommandResponse()" << std::endl;
}
