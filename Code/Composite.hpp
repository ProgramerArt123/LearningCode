#ifndef __CODE_LEARNING_CODE_COMPOSITE_HPP__
#define __CODE_LEARNING_CODE_COMPOSITE_HPP__

#include <list>
#include <vector>
#include <memory>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>

#include "Element.h"

namespace code_learning {
	class Config;

	namespace code {

		template<typename ...Children> class Composite;

		template<typename Child, typename Type> 
		class Composite<Child, Type> : public Element {
		public:
			Composite() {
				m_children.resize(m_children.size() + 1);
			}
			virtual void Decomposition(const Config &cfg)  {
				CalculateSignature(cfg);
			}
			virtual std::string GetPattern(const Config &cfg) const = 0;
			const std::string &GetSignature() const {
				return m_signature;
			}
			
		public:
			std::vector<std::list<std::shared_ptr<Type>>> m_children;
		private:
			void CalculateSignature(const Config &cfg) {
				const std::string &pattern = GetPattern(cfg);
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

		template<typename Child, typename ...Children>
		class Composite<Child, Children...> : public Composite<Children...>{
		public:
			Composite() {
				Composite<Children...>::m_children.resize(Composite<Children...>::m_children.size() + 1);
			}
		};
	}
}

#endif