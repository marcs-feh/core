#include <unistd.h>

#include "print.hh"
#include "context.hpp"

int main(){
	print(context::os_name, context::posix_version);
	return 0;
}
