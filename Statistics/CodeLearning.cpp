#include <iostream>
#include <algorithm>
#include "Code/Code.h"
#include "Code/Lexis.h"
#include "Code/SourceFile.h"
#include "Code/SourceFileBatch.hpp"
#include "Description.h"
#include "Code/Char.h"
#include "Code/Element.h"
#include "CodeLearning.h"


namespace code_learning {
	namespace statistics {
		CodeLearning::CodeLearning(const char *name) :
			m_board(name), m_glob(m_cfg, m_board){

		}

		void CodeLearning::Learning(code::Source &source) {
			m_board.m_total_files_count += source.Scan(m_glob);
			source.Foreach([&](const code::Element &element) {
				switch (element.GetType())
				{
				case code::ELEMENT_TYPE_PATH:
					m_statistics.push_back(std::shared_ptr<statistics::Element>(new statistics::Path(element.GetContent(), m_glob)));
					break;
				case code::ELEMENT_TYPE_FILE:
					m_statistics.push_back(std::shared_ptr<statistics::Element>(new statistics::File(element.GetContent(), m_glob)));
					break;
				case code::ELEMENT_TYPE_CODE:
					m_statistics.push_back(std::shared_ptr<statistics::Element>(new statistics::Code(element.GetContent(), m_glob)));
					break;
				default:
					throw "error source";
					break;
				}
				m_statistics.back()->Statistics(element);
			});
		}

		
	}
}