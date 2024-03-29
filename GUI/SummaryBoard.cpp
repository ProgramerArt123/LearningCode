
#include "SummaryBoard.h"

namespace code_learning {

	namespace GUI {

		SummaryBoard::SummaryBoard(const char *title, int argc, char *argv[]) :
			m_title(title)
#ifndef CONSOLE
			,m_app(argc, argv),
			m_window(m_title)
#endif // !CONSOLE
		{
		}

		SummaryBoard::~SummaryBoard() {
			
		}

		void SummaryBoard::Display() {
#ifdef CONSOLE
			while (true) {
				Flush();
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
#else
			m_window.show();
			m_app.exec();
#endif
		}

		void SummaryBoard::SetTotalCodesCount(uint64_t total) {
			m_total_codes_count = total;
#ifndef CONSOLE
			emit m_window.UpdateProgressSignal(m_finished_codes_count, m_total_codes_count);
#endif // !CONSOLE
		}

		void SummaryBoard::SetFinishedCodesCount(uint64_t finished) {
			m_finished_codes_count = finished;
#ifndef CONSOLE
			emit m_window.UpdateProgressSignal(m_finished_codes_count, m_total_codes_count);
#endif // !CONSOLE
		}

		void SummaryBoard::UpdateProcessingCodes(const std::string &processing) {
			std::lock_guard<std::mutex> lock(m_disply_mutex);
			m_processing_codes = processing;
#ifndef CONSOLE
			emit m_window.UpdateCodesSignal(m_processing_codes.c_str());
#endif // !CONSOLE
		}

		void SummaryBoard::UpdateProcessingPath(const std::string &processing) {
			std::lock_guard<std::mutex> lock(m_disply_mutex);
			m_processing_path = processing;
#ifndef CONSOLE
			emit m_window.UpdatePathSignal(m_processing_path.c_str());
#endif // !CONSOLE
		}

		void SummaryBoard::Flush() {
#ifdef CONSOLE
			system("cls");
			const char *frame = "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
			size_t frameWidth = strlen(frame);
			std::cout << frame << std::endl;
			const std::string &titleItem = "Welcome " + m_title + " Learning !";
			const size_t margin = (frameWidth - titleItem.size() - 2) / 2;
			std::cout << "+";
			for (size_t index = 0; index < margin; index++) {
				std::cout << " ";
			}
			std::cout << titleItem;
			for (size_t index = 0; index < margin; index++) {
				std::cout << " ";
			}
			std::cout << "+" << std::endl;
			std::cout << frame << std::endl << std::endl;
			std::cout << "total codes:" << m_total_codes_count << std::endl << std::endl;
			std::cout << "finish codes:" << m_finished_codes_count << std::endl << std::endl;
			boost::progress_display progress(m_total_codes_count, std::cout, "percent: ", "         ", "progress:");
			progress += m_finished_codes_count;
			std::cout << std::endl << std::endl;
			if (0 == m_total_codes_count || m_finished_codes_count < m_total_codes_count) {
				std::lock_guard<std::mutex> lock(m_disply_mutex);
				std::cout << "module:" << m_processing_path << std::endl << std::endl;
				std::cout << "codes:" << m_processing_codes << std::endl << std::endl;
			}
			else {
				std::cout << "completed!" << std::endl << std::endl;
			}

#endif
		}
	}
}