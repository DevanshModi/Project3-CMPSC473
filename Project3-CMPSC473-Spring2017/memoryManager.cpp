#include "memoryManager.h"
#include <list>

unsigned long long memoryManager::memoryAccess(unsigned long long address)
{
	/* 
	Add first entry to page table if empty 
	*/
	if (pageTable->isEmpty()) {		
		index = 0;
		newPageEntry(address, index);		// Create a new page entry
		if (policy == FIFO)
			pageTable->pushFIFO(page);			// Push the page to page table
		else
			pageTable->pushLRU(page);			// Push the page to page table
		int offset = address % (2 ^ N);
		return page->frameIndex*(2^N) + offset;
	}
	/*
	If the page table is not full, continue adding pages
	*/
	else if (index = pageTable->size()-1 < numFrames) {
		// Check if address already exists in page table
		index = pageTable->inTable(address, N);
		// Physical address found so return index + frameIndex
		if (index != -1) {
			int offset = address % (2^N);
			return page->frameIndex*(2 ^ N) + offset;
		}

		// Create new page entry if not in page table
		newPageEntry(address, index);		// Create a new page entry
		if (policy == FIFO)
			pageTable->pushFIFO(page);			// Push the page to page table
		else
			pageTable->pushLRU(page);			// Push the page to page table
	}
	/*
	Page table is full so return address if inside, otherwise invoke swap
	*/
	else {
		// Check if address already exists in page table
		index = pageTable->inTable(address, N);
		// Physical address found so return index + frameIndex
		if (index != -1) {
			int offset = address % (2^N);
			return page->frameIndex*(2 ^ N) + offset;
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
		index = page->frameIndex;				// Update index of physical memory location to be swapped
		pageTable->popFIFO();					// Remove the last page entry
		newPageEntry(frameNumber, index);		// Add in new frame to table
		if (policy == FIFO)
			pageTable->pushFIFO(page);			// Push the page to page table
		else
			pageTable->pushLRU(page);			// Push the page to page table

	}
	else if (policy == LRU) {
		index = page->frameIndex;				// Update index of physical memory location to be swapped
		pageTable->popLRU();					// Remove the earliest page entry
		newPageEntry(frameNumber, index);		// Add in new frame to table
		if (policy == FIFO)
			pageTable->pushFIFO(page);			// Push the page to page table
		else
			pageTable->pushLRU(page);			// Push the page to page table
	}
}

void memoryManager::newPageEntry(unsigned long long addr, int frameIndex)
{
	PageEntry *page = (PageEntry *)malloc(sizeof(PageEntry));
	page->pageNum = (addr / pow(2, N));
	page->frameIndex = index;
}

