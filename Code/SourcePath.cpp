#include <boost/filesystem.hpp>
#include "Config.h"
#include "SourceFile.h"
#include "SourcePath.h"
namespace code_learning {
	namespace code {
		SourcePath::SourcePath(const char *path):Source(path),
			m_path(path){
			
		}

		uint64_t SourcePath::Scan(const Glob &glob) {
			SearchFiles(m_path.c_str(), *this, glob);
			return m_file_count;
		}

		void SourcePath::Foreach(std::function<void(const std::string &, const std::list<std::unique_ptr<code::Region>> &)> factor) const {
			for (const auto &file : m_files) {
				file.second->Foreach(factor);
			}
		}

		void SourcePath::AddSourceFile(const char *fileName, SourcePath &source, const Glob &glob) {
			SourceFile *file = new SourceFile(fileName);
			source.m_files.insert(std::make_pair(file->m_name.c_str(), file));
			source.m_file_count += file->Scan(glob);
		}

		void SourcePath::SearchFiles(const char *path, SourcePath &source, const Glob &glob) {
			const boost::filesystem::path dir(path);
			const boost::filesystem::directory_iterator endIter;
			for (boost::filesystem::directory_iterator iter(dir); iter != endIter; iter++) {
				if (boost::filesystem::is_regular_file(*iter) &&
					iter->path().has_extension() &&
					IsValidName(iter->path().extension().string())) {
					AddSourceFile(iter->path().string().c_str(), source, glob);
				}
				else if (boost::filesystem::is_directory(*iter) &&
					!iter->path().filename_is_dot() &&
					!iter->path().filename_is_dot_dot()) {
					std::shared_ptr<SourcePath> child(new SourcePath(iter->path().string().c_str()));
					SearchFiles(iter->path().string().c_str(), *child, glob);
					if (child->m_file_count) {
						source.m_files.insert(std::make_pair(child->m_name, child));
						source.m_file_count += child->m_file_count;
					}
				}
			}
		}

		bool SourcePath::IsValidName(const std::string &name) const {
			std::string lower;
			transform(name.begin(), name.end(), std::back_inserter(lower), tolower);
			return m_suffix_names.find(lower) != m_suffix_names.end();
		}
	}
}

