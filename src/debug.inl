
template<typename Tuple, size_t... Is>
void Debug::Priv::PrintTuple(std::ostream& stream, Tuple const& tuple, Sequence<Is...>) {
	// a bit of magic from stackoverflow
	using Swallow = int[];
	(void) Swallow {
		0,
		(void(stream << (Is == 0 ? "" : ", ") << std::get<Is>(tuple)), 0)...
	};
}

template<typename... Args>
std::ostream& Debug::operator<< (std::ostream& stream, std::tuple<Args...> const& tuple)
{
	stream << "( ";
	Priv::PrintTuple(stream, tuple, Priv::GenSequence<sizeof...(Args)>());
	return stream << " )";
}

template<typename... TArgs>
Debug::StacktraceFrame<TArgs...>::StacktraceFrame(char const* func, char const* file, 
	size_t line, StacktraceFrameBase* next, TArgs... other) :

	StacktraceFrameBase(func, file, line, next),
	args_(std::make_tuple(other...))
{}

template<typename... TArgs>
void Debug::StacktraceFrame<TArgs...>::print(std::ostream& stream) const {
	stream << '\t' << func_ << args_ << " at line " << line_ << " of \""
		<< file_ << '\"' << std::endl;
}

template<typename... TArgs>
void Debug::Stacktrace::pushFrame(char const* func, char const* file, 
	size_t line, TArgs...	args) {

	StacktraceFrameBase* new_frame = new(std::nothrow) StacktraceFrame<TArgs...>(
		func, file, line, first_frame_, args...);

	if(new_frame != nullptr) {
		first_frame_ = new_frame;
	}
}
template<typename... TArgs>
Debug::StacktraceFrameGuard::StacktraceFrameGuard(char const* func, char const* file, 
	size_t line, TArgs... args
) {
	Stacktrace::GetInstance().pushFrame(func, file, line, args...);
}

