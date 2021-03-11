#if defined unix || defined __unix || defined __unix__

#include <unistd.h> // getpagesize
#include <sys/mman.h> // mmap, munmap

#endif

#if defined _WIN32 || defined _WIN64

#include <Windows.h> // VirtualAlloc, GetSystemInfo

#endif

#include <new> // std::bad_alloc
#include "osdependent.hpp"

namespace Memory {
	static size_t const GetPageSize() noexcept;

	size_t const PAGE_SIZE = GetPageSize();

#if defined unix || defined __unix || defined __unix__

	void* const PageAlloc(size_t npages) {
		void* mem = mmap(nullptr, npages * PAGE_SIZE,
			PROT_NONE, MAP_PRIVATE | MAP_NORESERVE, -1, 0);

		if(mem == nullptr) {
			throw std::bad_alloc();
		}
		return mem;
	}

	void PageFree(void* addr, size_t npages) {
		if(munmap(addr, npages * PAGE_SIZE)) {
			throw std::bad_alloc();
		}
	}

	void PageCommit(void* ppage, size_t count) {
		if(mprotect(ppage, PAGE_SIZE * count, PROT_READ | PROT_WRITE)) {
			throw std::bad_alloc();
		}
	}

	static size_t const GetPageSize() noexcept {
		return static_cast<size_t>(getpagesize());
	}

#endif

#if defined _WIN32 || defined _WIN64

void* const PageAlloc(size_t npages) {
	void* mem = VirtualAlloc(nullptr, npages * PAGE_SIZE, MEM_RESERVE, PAGE_NOACCESS);

	if(mem == NULL) {
		throw std::bad_alloc();
	}

	return mem;
}

void PageFree(void* addr, size_t npages) {
	if(!VirtualFree(addr, npages * PAGE_SIZE, MEM_RELEASE)) {
		throw std::bad_alloc();
	}
}

void PageCommit(void* ppage, size_t count) {
	if(!VirtualAlloc(ppage, count * PAGE_SIZE, MEM_COMMIT, PAGE_READWRITE)) {
		throw std::bad_alloc();
	}
}

static size_t const GetPageSize() noexcept {
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	return static_cast<size_t>(si.dwPageSize);
}

#endif
}
