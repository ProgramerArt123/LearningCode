#include <iostream>
#include <algorithm>
#include "Code/Code.h"
#include "Code/Lexis.h"
#include "Code/SourceFile.h"
#include "Code/SourceFileBatch.hpp"
#include "Description.h"
#include "Code/Char.h"
#include "CodeLearning.h"


namespace code_learning {
	namespace statistics {
		CodeLearning::CodeLearning(const char *name) :
			m_glob(m_cfg), m_code("", m_glob), m_board(name){

		}

		void CodeLearning::Learning(code::Source &source) {
			m_file_count += source.Scan(m_glob);
			m_board.m_total_files_count = m_file_count;
			source.Foreach([&](const std::string &fileName, const std::vector<std::list<std::shared_ptr<code::Element>>> &children) {
				for (const auto &region : children.front()) {
					m_code.Statistics(*region);
				}
				m_board.UpdateProcessing(fileName);
				m_board.m_finished_files_count++;
			});
		}

		
	}
}