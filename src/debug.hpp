#ifndef S4LIB_DEBUG_HPP
#define S4LIB_DEBUG_HPP

#include <cstddef>
#include <tuple>
#include <iostream>
#include <cassert>

#ifdef NDEBUG

#define $$
#define $_

#define ASSERT(expr)
#define ASSERT_(...)

#else

#define $$ \
	Debug::StacktraceFrameGuard STKTRC_FRM_GRD_(__PRETTY_FUNCTION__, __FILE__, __LINE__);

#define $_(...) \
	Debug::StacktraceFrameGuard STKTRC_FRM_GR_(__PRETTY_FUNCTION__, __FILE__, __LINE__, \
		__VA_ARGS__);

#define ASSERT_(expr, func, file, line) 												\
	do { 																				\
		if(!(expr)) { 																	\
			std::cerr << "assertion failed at function \"" << func << "\" of " << 		\
				file << ":" << line << std::endl; 										\
			Debug::Stacktrace::GetInstance().print(std::cerr); 							\
			assert(expr); 																\
		} 																				\
	} while(false);

#define ASSERT(expr) ASSERT_(expr, __PRETTY_FUNCTION__, __FILE__, __LINE__)

#endif

// TODO: add thread_local to stacktrace instance

namespace Debug {
	namespace Priv {
		template<size_t...> struct Sequence {};

		template<size_t N, size_t... Is>
		struct GenSequence : GenSequence<N - 1, N - 1, Is...> {};

		template<size_t... Is>
		struct GenSequence<0, Is...> : Sequence<Is...> {};

		template<typename Tuple, size_t... Is>
		void PrintTuple(std::ostream& stream, Tuple const& tuple, Sequence<Is...>);
	}

	template<typename... Args>
	std::ostream& operator<< (std::ostream& stream, std::tuple<Args...> const& tuple);

	class StacktraceFrameBase {
	protected:
		friend class Stacktrace;

		StacktraceFrameBase(char const* func, char const* file, size_t line,
			StacktraceFrameBase* next);

		virtual ~StacktraceFrameBase() = default;

		virtual void print(std::ostream& stream) const = 0;

		StacktraceFrameBase* getNext() const;

		char const* func_;
		char const* file_;
		size_t line_;

		StacktraceFrameBase* next_;
	};

	template<typename... TArgs>
	class StacktraceFrame final : public StacktraceFrameBase {
	protected:
		friend class Stacktrace;

		StacktraceFrame(char const* func, char const* file, size_t line, 
			StacktraceFrameBase* next, TArgs... other);

		void print(std::ostream& stream) const;

	private:
		std::tuple<TArgs...> args_;
	};

	class Stacktrace final {
	protected:
		friend class StacktraceFrameGuard;

		template<typename... TArgs>
		void pushFrame(char const* func, char const* file, size_t line, TArgs... args);
		void popFrame();

	public:
		void print(std::ostream& ostream) const;
		static Stacktrace& GetInstance();

	private:
		Stacktrace() = default;
		~Stacktrace();

		StacktraceFrameBase* first_frame_;
	};

	class StacktraceFrameGuard final {
	public:
		template<typename... TArgs>
		StacktraceFrameGuard(char const* func, char const* file, size_t line, 
			TArgs... args);
		~StacktraceFrameGuard();
	};
}

#include "debug.inl"

#endif
