#ifndef __CODE_LEARNING_SOURCE_FILE_BATCH_HPP__
#define __CODE_LEARNING_SOURCE_FILE_BATCH_HPP__

#include <memory>
#include <list>
#include "SourceFile.h"

namespace code_learning {
	
	class SourceFileBatch {
	public:
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

		std::list<std::unique_ptr<SourceFile>>::const_iterator begin() const {
			return m_files.begin();
		}
		std::list<std::unique_ptr<SourceFile>>::const_iterator end() const {
			return m_files.end();
		}

	private:
		std::list<std::unique_ptr<SourceFile>> m_files;
	};

}

#endif