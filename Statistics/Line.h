#ifndef __CODE_LEARNING_STATISTICS_LINE_H__
#define __CODE_LEARNING_STATISTICS_LINE_H__

#include "Config.h"
#include "Generate.h"
#include "Lexis.h"
#include "Adjacencies.hpp"
#include "Composite.hpp"
#include "Code/Lexis.h"
#include "Descriptions.h"

namespace code_learning {
	namespace code {
		class Line;
	}
	namespace statistics {
		class Line : public Composite<statistics::Lexis, statistics::Lexis> {
		public:
			explicit Line(const std::string &content, Glob &glob);
			void Statistics(code::Line &line);
			void Summary()const override;
		private:
			bool PeekWrap(std::list<std::shared_ptr<code::Lexis>>::const_iterator &lexis,
				std::list<std::shared_ptr<code::Lexis>>::const_iterator end);
			bool PeekWrap(std::list<std::shared_ptr<code::Lexis>>::const_iterator &lexis,
				std::list<std::shared_ptr<code::Lexis>>::const_iterator end) const;

		private:
			Descriptions m_descs;
			Wrapper m_wrapper;
		};
	}
}

#endif