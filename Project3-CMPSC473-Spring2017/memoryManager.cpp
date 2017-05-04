#include "memoryManager.h"
#include <list>

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
	accessCounter++;
	/* 
	Add first entry to page table if empty 
	*/
	if (pageTable->isEmpty()) {		
		accessCounter = 1;						// Reset memory access counter to initial post operation statez
		newPageEntry(address);					// Create a new page entry
		pageTable->push(page);					// Push the page to page table
	}
	/*
	If the page table is not full, continue adding pages
	*/
	else if (pageTable->size() < numFrames) {
		//// Check if address already exists in page table
		//for (int j = 0; j < pageTable->size(); j++) {
		//	if (page->pageNum == (address / pow(2, N)))
		//		return page->frameAddr;			// Return physical address if found in page table
		//}
		// Create new page entry if not in page table
		newPageEntry(address);					// Create a new page entry
		pageTable->push(page);					// Push the page to page table
	}
	/*
	Page table is full so return address if inside, otherwise invoke swap
	*/
	else {
		// Check if address already exists in page table
		for (int j = 0; j < pageTable->size(); j++) {
			if (page->pageNum == (address / pow(2, N)))
				return (page->frameRef + offset);			// Return physical address if found in page table
		}
		// Page table is full so swap
		swap(address, page->pageNum);
	}
}

void memoryManager::swap(unsigned int frameNumber, unsigned int pageNumber)
{
	int pagenum = -1;
	/*
	Page table is full so swap the current frame based on replacement policy
	*/
	if (policy == FIFO) {
		// Find the page entry last entered into the table
		for (int i = 0; i < pageTable->size(); i++) {
			int lastIn = -1;
			if (page->counter > lastIn) {
				lastIn = page->counter;
				pagenum = page->pageNum;
			}
		}
		// Remove the last page entry and add in new frame to table
		for (int j = 0; j < pageTable->size(); j++) {
			page[j]->pop();
			newPageEntry(frameNumber);
			pageTable->push(*page);
		}
	}
	else if (policy == LRU) {
		// Find the earliest page entry in the table
		for (int i = 0; i < pageTable->size(); i++) {
			int earliestIn = INT_MAX;
			if (page->counter < earliestIn) {
				earliestIn = page->counter;
				pagenum = page->pageNum;
			}
		}
		// Remove the earliest page entry and add in new frame to table
		for (int j = 0; j < pageTable->size(); j++) {
			if (page[j]->pageNum == pagenum) {
				page[j]->pop();
				newPageEntry(frameNumber);
				pageTable->push(*page);
			}
		}
	}
}

void memoryManager::newPageEntry(unsigned long long addr)
{
	PageEntry *page = (PageEntry *)malloc(sizeof(PageEntry));
	page->pageNum = (addr / pow(2, N));
	page->counter = accessCounter;
	page->validBit = 1;
	page->offset = (addr % pow(2, N));
	page->frameRef = ?????;
}