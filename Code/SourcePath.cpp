
#include "Config.h"
#include "SourceFile.h"
#include "SourcePath.h"
namespace code_learning {
	namespace code {
		SourcePath::SourcePath(const char *path) :
			Source(path) {
			m_type = ELEMENT_TYPE_PATH;
		}
		SourcePath::~SourcePath() {
		}
		uint64_t SourcePath::Scan(const Glob &glob) {
			SearchFiles(m_file_name.c_str(), *this, glob);
			Decomposition(glob);
			return m_file_count;
		}

		bool SourcePath::ContentAppend(char next, const Glob &glob) {
			return false;
		}

		void SourcePath::Decomposition(const Glob &glob) {
			for (auto &child : m_children.front()) {
				child->Decomposition(glob);
				const std::shared_ptr<code::Source> &path = 
					std::dynamic_pointer_cast<code::Source>(child);
				m_file_count += path->m_file_count;
			}
			Element::Decomposition(glob);
		}

		void SourcePath::CallBack(std::function<void(const code::Element &)> factor) const {
			factor(*this);
		}

		void SourcePath::AddSourceFile(const char *fileName, SourcePath &source, const Glob &glob) {
			m_children.front().push_back(std::shared_ptr<code::SourceFile>(
				new code::SourceFile(fileName)));
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
						m_children.front().push_back(std::shared_ptr<code::SourcePath>(
							new code::SourcePath(iter->path().string().c_str())));
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

