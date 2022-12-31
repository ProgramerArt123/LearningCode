#ifndef __CODE_LEARNING_CODE_H__
#define __CODE_LEARNING_CODE_H__

#include <list>
#include <memory>
#include "Region.h"
#include "Frequency.hpp"

namespace code_learning {

	class Lexis;
	class Config;

	namespace code {

		class Line {
		public:
			std::string m_content;
			std::list<std::unique_ptr<Lexis>> m_lexes;
			void Decomposition(Config &cfg);
			const std::string &GetSignature() const;
		private:
			bool CheckEncoding(const char *content, size_t &index);
			std::string m_signature;
		};

		class Region {
		public:
			void Decomposition(Config &cfg);
			const std::string &GetSignature() const;
			std::list<std::unique_ptr<code::Line>> m_lines;
			std::string m_signature;
		};

		class Code {
		public:
			explicit Code(const char *content, Config &cfg);
			void Statistics(ListMap<Frequency<statistics::Region>> &regions)const;
		private:
			std::list<std::unique_ptr<code::Region>> m_regions;
			const Config &m_cfg;
		};
	}
}

#endif