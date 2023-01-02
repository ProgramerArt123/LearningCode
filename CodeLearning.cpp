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
		
		std::cout << "#################################################" << std::endl;
		std::cout << "Symmetries:" << std::endl;
		for (auto &symmetry : m_symmetries) {
			std::cout << symmetry.first << ":" << symmetry.second << std::endl;
		}
	}

	void CodeLearning::Statistics(const SourceFile &source) {
		source.Statistics(m_regions);
		for (auto &region : m_regions) {
			for (auto &symmetry : region->m_element.m_symmetries) {
				m_symmetries[symmetry.first] += symmetry.second;
			}
		}
	}

	void CodeLearning::ProcessSymmetries() {
		ProcessSymmetry('(', ')');
		ProcessSymmetry('{', '}');
		ProcessSymmetry('[', ']');
		ProcessSymmetry('<', '>');
	}

	void CodeLearning::ProcessSymmetry(char left, char right) {
		if (m_symmetries[left] && m_symmetries[right]) {
			if (m_symmetries[left] == m_symmetries[right]) {
				m_glob.m_generate.symmetries.insert(std::make_pair(left, Symmetry(left, right)));
			}
			else if (m_symmetries[left] > m_symmetries[right] &&
				(float)(m_symmetries[right] * 100) / m_symmetries[left] >= m_cfg.symmetry_percent) {
				m_glob.m_generate.symmetries.insert(std::make_pair(left, Symmetry(left, right)));
			}
			else if (m_symmetries[right] > m_symmetries[left] &&
				(float)(m_symmetries[left] * 100) / m_symmetries[right] >= m_cfg.symmetry_percent) {
				m_glob.m_generate.symmetries.insert(std::make_pair(left, Symmetry(left, right)));
			}
			else {
				m_glob.m_generate.symmetries.erase(left);
			}
		}
	}

}