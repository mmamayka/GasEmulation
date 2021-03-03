#include "debug.hpp"

Debug::StacktraceFrameBase::StacktraceFrameBase(char const* func, char const* file, 
	size_t line, StacktraceFrameBase* next) :

	func_(func),
	file_(file),
	line_(line),
	next_(next)
{
	assert(func != nullptr);
	assert(file != nullptr);
}

Debug::StacktraceFrameBase* Debug::StacktraceFrameBase::getNext() const {
	return next_;
}

Debug::Stacktrace& Debug::Stacktrace::GetInstance() {
	static Stacktrace Instance;
	return Instance;
}

Debug::Stacktrace::~Stacktrace() {
	while(first_frame_ != nullptr)
		popFrame();
}

void Debug::Stacktrace::popFrame() {
	assert(first_frame_ != nullptr);

	StacktraceFrameBase* next = first_frame_->getNext();
	delete first_frame_;
	first_frame_ = next;
}

void Debug::Stacktrace::print(std::ostream& ostream) const {
	ostream << "stacktrace:\n";

	StacktraceFrameBase* cur = first_frame_;
	while(cur != nullptr) {
		cur->print(ostream);
		cur = cur->getNext();
	}
}

Debug::StacktraceFrameGuard::~StacktraceFrameGuard() {
	Stacktrace::GetInstance().popFrame();
}


