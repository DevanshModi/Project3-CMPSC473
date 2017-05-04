#pragma once

#include <list>
#include "virtualMemoryManagerInterface.hpp"

// Structures
struct PageEntry
{
	int pageNum;
	int frameIndex;
	unsigned long long frameAddr;
};
struct PageTable
{
	// List contructor
	std::list<PageEntry> *table;

	// Initialize the page table
	PageTable() {
		table = new std::list<PageEntry>;
	}

	// Add new page to table
	void pushFIFO(PageEntry *page) {
		table->push_back(*page);
	}

	// Add new page to table
	void pushLRU(PageEntry *page) {
		table->push_front(*page);
	}

	// Remove the last page and return it
	PageEntry* popFIFO() {
		if (isEmpty())
			return NULL;
		PageEntry page = table->front();
		//free(&page);
		table->pop_front();
	}

	// Remove the last page and return it
	PageEntry* popLRU() {
		if (isEmpty())
			return NULL;
		PageEntry page = table->back();
		//free(&page);
		table->pop_back();
	}

	// Checks if page is in page table and return index to physical memory location if it is
	int inTable(unsigned long long addr, unsigned int N) {
		for (std::list<PageEntry>::iterator list_iter = table->begin(); list_iter != table->end(); list_iter++) {
			if ((list_iter)->pageNum == (addr / pow(2, N)))
				return (list_iter)->frameIndex;
		}
		return -1;	// returns -1 if not in page table
	}

	// Checks size of page table
	unsigned int size() {
		return table->size();
	}

	// Checks if page table is empty
	bool isEmpty() {
		return table->empty();
	}
};


class memoryManager : public virtualMemoryManagerInterface {
public:
	memoryManager(ReplacementPolicy p, unsigned int pS, unsigned int nF, unsigned int vA) : virtualMemoryManagerInterface(p, pS, nF, vA) {
		pageTable = new PageTable();
		policy = p;
	}
	unsigned long long memoryAccess(unsigned long long address) override;
	void swap(unsigned int frameNumber, unsigned int pageNumber);
	void newPageEntry(unsigned long long addr, int frameIndex);

private:
	PageTable *pageTable = NULL;
	PageEntry *page = NULL;
	ReplacementPolicy policy;
	unsigned long long addr;
	int index = -1;
};