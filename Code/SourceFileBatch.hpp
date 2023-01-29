#ifndef __CODE_LEARNING_CODE_SOURCE_FILE_BATCH_HPP__
#define __CODE_LEARNING_CODE_SOURCE_FILE_BATCH_HPP__

#include <memory>
#include <list>
#include "SourceFile.h"

namespace code_learning {
	namespace code {
		class SourceFileBatch : public Source {
		public:
			SourceFileBatch():Source("[batch]"){
			}

			SourceFileBatch(const std::string &fileName) :Source("[batch]") {
				AddSourceFiles(fileName);
			}

			template<typename ...FILENAMES>
			SourceFileBatch(const std::string &fileName, const FILENAMES &...fileNames) {
				AddSourceFiles(fileName, fileNames...);
			}

			void AddSourceFiles(const std::string &fileName) {
				m_files.push_back(std::unique_ptr<SourceFile>(new SourceFile(fileName)));
			}

			template<typename ...FILENAMES>
			void AddSourceFiles(const std::string &fileName, FILENAMES ...fileNames) {
				m_files.push_back(std::unique_ptr<SourceFile>(new SourceFile(fileName)));
				AddSourceFiles(fileNames...);
			}

			uint64_t Scan(const Glob &glob) override {
				for (auto &file : m_files) {
					file->Scan(glob);
				}
				return m_files.size();
			}

			void CallBack(std::function<void(const code::Element &)> factor) const override {
				for (const auto &file : m_files) {
					file->CallBack(factor);
				}
			}

		private:
			std::list<std::unique_ptr<SourceFile>> m_files;
		};
	}
}

#endif