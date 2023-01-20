#include <iostream>
#include "Code/Element.h"
#include "Element.h"

namespace code_learning {
	namespace statistics {
		Element::Element(const std::string &content, Glob &glob):
			m_content(content),m_glob(glob){
		}
		void Element::Sort() {
		}
		void Element::Summary()const {

		}
		const std::string &Element::GetContent()const {
			return m_content;
		}
		
	}
}