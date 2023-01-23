#ifndef __CODE_LEARNING_STATISTICS_CODE_LEARNING_H__
#define __CODE_LEARNING_STATISTICS_CODE_LEARNING_H__

#include <memory>
#include <map>
#include <string>
#include "Glob.h"
#include "Region.h"
#include "SummaryBoard.h"

namespace code_learning {
	namespace code {
		class Source;
		class SourceFile;
		class SourceFileBatch;
	}

	namespace statistics {

		class CodeLearning : public Region {
		public:
			explicit CodeLearning(const char *name);

			template<typename T>
			void SetIgnores(T ignore) {
				m_cfg.ignores.insert(ignore);
			}

			template<typename T, typename ...Ts>
			void SetIgnores(T ignore, Ts ...ignores) {
				m_cfg.ignores.insert(ignore);
				SetIgnores(ignores...);
			}

			template<typename T>
			void SetSplits(T split) {
				m_cfg.splits.insert(split);
			}

			template<typename T, typename ...Ts>
			void SetSplits(T split, Ts ...splits) {
				m_cfg.splits.insert(split);
				SetSplits(splits...);
			}

			void Learning(code::Source &source);
			void Summary() const override;
		private:
			void ProcessSymmetries();
			void ProcessSymmetry(const code::Symmetry &symmetry);
		private:
			uint64_t m_file_count = 0;

			Config m_cfg;

			Glob m_glob;

			SummaryBoard m_board;
		};
	}
}

#endif