#include <iostream>
#include "Code/Code.h"
#include "Code/Lexis.h"
#include "Glob.h"
#include "Code/Line.h"
#include "Block.h"

namespace code_learning {
	namespace statistics {
		Block::Block(const std::string &content, Glob &glob) :
			Line(content, glob) {
		}
		void Block::Statistics(const code::Element &element) {
			Line::Statistics(element);
			for (auto &child : *element.GetChild(0)) {
				if (code::ELEMENT_TYPE_BLOCK == child->GetType()) {
					Statistics(*child);
				}
			}
		}
	}
}