#ifndef __CODE_LEARNING_CODE_SOURCE_PATH_H__
#define __CODE_LEARNING_CODE_SOURCE_PATH_H__

#include <memory>
#include <algorithm>
#include <boost/filesystem.hpp>
#include "Config.h"
#include "Code.h"
#include "Lexis.h"
#include "Source.h"
#include "Element.h"

namespace code_learning {
	namespace code {
		class SourcePath : public code::Composite<code::Element>, public Source{
		public:
			explicit SourcePath(const char *path);
			virtual ~SourcePath();
			uint64_t Scan(const Glob &glob) override;
			bool ContentAppend(char next, const Glob &glob) override;
			void Decomposition(const Glob &glob) override;
			void CallBack(std::function<void(const code::Element &)> factor) const override;
			
			void AddSuffixNames(const std::string &name) {
				m_suffix_names.insert(name);
			}

			template<typename ...NAMES>
			void AddSuffixNames(const std::string &name, const NAMES &...names) {
				m_suffix_names.insert(name);
				AddSuffixNames(names...);
			}

			void AddSourceFile(const char *fileName, SourcePath &source, const Glob &glob);
			void SearchFiles(const char *path, SourcePath &source, const Glob &glob);


		private:
			bool IsValidName(const std::string &name) const;
		private:
			std::set<std::string> m_suffix_names;
		};
	}
}

#endif