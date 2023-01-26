#include <boost/filesystem.hpp>
#include "Source.h"

namespace code_learning {

	namespace code {
		Source::Source(const char *fileName) :m_file_name(fileName) {
			const boost::filesystem::path dir(m_file_name);
			m_name = dir.filename().string();
		}
	}

}