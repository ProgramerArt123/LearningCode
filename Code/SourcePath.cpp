#include <boost/filesystem.hpp>
#include "Config.h"
#include "SourcePath.h"
namespace code_learning {
	namespace code {
		SourcePath::SourcePath(const char *path):m_path(path){
			
		}

		uint64_t SourcePath::Scan(const Glob &glob) {
			const boost::filesystem::path dir(m_path);
			const boost::filesystem::recursive_directory_iterator endIter;
			for (boost::filesystem::recursive_directory_iterator iter(dir); iter != endIter; iter++) {
				if (boost::filesystem::is_regular_file(*iter) &&
					iter->path().has_extension() &&
					IsValidName(iter->path().extension().generic_string())) {
					AddSourceFiles(iter->path().generic_string().c_str());
				}
			}
			return SourceFileBatch::Scan(glob);
		}

		bool SourcePath::IsValidName(const std::string &name) const {
			std::string lower;
			transform(name.begin(), name.end(), std::back_inserter(lower), tolower);
			return m_suffix_names.find(lower) != m_suffix_names.end();
		}
	}
}

