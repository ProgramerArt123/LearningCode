#ifndef __CODE_LEARNING_GLOB_H__
#define __CODE_LEARNING_GLOB_H__

#include "Config.h"
#include "SummaryBoard.h"
#include "Statistics/Generate.h"

namespace code_learning {
	
	class Glob {
	public:
		explicit Glob(const char *name, const Config &cfg):
			m_cfg(cfg), m_board(name){
		}
		const Config &m_cfg;
		statistics::Generate m_generate;
		SummaryBoard m_board;
	};
}

#endif