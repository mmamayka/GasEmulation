#include <cassert>
#include <sstream>
#include <iostream>
#include "tests.hpp"

namespace Tests {
	namespace AUX {
		static std::map<char const*, AUX::UnitTestsGroup>& GetGroups_() {
			static std::map<char const*, AUX::UnitTestsGroup> Groups_;
			return Groups_;
		}

		UnitTest::UnitTest(char const* name, Function func) :
			name_(name), func_(func)
		{
			assert(name != NULL);
			assert(func != NULL);
		}

		bool const UnitTest::run(std::ostream& log_stream) const {
			log_stream << "\tTEST \'" << name_ << "\' STATUS - ";

			bool ok = true;
			try {
				func_();
			}
			catch(UnitTestAssert& err) {
				log_stream << "FAILED AT \'" << err.what() << "\'\n";
				ok = false;
			}
			
			if(ok) {
				log_stream << "OK\n";
			}

			return ok;
		}

		UnitTestsGroup::UnitTestsGroup(char const* name) :
			name_(name) 
		{
			assert(name != NULL);
		}

		bool const UnitTestsGroup::run(std::ostream& log_stream) const {
			std::ostringstream log_buffer;

			bool ok = true;
			for(auto const& test : tests_) {
				ok |= test.second.run(log_buffer);
			}

			log_stream << "GROUP \'" << name_ << "\' STATUS - " <<
				(ok ? "OK" : "FAILED") << '\n' << log_buffer.str() << '\n';

			return ok;
		}

		bool const UnitTestsGroup::reg(char const* name, UnitTest::Function func) {
			assert(name != NULL);
			assert(func != NULL);
			assert(tests_.find(name) == tests_.end());

			tests_.insert(std::make_pair(name, UnitTest(name, func)));
			return true;
		}

		int const MakeUnitTest(char const* group, char const* name, 
			UnitTest::Function func)
		{
			assert(group != NULL);
			assert(name != NULL);
			assert(func != NULL);

			auto itr = AUX::GetGroups_().find(group);
			if(itr == AUX::GetGroups_().end()) {
				itr = AUX::GetGroups_().insert(
					std::make_pair(group, UnitTestsGroup(group))).first;
			}

			itr->second.reg(name, func);

			return 0;
		}
	}

	void RunAllTests() {
		bool ok = true;
		for(auto const& group : AUX::GetGroups_()) {
			ok |= group.second.run(std::cerr);
		}

		if(!ok) {
			std::cerr << "TESTS FAILED" << std::endl;
		}
	}

	void RunGroup(char const* name) {
		auto itr = AUX::GetGroups_().find(name);
		if(itr == AUX::GetGroups_().end()) {
			std::cerr << "INVALID GROUP NAME" << std::endl;
		}

		bool ok = itr->second.run(std::cerr);
		if(!ok) {
			std::cerr << "TESTS FAILED" << std::endl;
		}
	}
}
