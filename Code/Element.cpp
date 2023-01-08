
#include "Element.h"

namespace code_learning {
	namespace code {
		const std::string &Element::GetContent() const {
			return m_content;
		}
		std::string::const_iterator Element::begin() const {
			return m_content.begin();
		}
		std::string::const_iterator Element::end() const {
			return m_content.end();
		}
	}
}