#include <boost/filesystem.hpp>
#include "Source.h"

namespace code_learning {

	namespace code {
		Source::Source(const char *fileName) {
			const boost::filesystem::path path(fileName);
			m_name = path.filename().string();
		}
	}

}