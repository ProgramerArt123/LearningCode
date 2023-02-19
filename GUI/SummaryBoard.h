#ifndef __CODE_LEARNING_GUI_SUMMARY_BOARD_H__
#define __CODE_LEARNING_GUI_SUMMARY_BOARD_H__

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

			std::atomic_bool m_is_stop = false;

			int m_argc = 0;
			char **m_argv = NULL;
			const std::string m_title; 
#ifndef CONSOLE
			std::unique_ptr<QApplication> m_app;
			std::unique_ptr<MainWindow> m_window;
#endif // !CONSOLE
		private:
			std::thread m_disply;
			std::mutex m_disply_mutex;
			std::string m_processing_codes;
			std::string m_processing_path;
			std::atomic_uint64_t m_total_codes_count = 0;
			std::atomic_uint64_t m_finished_codes_count = 0;


		};
	}
}

#endif