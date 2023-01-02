#ifndef __CODE_LEARNING_CODE_LEARNING_H__
#define __CODE_LEARNING_CODE_LEARNING_H__

#include <memory>
#include <map>
#include <string>
#include "Glob.h"
#include "Statistics/Region.h"
#include "Frequency.hpp"
#include "ListMap.hpp"
#include "Descriptions.h"

namespace code_learning {

	class SourceFile;
	class SourceFileBatch;

	class CodeLearning {
	public:
		explicit CodeLearning();

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
		void Learning(SourceFileBatch &sources);
		void Summary();
	private:
		void Statistics(const SourceFile &source);
		void ProcessSymmetries();
		void ProcessSymmetry(char left, char right);
	private:
		uint64_t m_file_count = 0;
		
		Config m_cfg;

		Glob m_glob;

		ListMap<Frequency<statistics::Region>> m_regions;
	
		std::map<char, uint64_t> m_symmetries;
	};
}

#endif