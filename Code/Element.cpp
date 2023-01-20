
#include "Element.h"

namespace code_learning {
	namespace code {
		bool Element::TryAppendChar(char next, const Glob &glob) {
			return false;
		}
		bool Element::IsSpace()const {
			 return false;
		}
		bool Element::IsMulti()const {
			return false;
		}
		void Element::Decomposition(const Glob &glob) {

		}
		size_t Element::GetChildrenCount()const {
			return 0;
		}
		const std::list<std::shared_ptr<Element>> *Element::GetChild(size_t index) const {
			return NULL;
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