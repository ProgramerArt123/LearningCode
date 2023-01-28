#ifndef __CODE_LEARNING_SUMMARY_BOARD_H__
#define __CODE_LEARNING_SUMMARY_BOARD_H__

#include <thread>
#include <mutex>
#include <atomic>
#include <boost/progress.hpp>


namespace code_learning {

	class SummaryBoard {
	public:
		explicit SummaryBoard(const char *title);
		virtual ~SummaryBoard();
		void UpdateProcessingCodes(const std::string &processing);
		void UpdateProcessingPath(const std::string &processing);
		void Flush() ;
		
		std::atomic_uint64_t m_total_codes_count = 0;

		std::atomic_uint64_t m_finished_codes_count = 0;

		std::atomic_bool m_is_stop = false;
	private:
		std::thread m_disply;
		std::mutex m_disply_mutex;
		const std::string m_title;
		std::string m_processing_codes;
		std::string m_processing_path;
	};
}

#endif