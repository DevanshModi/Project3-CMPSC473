/*
CMPSC 473
Team: Devansh Modi, Eric Traister
Project 3 Code
*/

#include <stdio.h>
#include "memoryManager.h"

int main() {
	//Define the Testbench here.

	// Local Variables
	int policy;
	unsigned int tb_N; // N = Page Address bits size, 2^ N = The physical frame/virtual page size to manage (bytes)
	unsigned int tb_numFrames; // total number of physical frames. Phy mem size = numFrames * 2^N
	unsigned int tb_virtualAddressSpaceSize; //  2^virtualAddressSpaceSize = total virtual address space (bytes)
	int hold;

	while (1) {
		tb_N = 3;tb_numFrames = 4;tb_virtualAddressSpaceSize = 8;policy = 1;
		std::cout << "Please enter N\t(page address bits size)\n";
		//std::cin >> tb_N;

		std::cout << "Please enter numFrames\t(total number of physical frames)\n";
		//std::cin >> tb_numFrames;

		std::cout << "Please enter virtualAddressSpaceSize\n";
		//std::cin >> tb_virtualAddressSpaceSize;

		std::cout << "Please enter '1' for FIFO (first in, first out)\nPlease enter '2' for LRU (least recently used)\n";
		//std::cin >> policy;

		if (policy == 1) {
			// Initiate FIFO testbench
			memoryManager fifoTest = memoryManager(FIFO, tb_N, tb_numFrames, tb_virtualAddressSpaceSize);

			// Emulate the memory manager

			std::cout<<"First Function Call"<<fifoTest.memoryAccess(171);
			std::cout << "First Function Call" << fifoTest.memoryAccess(141);
			std::cout << "First Function Call" << fifoTest.memoryAccess(13);
			std::cout << "First Function Call" << fifoTest.memoryAccess(227);
			std::cout << "First Function Call" << fifoTest.memoryAccess(203);
			std::cout << "First Function Call" << fifoTest.memoryAccess(4);
			fifoTest.memoryAccess(1);
			fifoTest.memoryAccess(6);
			fifoTest.memoryAccess(4);
			fifoTest.memoryAccess(0);
			fifoTest.memoryAccess(1);
			fifoTest.memoryAccess(0);
			fifoTest.memoryAccess(3);
			fifoTest.memoryAccess(1);
			fifoTest.memoryAccess(2);
			fifoTest.memoryAccess(1);

			// Pause execution from repeating while loop
			std::cin >> hold;
		}
		else if (policy == 2) {
			// Initiate LRU testbench
			memoryManager lruTest = memoryManager(LRU, tb_N, tb_numFrames, tb_virtualAddressSpaceSize);

			// Emulate the memory manager
			lruTest.memoryAccess(0);
			lruTest.memoryAccess(2);
			lruTest.memoryAccess(1);
			lruTest.memoryAccess(6);
			lruTest.memoryAccess(4);
			lruTest.memoryAccess(0);
			lruTest.memoryAccess(1);
			lruTest.memoryAccess(0);
			lruTest.memoryAccess(3);
			lruTest.memoryAccess(1);
			lruTest.memoryAccess(2);
			lruTest.memoryAccess(1);

			// Pause execution from repeating while loop
			std::cin >> hold;
		}
		else
			return (-1);


	}

	return 0;
}