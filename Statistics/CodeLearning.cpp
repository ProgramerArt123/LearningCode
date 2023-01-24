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
			m_glob(m_cfg), File("", m_glob),m_board(name){

		}

		void CodeLearning::Learning(code::Source &source) {
			m_file_count += source.Scan(m_glob);
			m_board.m_total_files_count = m_file_count;
			source.Foreach([&](const std::string &fileName, const std::vector<std::list<std::shared_ptr<code::Element>>> &children) {
				for (const auto &region : children.front()) {
					Region::Statistics(*region);
				}
				m_board.UpdateProcessing(fileName);
				m_board.m_finished_files_count++;
			});
			ProcessSymmetries();
		}

		void CodeLearning::Summary() const {
			std::cout << "learn file[" << m_file_count << "]" << std::endl;
			std::cout << "learn lexis:" << std::endl;
			for (const auto &child : m_children) {
				for (const auto &region : *child) {
					region->Summary();
				}
			}
			m_glob.m_generate.Summary();
		}

		void CodeLearning::ProcessSymmetries() {
			const int count = sizeof(code::symmetries) / sizeof(code::Symmetry);
			for (int index = 0; index < count; index++) {
				ProcessSymmetry(code::symmetries[index]);
			}
		}

		void CodeLearning::ProcessSymmetry(const code::Symmetry &symmetry) {
			if (m_symmetries[symmetry.m_left] && m_symmetries[symmetry.m_right]) {
				if (m_symmetries[symmetry.m_left] == m_symmetries[symmetry.m_right]) {
					m_glob.m_generate.symmetries[symmetry.m_left] = symmetry;
				}
				else if (m_symmetries[symmetry.m_left] > m_symmetries[symmetry.m_right] &&
					m_symmetries[symmetry.m_right] * m_cfg.m_symmetry.denominator() >
					m_symmetries[symmetry.m_left] * m_cfg.m_symmetry.numerator()) {
					m_glob.m_generate.symmetries[symmetry.m_left] = symmetry;
				}
				else if (m_symmetries[symmetry.m_right] > m_symmetries[symmetry.m_left] &&
					m_symmetries[symmetry.m_left] * m_cfg.m_symmetry.denominator() >
					m_symmetries[symmetry.m_right] * m_cfg.m_symmetry.numerator()) {
					m_glob.m_generate.symmetries[symmetry.m_left] = symmetry;
				}
				else {
					m_glob.m_generate.symmetries.erase(symmetry.m_left);
				}
			}
		}
	}
}