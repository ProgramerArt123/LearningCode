#ifndef __CODE_LEARNING_GLOB_H__
#define __CODE_LEARNING_GLOB_H__

#include "Config.h"
#include "Statistics/Generate.h"
#include "GUI/SummaryBoard.h"

namespace code_learning {
	
	class Glob {
	public:
		Glob(const Config &cfg, std::shared_ptr<GUI::SummaryBoard> &board):
			m_cfg(cfg), m_board(board){
		}
		const Config &m_cfg;
		std::shared_ptr<GUI::SummaryBoard> &m_board;
		statistics::Generate m_generate;

	};
}

#endif