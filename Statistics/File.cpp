
#include "File.h"

namespace code_learning {
	namespace statistics {
		File::File(const std::string &content, Glob &glob):
			Region(content, glob){

		}
	}
}