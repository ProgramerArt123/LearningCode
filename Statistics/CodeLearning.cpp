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
		CodeLearning::CodeLearning(const char *name) :
			m_name(name) ,m_glob(m_cfg, m_board){

		}

		CodeLearning::~CodeLearning() {
			while (m_learning_count) {
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
		}

		static void LearningThread(std::tuple<CodeLearning&, code::Source&> params) {
			CodeLearning& learning = std::get<0>(params);
			code::Source& source = std::get<1>(params);
			learning.Learning(source);
			source.m_is_learning = false;
			learning.m_learning_count--;
		}

		void CodeLearning::StartLearning(code::Source &source) {
			m_learning_count++;
			source.m_is_learning = true;
			std::thread(LearningThread, 
				std::tuple<CodeLearning&, code::Source&>{*this, source}).detach();
		}

		void CodeLearning::Learning(code::Source &source) {
			IncrementalTotalCodesCount(source.Scan(m_glob));
			source.CallBack([&](const code::Element &element) {
				std::shared_ptr<statistics::Element> statistics = Path::CreateStatistic(element, m_glob);
				statistics->Statistics(element);
				std::lock_guard<std::mutex> lock(m_learning_mutex);
				m_statistics.push_back(statistics);
			});
		}

		void CodeLearning::IncrementalTotalCodesCount(uint64_t increment) {
			static std::atomic_uint64_t total = 0;
			total += increment;
			if (m_board) {
				m_board->SetTotalCodesCount(total);
			}
		}

		void CodeLearning::Display(int argc, char *argv[]) {
			m_board = std::shared_ptr<GUI::SummaryBoard>(
				new GUI::SummaryBoard(m_name.c_str(), argc, argv));
			m_board->Display();
		}
	}
}