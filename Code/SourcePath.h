#ifndef __CODE_LEARNING_CODE_SOURCE_PATH_H__
#define __CODE_LEARNING_CODE_SOURCE_PATH_H__

#include <memory>
#include <algorithm>
#include "Config.h"
#include "Code.h"
#include "Lexis.h"
#include "SourceFileBatch.hpp"

namespace code_learning {
	namespace code {
		class SourcePath : public SourceFileBatch {
		public:
			explicit SourcePath(const char *path);
			uint64_t Scan(const Glob &glob) override;

			template<typename T>
			void AddSuffixNames(T name) {
				m_suffix_names.insert(name);
			}

			template<typename T, typename ...Ts>
			void AddSuffixNames(T name, Ts ...names) {
				m_suffix_names.insert(name);
				AddSuffixNames(names...);
			}

		private:
			bool IsValidName(const std::string &name) const;

		private:
			const std::string m_path;
			std::set<std::string> m_suffix_names;
		};
	}
}

#endif