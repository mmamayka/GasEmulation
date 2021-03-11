#ifndef OS_DEPENDENT_H
#define OS_DEPENDENT_H

#include <cstddef>

namespace Memory {
	extern size_t const PAGE_SIZE;

	void* const PageAlloc(size_t npages);
	void PageFree(void* addr, size_t npages);
	void PageCommit(void* ppage, size_t count);
}

#endif
