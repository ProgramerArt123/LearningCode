#ifndef __CODE_LEARNING_STATISTICS_LINE_H__
#define __CODE_LEARNING_STATISTICS_LINE_H__

#include "Config.h"
#include "Word.h"
#include "Adjacencies.hpp"
#include "ListMap.hpp"
#include "Frequency.hpp"
#include "Element.h"
#include "Lexis.h"
#include "Descriptions.h"

namespace code_learning {
	namespace code {
		class Line;
	}
	namespace statistics {
		class Line : public Element {
		public:
			explicit Line(const std::string &content, Config &cfg);
			void Statistics(code::Line &line);
			void Summary()const override;
		private:
			Wrapper PeekWrap(std::list<std::unique_ptr<Lexis>>::const_iterator &lexis, 
				std::list<std::unique_ptr<Lexis>>::const_iterator end)const;
			bool PeekWrap(std::list<std::unique_ptr<Lexis>>::const_iterator &lexis, 
				const std::string &wrap, std::list<std::unique_ptr<Lexis>>::const_iterator end)const;

		private:
			ListMap<Frequency<Word>> m_words;
			Descriptions m_descs;
		};
	}
}

#endif