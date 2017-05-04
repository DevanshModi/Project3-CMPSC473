/*
CMPSC 473
Team: Devansh Modi, Eric Traister
Project 3 Code
*/

#include "memoryManager.h"
#include <list>

unsigned long long memoryManager::memoryAccess(unsigned long long address)
{

	unsigned int pagesize = intpow(2, N);
	std::list<PageEntry>::iterator itr;
	
	//Following code generates the page number
	PageEntry *page = (PageEntry *)malloc(sizeof(PageEntry));
	page->pageNum = (address / pagesize);
	
	int offset = address % pagesize;

	/* 
	Add first entry to page table if empty 
	*/
	if (pageTable->size()==0) {		

		page->frameAddr = 0; //based on the replacement policy in swapping
		//newPageEntry(address, index);		// Create a new page entry

		if (policy == FIFO)
			pageTable->pushFIFO(page);			// Push the page to page table
		else
			pageTable->pushLRU(page);			// Push the page to page table

		pageTable->Point = pageTable->begin();

		return page->frameAddr*pagesize + offset;
	}
	/*
	If the page table is not full, continue adding pages
	*/
	else if (pageTable->size() < numFrames) {

		// Check which frame is available.
		//page->frameAddr = pageTable->inTable();
		itr = pageTable->inTable();

		//Push the page into the selected frame
	
		page->frameAddr = itr->frameAddr = pageTable->size();
		itr->pageNum = page->pageNum;

		//for (itr = pageTable->begin(); ; ++itr)
		//advance(itr, page->frameAddr-1);       // it points now to number 2     
		//itr += page->frameAddr;
		//pageTable->insert(itr, page);
		return page->frameAddr*pagesize + offset;
	}
	/*
	Page table is full so return address if inside, otherwise invoke swap
	*/
	else {
		if (policy == FIFO) {
			//Check for page fault here.
			if (!pageTable->CheckFrame(page->pageNum)) {
				pageTable->doFIFO(pageTable->Point,page); 
				swap(page->frameAddr, page->pageNum);
			}
		}
		else {

		}
		
	}
}

//void memoryManager::swap(unsigned int frameNumber, unsigned int pageNumber)
//{
//	int pagenum = -1;
//	/*
//	Page table is full so swap the current frame based on replacement policy
//	*/
//	if (policy == FIFO) {
//		index = page->frameAddr;				// Update index of physical memory location to be swapped
//		pageTable->popFIFO();					// Remove the last page entry
//		newPageEntry(frameNumber, index);		// Add in new frame to table
//		if (policy == FIFO)
//			pageTable->pushFIFO(page);			// Push the page to page table
//		else
//			pageTable->pushLRU(page);			// Push the page to page table
//
//	}
//	else if (policy == LRU) {
//		index = page->frameAddr;				// Update index of physical memory location to be swapped
//		pageTable->popLRU();					// Remove the earliest page entry
//		newPageEntry(frameNumber, index);		// Add in new frame to table
//		if (policy == FIFO)
//			pageTable->pushFIFO(page);			// Push the page to page table
//		else
//			pageTable->pushLRU(page);			// Push the page to page table
//	}
//}

unsigned long memoryManager::intpow(unsigned int base, unsigned int exp)
{
	unsigned long res = 1;
	while (exp)
	{
		if (exp & 1)
			res *= base;
		exp >>= 1;

		base *= base;
	}

	return res;
}


