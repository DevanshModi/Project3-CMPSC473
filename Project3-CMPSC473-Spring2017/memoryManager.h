#pragma once

#include <list>
#include "virtualMemoryManagerInterface.hpp"

// Structures
struct PageEntry
{
	unsigned long pageNum;			//Logical Page Number
	unsigned long frameAddr; //Physical Address of Frame
};
struct PageTable
{
	// List contructor
	std::list<PageEntry> *table;
	unsigned int Frames;
	std::list<PageEntry>::iterator Point;

	// Initialize the page table
	PageTable(unsigned int numFrames) {
		table = new std::list<PageEntry>;
		Frames = numFrames;
		table->resize(Frames-1);
	}

	//Ret
	std::list<PageEntry>::iterator begin() {
		return table->begin();
	}


	//Insert page to the frame whose iterator is passed.
	void insert(std::list<PageEntry>::iterator itr,PageEntry *page) {
		table->insert(itr, *page);
	}

	// Add new page to table
	void pushFIFO(PageEntry *page) {
		table->push_front(*page);
	}

	// Add new page to table
	void pushLRU(PageEntry *page) {
		table->push_front(*page);
	}

	// Remove the last page and return it
	void doFIFO(std::list<PageEntry>::iterator &Point, PageEntry *page) {
		
		std::list<PageEntry>::iterator copyitr;
		page->frameAddr = Point->frameAddr;
		if (Point->frameAddr == Frames-1) Point = table->begin();
		table->insert(Point, *page);
		copyitr = std::next(Point, 1);
		table->erase(Point);
		Point = copyitr;

	}

	// Remove the last page and return it
	void popLRU() {
		if (isEmpty())
			//return NULL;
		PageEntry page = table->back();
		//free(&page);
		table->pop_back();
	}

	//Check if there is an empty frame.
	std::list<PageEntry>::iterator inTable() {
		//int pos = 0;
		bool run = 1;
		std::list<PageEntry>::iterator list_iter,ReturnIter;
		for (list_iter = table->begin(); run && list_iter != table->end(); list_iter++) {
			if ((list_iter)->pageNum == NULL) {
				ReturnIter = list_iter;
				run = 0;
			}
		}

		return ReturnIter;	// returns -1 if not in page table
	}

	// Checks size of page table
	unsigned int size() {
		unsigned int size = 0, count = 0;
		std::list<PageEntry>::iterator list_iter;
		for (list_iter = table->begin(); count<=Frames && list_iter != table->end(); list_iter++) {
			if ((list_iter)->pageNum != NULL)
				size++;
			count++;
		}
		return size;
	}

	// Checks if the whole page table is empty
	bool isEmpty() {
		bool e=1;
		unsigned int count = 0;
		std::list<PageEntry>::iterator list_iter;
		for (list_iter = table->begin(); count<=Frames && list_iter != table->end(); list_iter++) {
			if ((list_iter)->pageNum != NULL)
				e = 0;
			count++;
		}
		return e;
	}

	// Checks if page is in page table and return index to physical memory location if it is
	int CheckFrame(unsigned int pnum) {
		int e = 0;
		unsigned int count = 0;
		std::list<PageEntry>::iterator list_iter;
		for (list_iter = table->begin(); count<=Frames && list_iter != table->end(); list_iter++) {
			if ((list_iter)->pageNum == pnum)
				e = (list_iter)->frameAddr;
			count++;
		}
		return e;
	}
};


class memoryManager : public virtualMemoryManagerInterface {
public:
	memoryManager(ReplacementPolicy p, unsigned int pS, unsigned int nF, unsigned int vA) : virtualMemoryManagerInterface(p, pS, nF, vA) {
		pageTable = new PageTable(nF);
		policy = p;
	}
	unsigned long long memoryAccess(unsigned long long address) override;
	//void swap(unsigned int frameNumber, unsigned int pageNumber);
	unsigned long intpow(unsigned int base, unsigned int exp);
	//void newPageEntry(unsigned long long addr, int frameIndex);
	//unsigned long long& numberPageSwaps();

	PageTable *pageTable = NULL;
	PageEntry *page = NULL;
	ReplacementPolicy policy;
	unsigned long long addr;

	//int index = 0; //We don't need another index variable as a list is already an ordered data structure.
};
