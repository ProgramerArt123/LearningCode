#include <iostream>
#include <algorithm>
#include "Code/Lexis.h"
#include "SourceFile.h"
#include "SourceFileBatch.hpp"
#include "Description.h"
#include "CodeLearning.h"
#include "Char.h"

namespace code_learning {

	CodeLearning::CodeLearning():m_glob(m_cfg), m_regions(m_glob) {

	}

	void CodeLearning::Learning(SourceFile &source) {
		m_file_count++;
		source.Scan(m_glob);
		Statistics(source);
		m_regions.Sort();
		ProcessSymmetries();
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
		
		m_glob.m_generate.Summary();
	}

	void CodeLearning::Statistics(const SourceFile &source) {
		source.Statistics(m_regions);
		for (auto &region : m_regions) {
			for (auto &symmetry : region->GetSymmetries()) {
				m_symmetries[symmetry.first] += symmetry.second;
			}
		}
	}

	void CodeLearning::ProcessSymmetries() {
		const int count = sizeof(symmetries) / sizeof(Symmetry);
		for (int index = 0; index < count; index ++) {
			ProcessSymmetry(symmetries[index]);
		}
	}

	void CodeLearning::ProcessSymmetry(const Symmetry &symmetry) {
		if (m_symmetries[symmetry.m_left] && m_symmetries[symmetry.m_right]) {
			if (m_symmetries[symmetry.m_left] == m_symmetries[symmetry.m_right]) {
				m_glob.m_generate.symmetries[symmetry.m_left] = symmetry;
			}
			else if (m_symmetries[symmetry.m_left] > m_symmetries[symmetry.m_right] &&
				(float)(m_symmetries[symmetry.m_right] * 100) / m_symmetries[symmetry.m_left] >= m_cfg.symmetry_percent) {
				m_glob.m_generate.symmetries[symmetry.m_left] = symmetry;
			}
			else if (m_symmetries[symmetry.m_right] > m_symmetries[symmetry.m_left] &&
				(float)(m_symmetries[symmetry.m_left] * 100) / m_symmetries[symmetry.m_right] >= m_cfg.symmetry_percent) {
				m_glob.m_generate.symmetries[symmetry.m_left] = symmetry;
			}
			else {
				m_glob.m_generate.symmetries.erase(symmetry.m_left);
			}
		}
	}

}