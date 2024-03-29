#include "Glob.h"
#include "Code.h"
namespace code_learning {
	namespace statistics {
		Code::Code(const std::string &content, Glob &glob):
			Region(content, glob){

		}
		void Code::Statistics(const code::Element &element) {
			Region::Statistics(element);
			ProcessSymmetries();
			static std::atomic_uint64_t finished = 0;
			finished ++;
			if (m_glob.m_board) {
				m_glob.m_board->SetFinishedCodesCount(finished);
			}
		}
		void Code::ProcessSymmetries() {
			const int count = sizeof(code::symmetries) / sizeof(code::Symmetry);
			for (int index = 0; index < count; index++) {
				ProcessSymmetry(code::symmetries[index]);
			}
		}

		void Code::ProcessSymmetry(const code::Symmetry &symmetry) {
			if (m_symmetries[symmetry.m_left] && m_symmetries[symmetry.m_right]) {
				if (m_symmetries[symmetry.m_left] == m_symmetries[symmetry.m_right]) {
					m_glob.m_generate.symmetries[symmetry.m_left] = symmetry;
				}
				else if (m_symmetries[symmetry.m_left] > m_symmetries[symmetry.m_right] &&
					m_glob.m_cfg.m_symmetry  < algorithm::Probability(m_symmetries[symmetry.m_right], m_symmetries[symmetry.m_left])) {
					m_glob.m_generate.symmetries[symmetry.m_left] = symmetry;
				}
				else if (m_symmetries[symmetry.m_right] > m_symmetries[symmetry.m_left] &&
					m_glob.m_cfg.m_symmetry < algorithm::Probability(m_symmetries[symmetry.m_left], m_symmetries[symmetry.m_right])) {
					m_glob.m_generate.symmetries[symmetry.m_left] = symmetry;
				}
				else {
					m_glob.m_generate.symmetries.erase(symmetry.m_left);
				}
			}
		}
	}
}