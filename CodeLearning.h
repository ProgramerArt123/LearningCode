#ifndef __CODE_LEARNING_CODE_LEARNING_H__
#define __CODE_LEARNING_CODE_LEARNING_H__

#include <memory>
#include <map>
#include <string>
#include "SourceFile.h"
#include "Config.h"

namespace code_learning {
	class CodeLearning {
	public:
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

		void Learning(SourceFile &source);
		void Summary();
	private:
		uint64_t m_file_count = 0;
		std::map<std::string, uint64_t> m_lexes;
		
		Config m_cfg;
	};
}

#endif