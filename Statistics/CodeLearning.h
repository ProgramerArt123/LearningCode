#ifndef __CODE_LEARNING_STATISTICS_CODE_LEARNING_H__
#define __CODE_LEARNING_STATISTICS_CODE_LEARNING_H__

#include <memory>
#include <map>
#include <string>
#include "Glob.h"
#include "Path.h"
#include "GUI/SummaryBoard.h"

namespace code_learning {
	namespace code {
		class Source;
		class SourcePath;
		class SourceFile;
		class SourceFileBatch;
	}

	namespace statistics {

		class CodeLearning  {
		public:
			CodeLearning(const char *name, int argc, char *argv[]);
			virtual ~CodeLearning();


			void SetIgnores(char ignore) {
				m_cfg.ignores.insert(ignore);
			}

			template<typename ...IGNORES>
			void SetIgnores(char ignore, IGNORES ...ignores) {
				m_cfg.ignores.insert(ignore);
				SetIgnores(ignores...);
			}

			void SetSplits(char split) {
				m_cfg.splits.insert(split);
			}

			template<typename ...SPLITS>
			void SetSplits(char split, SPLITS ...splits) {
				m_cfg.splits.insert(split);
				SetSplits(splits...);
			}

			void StartLearning(code::SourcePath &source);

			void Learning(code::Source &source);

			GUI::SummaryBoard m_board;

			std::atomic_uint64_t m_learning_count = 0;
		private:
			Config m_cfg;

			Glob m_glob;

			std::list<std::shared_ptr<statistics::Element>> m_statistics;

		};
	}
}

#endif