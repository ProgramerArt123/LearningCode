#include <boost/filesystem.hpp>
#include "Source.h"

namespace code_learning {

	namespace code {
		Source::Source(const std::string &fileName) :m_file_name(fileName) {
			const boost::filesystem::path dir(m_file_name);
			m_name = dir.filename().string();
			m_parent = dir.parent_path().string();
		}
		Source::~Source() {
			while (m_is_learning) {
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
		}
	}

}