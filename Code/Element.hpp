#ifndef __CODE_LEARNING_CODE_ELEMENT_HPP__
#define __CODE_LEARNING_CODE_ELEMENT_HPP__

#include <list>
#include <memory>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>

namespace code_learning {

	class Lexis;
	class Config;

	namespace code {

		template<typename Child>
		class Element {
		public:
			Element(Config &cfg) :m_cfg(cfg){

			}
			typename std::list<std::unique_ptr<Child>>::const_iterator begin() const {
				return m_children.begin();
			}
			typename std::list<std::unique_ptr<Child>>::const_iterator end() const {
				return m_children.end();
			}
			virtual void Decomposition(Config &cfg) {
				CalculateSignature();
			}
			virtual bool ContentAppend(char c) = 0;
			virtual std::string GetPattern() const = 0;
			const std::string &GetSignature() const {
				return m_signature;
			}
			
		protected:
			Config &m_cfg;
			std::string m_content;
			std::list<std::unique_ptr<Child>> m_children;
		private:
			void CalculateSignature() {
				const std::string &pattern = GetPattern();
				boost::uuids::detail::md5 md5;
				boost::uuids::detail::md5::digest_type digest;
				md5.process_bytes(pattern.c_str(), pattern.length());
				md5.get_digest(digest);
				const auto charDigest = reinterpret_cast<const char *>(&digest);
				char result[33]{ 0 };
				boost::algorithm::hex(charDigest, charDigest + sizeof(boost::uuids::detail::md5::digest_type), result);
				m_signature = result;
			}
			std::string m_signature;


		};

	}
}

#endif