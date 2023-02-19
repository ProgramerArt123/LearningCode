#include <iostream>
#include <algorithm>
#include <thread>
#include "Code/Code.h"
#include "Code/Lexis.h"
#include "Code/SourcePath.h"
#include "Code/SourceFile.h"
#include "Code/SourceFileBatch.hpp"
#include "Description.h"
#include "Code/Char.h"
#include "Code/Element.h"
#include "CodeLearning.h"


namespace code_learning {
	namespace statistics {
		CodeLearning::CodeLearning(const char *name, int argc, char *argv[]) :
			m_board(name, argc, argv), m_glob(m_cfg, m_board){

		}

		CodeLearning::~CodeLearning() {
			while (m_learning_count) {
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
		}

		static void LearningThread(void *learning, void *source) {
			((CodeLearning*)learning)->Learning(*(code::SourcePath*)source);
			((code::SourcePath*)source)->m_is_learning = false;
			((CodeLearning*)learning)->m_learning_count--;
		}

		void CodeLearning::StartLearning(code::SourcePath &source) {
			m_learning_count++;
			source.m_is_learning = true;
			std::thread(LearningThread, (void*)this, (void*)&source).detach();
		}

		void CodeLearning::Learning(code::Source &source) {
			m_board.IncrementalTotalCodesCount(source.Scan(m_glob));
			source.CallBack([&](const code::Element &element) {
				m_statistics.push_back(Path::CreateStatistic(element, m_glob));
				m_statistics.back()->Statistics(element);
			});
		}

		
	}
}