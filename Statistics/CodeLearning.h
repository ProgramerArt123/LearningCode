#ifndef __CODE_LEARNING_STATISTICS_CODE_LEARNING_H__
#define __CODE_LEARNING_STATISTICS_CODE_LEARNING_H__

#include <memory>
#include <map>
#include <string>
#include "Glob.h"
#include "Path.h"
#include "SummaryBoard.h"

namespace code_learning {
	namespace code {
		class Source;
		class SourceFile;
		class SourceFileBatch;
	}

	namespace statistics {

		class CodeLearning  {
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
		
		private:
			Config m_cfg;

			SummaryBoard m_board;

			Glob m_glob;

			std::list<std::shared_ptr<statistics::Element>> m_statistics;

		};
	}
}

#endif