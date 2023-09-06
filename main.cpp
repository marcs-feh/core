#include <unistd.h>

#include "utils.hpp"
#include "assert.hpp"
#include "context.hpp"
#include "slice.hpp"
#include "view.hpp"

#include "print.hh"

#include  "tests/slice.cpp"
#include  "tests/view.cpp"

int main(){
	test_Slice();
	test_View();
	return 0;
}
