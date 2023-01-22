#ifndef __CODE_LEARNING_CODE_SOURCE_FILE_BATCH_HPP__
#define __CODE_LEARNING_CODE_SOURCE_FILE_BATCH_HPP__

#include <memory>
#include <list>
#include "SourceFile.h"

namespace code_learning {
	namespace code {
		class SourceFileBatch : public Source {
		public:
			SourceFileBatch() {
			}

			template<typename T>
			SourceFileBatch(T file) {
				AddSourceFiles(file);
			}

			template<typename T, typename ...Ts>
			SourceFileBatch(T file, Ts ...files) {
				AddSourceFiles(file, files...);
			}

			template<typename T>
			void AddSourceFiles(T file) {
				m_files.push_back(std::unique_ptr<SourceFile>(new SourceFile(file)));
			}

			template<typename T, typename ...Ts>
			void AddSourceFiles(T file, Ts ...files) {
				m_files.push_back(std::unique_ptr<SourceFile>(new SourceFile(file)));
				AddSourceFiles(files...);
			}

			uint64_t Scan(const Glob &glob) override {
				for (auto &file : m_files) {
					file->Scan(glob);
				}
				return m_files.size();
			}

			void Foreach(std::function<void(const std::string &, const std::list<std::unique_ptr<code::Region>> &)> factor) const override {
				for (const auto &file : m_files) {
					file->Foreach(factor);
				}
			}

		private:
			std::list<std::unique_ptr<SourceFile>> m_files;
		};
	}
}

#endif