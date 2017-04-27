#include "memoryManager.h"
// memoryManager.cpp

unsigned long long memoryManager::memoryAccess(unsigned long long address)
{
	/*
	1.	Is the page table empty?
	2.	If not, is the page table full?
			If(full)
				-> fill the next page into the open table slot
			Else(not full)
				-> replace/swap page based on the active policy
	*/

	/// TODO:	this doesn't make sense... I think pages should be taken from a "data bank" so it already holds its page #
	///			need to figure out how to create or pull pages from "HDD/data bank" for testbench
	PageEntry *page = (PageEntry *)malloc(sizeof(PageEntry));
	page->addr = address;
	page->frameNum = 0;
	page->pageNum = 0;
	page->counter = mycounter;

	if (pageTable->isEmpty()) {
		// Add the first page to page table
		pageTable->push(page);
	}
	else if (pageTable->size() < numFrames) {
		// If the page table is not full, continue adding pages
		/// TODO:	add code to add pages into list
	}
	else {
		// Page table is full so swap
		swap(page->frameNum, page->pageNum);
	}
}

void memoryManager::swap(unsigned int frameNumber, unsigned int pageNumber)
{
	///@todo ta instrumentation to go here
	///students should instrument memorymanager performance in their own class for their internal verification or may
	///modify this code for their testing purpose; however the TAs instrumentation will used for determining grade basis.


	// Page table is full so swap the current frame based on replacement policy
	if (policy == FIFO) {
		/// TODO:	invoke function to swap page using FIFO
	}
	else if (policy == LRU) {
		/// TODO:	invoke function to swap page using LRU
	}

	myNumSwaps++;
}