#include "Code/Element.h"
#include "Path.h"

namespace code_learning {
	namespace statistics {
		Path::Path(const std::string &content, Glob &glob):
			File(content, glob){

		}
		void Path::Statistics(const code::Element &element) {
			for (auto &child : *element.GetChild(0)) {
				switch (child->GetType())
				{
				case code::ELEMENT_TYPE_PATH:
					Statistics(*child);
					break;
				case code::ELEMENT_TYPE_FILE:
					File::Statistics(*child);
					break;
				case code::ELEMENT_TYPE_CODE:
					Code::Statistics(*child);
					break;
				default:
					break;
				}
			}
		}
	}
}