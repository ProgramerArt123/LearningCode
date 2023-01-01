#include <iostream>
#include <algorithm>
#include "Lexis.h"
#include "SourceFile.h"
#include "SourceFileBatch.hpp"
#include "Description.h"
#include "CodeLearning.h"

namespace code_learning {

	CodeLearning::CodeLearning():m_glob(m_cfg), m_regions(m_glob) {

	}

	void CodeLearning::Learning(SourceFile &source) {
		m_file_count++;
		source.Scan(m_glob.m_cfg);
		Statistics(source);
		m_regions.Sort();
	}

	void CodeLearning::Learning(SourceFileBatch &sources) {
		for (auto &source: sources) {
			Learning(*source);
		}
	}
	
	void CodeLearning::Summary() {
		std::cout << "learn file[" << m_file_count << "]" << std::endl;
		std::cout << "learn lexis:" << std::endl;
		for (const auto &region : m_regions) {
			region->Summary();
		}
	}

	void CodeLearning::Statistics(const SourceFile &source) {
		source.Statistics(m_regions);
	}

}