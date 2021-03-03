#ifndef TESTS_HPP
#define TESTS_HPP

#include <ostream>
#include <map>
#include <stdexcept>

#define UNIT_UNWRAP_AGAIN_(x) x
#define UNIT_UNWRAP_(x) UNIT_UNWRAP_AGAIN_(x)

#define UNIT_CONCAT_TWICE_AGAIN_(x, y) x ## y
#define UNIT_CONCAT_AGAIN_(x, y) UNIT_CONCAT_TWICE_AGAIN_(x, y)
#define UNIT_CONCAT_(x, y) UNIT_CONCAT_AGAIN_(x, y)

#define UNIT_TEST_(count, name, group, ...) \
	static void UNIT_CONCAT_(UTEST_, count) ();   \
	int  UNIT_CONCAT_(ITEST_, count) =     \
		Tests::AUX::MakeUnitTest(group, name, UNIT_CONCAT_(UTEST_, count)); \
	static void UNIT_CONCAT_(UTEST_, count) () 

#define UNIT_TEST(...) UNIT_TEST_(__COUNTER__, __VA_ARGS__, "default")

#define UNIT_ASSERT(expr) \
	do { \
		if(!(expr)) \
			throw Tests::AUX::UnitTestAssert(#expr); \
	} while(0)

#define UNIT_NASSERT(expr) UNIT_ASSERT(!(expr))

namespace Tests {
	void RunAllTests();
	void RunGroup(char const* name);

	namespace AUX {
		class UnitTestAssert : public std::runtime_error {
		public:
			UnitTestAssert(char const* message) : runtime_error(message) {}
		};

		class UnitTest {
		protected:
			using Function = void(*)();

			friend class UnitTestsGroup;
			friend int const MakeUnitTest(char const* group, char const* name, 
				UnitTest::Function func);
			

			UnitTest(char const* name, Function func);
			bool const run(std::ostream& log_stream) const;

			char const* getName() const { return name_; }

		private:
			char const* name_;
			Function func_;
		};

		class UnitTestsGroup {
		protected:
			friend int const MakeUnitTest(char const* group, char const* name, 
				UnitTest::Function func);

			friend void ::Tests::RunAllTests();
			friend void ::Tests::RunGroup(char const* name);

			UnitTestsGroup(char const* name);
			bool const run(std::ostream& log_stream) const;

			char const* getName() const { return name_; }

			bool const reg(char const* name, UnitTest::Function func_);

		private:
			char const* name_;
			std::map<char const*, UnitTest> tests_;
		};

		int const MakeUnitTest(char const* group, char const* name, 
			UnitTest::Function func);
	}

};

#endif
