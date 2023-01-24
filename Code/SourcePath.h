#ifndef __CODE_LEARNING_CODE_SOURCE_PATH_H__
#define __CODE_LEARNING_CODE_SOURCE_PATH_H__

#include <memory>
#include <algorithm>
#include <boost/filesystem.hpp>
#include "Config.h"
#include "Code.h"
#include "Lexis.h"
#include "Source.h"

namespace code_learning {
	namespace code {
		class SourcePath : public Source {
		public:
			explicit SourcePath(const char *path);
			uint64_t Scan(const Glob &glob) override;
			void Foreach(std::function<void(const std::string &, const std::vector<std::list<std::shared_ptr<code::Element>>> &)> factor) const override;
			template<typename T>
			void AddSuffixNames(T name) {
				m_suffix_names.insert(name);
			}

			template<typename T, typename ...Ts>
			void AddSuffixNames(T name, Ts ...names) {
				m_suffix_names.insert(name);
				AddSuffixNames(names...);
			}

			void AddSourceFile(const char *fileName, SourcePath &source, const Glob &glob);
			void SearchFiles(const char *path, SourcePath &source, const Glob &glob);
		private:
			bool IsValidName(const std::string &name) const;
		private:
			const std::string m_path;
			std::set<std::string> m_suffix_names;
			std::map<std::string, std::shared_ptr<Source>> m_files;
		};
	}
}

#endif