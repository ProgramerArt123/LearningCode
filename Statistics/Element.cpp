#include <iostream>
#include "Element.h"

namespace code_learning {
	namespace statistics {
		Element::Element(const std::string &content, Config &cfg):
			m_content(content),m_cfg(cfg){
		}
		void Element::Sort() {
		}
		void Element::Summary()const {

		}
	}
}