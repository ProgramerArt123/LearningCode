#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>
#include "Element.h"

namespace code_learning {
	namespace code {
		ELEMENT_TYPE Element::GetType() const {
			return m_type;
		}
		bool Element::ContentAppend(char next, const Glob &glob) {
			return false;
		}
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
			CalculateSignature();
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
		void Element::CalculateSignature()  {
			char result[33]{ 0 };
			const std::string &pattern = GetPattern();
			boost::uuids::detail::md5 md5;
			boost::uuids::detail::md5::digest_type digest;
			md5.process_bytes(pattern.c_str(), pattern.length());
			md5.get_digest(digest);
			const auto charDigest = reinterpret_cast<const char *>(&digest);
			boost::algorithm::hex(charDigest, charDigest + sizeof(boost::uuids::detail::md5::digest_type), result);
			m_signature = result;
		}
	}
}