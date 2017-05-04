#pragma once

#include <list>
#include "virtualMemoryManagerInterface.hpp"

// Structures
struct PageEntry
{
	int pageNum;
	int counter;
	int validBit;
	double frameRef;
	double offset;
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
	void push(PageEntry *page) {
		table->push_back(*page);
	}

	// Remove the last page and return it
	PageEntry* pop() {
		if (isEmpty())
			return NULL;
		PageEntry page = table->front();
		free(&page);
		table->pop_front();
		//return &page;
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
		pageSize = pS;
		frameSize = nF;
		vAddrSize = vA;
	}
	unsigned long long memoryAccess(unsigned long long address) override;
	void swap(unsigned int frameNumber, unsigned int pageNumber);
	void newPageEntry(unsigned long long addr);

private:
	PageTable *pageTable = NULL;
	int accessCounter = 0;

	ReplacementPolicy policy;
	unsigned int pageSize, frameSize, vAddrSize;
	unsigned long long addr;
	PageEntry *page = NULL;
};