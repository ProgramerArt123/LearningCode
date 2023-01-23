#ifndef __CODE_LEARNING_GLOB_H__
#define __CODE_LEARNING_GLOB_H__

#include "Config.h"
#include "Statistics/Generate.h"

namespace code_learning {
	
	class Glob {
	public:
		explicit Glob(const Config &cfg):
			m_cfg(cfg){
		}
		const Config &m_cfg;
		statistics::Generate m_generate;
	};
}

#endif