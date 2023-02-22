#ifndef __CODE_LEARNING_GUI_SUMMARY_BOARD_H__
#define __CODE_LEARNING_GUI_SUMMARY_BOARD_H__
//#define CONSOLE
#include <thread>
#include <mutex>
#include <atomic>
#ifdef CONSOLE
#include <boost/progress.hpp>
#else
#include <QApplication>
#include "mainwindow.h"
#endif // CONSOLE

namespace code_learning {

	namespace GUI {

		class SummaryBoard {
		public:
			explicit SummaryBoard(const char *title, int argc, char *argv[]);
			virtual ~SummaryBoard();
			void Display();
			void IncrementalTotalCodesCount(uint64_t increment);
			void IncrementalFinishedCodesCount();
			void UpdateProcessingCodes(const std::string &processing);
			void UpdateProcessingPath(const std::string &processing);
			void Flush();

#ifndef CONSOLE
			QApplication m_app;
			MainWindow m_window;
#endif // !CONSOLE
		private:
			std::mutex m_disply_mutex;
			std::string m_processing_codes;
			std::string m_processing_path;
			std::atomic_uint64_t m_total_codes_count = 0;
			std::atomic_uint64_t m_finished_codes_count = 0;

			const std::string m_title;

		};
	}
}

#endif