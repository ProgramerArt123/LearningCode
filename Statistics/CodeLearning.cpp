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
			m_board.m_total_codes_count += source.Scan(m_glob);
			source.CallBack([&](const code::Element &element) {
				m_statistics.push_back(Path::CreateStatistic(element, m_glob));
				m_statistics.back()->Statistics(element);
			});
		}

		
	}
}