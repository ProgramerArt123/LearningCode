#include "SummaryBoard.h"

namespace code_learning {
	static void Disply(SummaryBoard &board) {
		while (!board.m_is_stop) {
			board.Flush();
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}

	SummaryBoard::SummaryBoard(const char *title):
		m_title(title), m_disply(Disply, std::ref(*this)){
	}

	SummaryBoard::~SummaryBoard() {
		m_is_stop = true;
		m_disply.join();
	}

	void SummaryBoard::UpdateProcessing(const std::string &processing) {
		std::lock_guard<std::mutex> lock(m_disply_mutex);
		m_processing = processing;
	}

	void SummaryBoard::Flush()  {
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
		std::cout << "total files:" << m_total_files_count << std::endl << std::endl;
		std::cout << "finish files:" << m_finished_files_count << std::endl << std::endl;
		boost::progress_display progress(m_total_files_count, std::cout, "percent: ", "         ", "progress:");
		progress += m_finished_files_count;
		std::cout << std::endl << std::endl;
		std::lock_guard<std::mutex> lock(m_disply_mutex);
		std::cout << "processing:" << m_processing << std::endl << std::endl;
	}
}