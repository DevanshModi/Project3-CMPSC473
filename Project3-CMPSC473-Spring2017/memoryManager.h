#pragma once

#include <list>
#include "virtualMemoryManagerInterface.hpp"

// Local Variables
ReplacementPolicy policy;

// Structures
struct PageEntry
{
	unsigned long long addr;
	unsigned int frameNum;
	unsigned int pageNum;
	unsigned int counter;
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
		table->push_back(page);	/// TODO:	figure out why page argument can't be pushed into table
	}

	// Remove the last page and return it
	PageEntry* pop() {
		if (isEmpty())
			return NULL;
		PageEntry *page = table->front();	/// TODO:	figure out why referenced page can't be created from popped element
		table->pop_front();
		return page;
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

private:

	PageTable *pageTable = NULL;
	int mycounter = 0;
	int myNumSwaps = 0;

};