
#include "Element.h"

namespace code_learning {
	namespace code {
		bool Element::TryAppendChar(char next, const Glob &glob) {
			return false;
		}
		const std::string &Element::GetContent() const {
			return m_content;
		}
		const std::string &Element::GetSignature() const {
			return m_signature;
		}
		std::string::const_iterator Element::begin() const {
			return m_content.begin();
		}
		std::string::const_iterator Element::end() const {
			return m_content.end();
		}
	}
}