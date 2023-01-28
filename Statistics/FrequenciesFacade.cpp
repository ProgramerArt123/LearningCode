#include "Frequency.hpp"
#include "Code/Element.h"
#include "Lexis.h"
#include "Line.h"
#include "Block.h"
#include "Region.h"
#include "Code.h"
#include "File.h"
#include "Path.h"
#include "FrequenciesFacade.h"

namespace code_learning {

	namespace statistics {
		FrequenciesFacade::FrequenciesFacade(Glob &glob) :m_children(glob) {

		}
		std::list<std::shared_ptr<AdjacencyBase>>::const_iterator FrequenciesFacade::begin() const {
			return m_children.begin();
		}
		std::list<std::shared_ptr<AdjacencyBase>>::const_iterator FrequenciesFacade::end() const {
			return m_children.end();
		}
		AdjacencyBase &FrequenciesFacade::Get(const code::Element &element, const std::string &key, const std::string &content) {
			switch (element.GetType())
			{
			case code::ELEMENT_TYPE_LEXIS:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Lexis>, "Lexis invalid");
				return m_children.Get<Frequency<statistics::Lexis>>(key, content);
			case code::ELEMENT_TYPE_LINE:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Line>, "Line invalid");
				return m_children.Get<Frequency<statistics::Line>>(key, content);
			case code::ELEMENT_TYPE_BLOCK:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Block>, "Block invalid");
				return m_children.Get<Frequency<statistics::Block>>(key, content);
			case code::ELEMENT_TYPE_REGION:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Region>, "Region invalid");
				return m_children.Get<Frequency<statistics::Region>>(key, content);
			case code::ELEMENT_TYPE_CODE:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Code>, "Code invalid");
				return m_children.Get<Frequency<statistics::Code>>(key, content);
			case code::ELEMENT_TYPE_FILE:
				static_assert(std::is_base_of_v<statistics::Element, statistics::File>, "File invalid");
				return m_children.Get<Frequency<statistics::File>>(key, content);
			case code::ELEMENT_TYPE_PATH:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Path>, "Path invalid");
				return m_children.Get<Frequency<statistics::Path>>(key, content);
			default:
				break;
			}
		}
		void FrequenciesFacade::Count(const code::Element &element, const std::string &key) {
			switch (element.GetType())
			{
			case code::ELEMENT_TYPE_LEXIS:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Lexis>, "Lexis invalid");
				m_children.Get<Frequency<statistics::Lexis>>(key)++;
				break;
			case code::ELEMENT_TYPE_LINE:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Line>, "Line invalid");
				m_children.Get<Frequency<statistics::Line>>(key)++;
				break;
			case code::ELEMENT_TYPE_BLOCK:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Block>, "Block invalid");
				m_children.Get<Frequency<statistics::Block>>(key)++;
				break;
			case code::ELEMENT_TYPE_REGION:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Region>, "Region invalid");
				m_children.Get<Frequency<statistics::Region>>(key)++;
				break;
			case code::ELEMENT_TYPE_CODE:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Code>, "Code invalid");
				m_children.Get<Frequency<statistics::Code>>(key)++;
				break;
			case code::ELEMENT_TYPE_FILE:
				static_assert(std::is_base_of_v<statistics::Element, statistics::File>, "File invalid");
				m_children.Get<Frequency<statistics::File>>(key)++;
				break;
			case code::ELEMENT_TYPE_PATH:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Path>, "Path invalid");
				m_children.Get<Frequency<statistics::Path>>(key)++;
				break;
			default:
				break;
			}
		}
		void FrequenciesFacade::FrontCount(const code::Element &element, const std::string &key, const std::string &next) {
			switch (element.GetType())
			{
			case code::ELEMENT_TYPE_LEXIS:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Lexis>, "Lexis invalid");
				m_children.Get<Frequency<statistics::Lexis>>(key).FrontCount(next);
				break;
			case code::ELEMENT_TYPE_LINE:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Line>, "Line invalid");
				m_children.Get<Frequency<statistics::Line>>(key).FrontCount(next);
				break;
			case code::ELEMENT_TYPE_BLOCK:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Block>, "Block invalid");
				m_children.Get<Frequency<statistics::Block>>(key).FrontCount(next);
				break;
			case code::ELEMENT_TYPE_REGION:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Region>, "Region invalid");
				m_children.Get<Frequency<statistics::Region>>(key).FrontCount(next);
				break;
			case code::ELEMENT_TYPE_CODE:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Code>, "Code invalid");
				m_children.Get<Frequency<statistics::Code>>(key).FrontCount(next);
				break;
			case code::ELEMENT_TYPE_FILE:
				static_assert(std::is_base_of_v<statistics::Element, statistics::File>, "File invalid");
				m_children.Get<Frequency<statistics::File>>(key).FrontCount(next);
				break;
			case code::ELEMENT_TYPE_PATH:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Path>, "Path invalid");
				m_children.Get<Frequency<statistics::Path>>(key).FrontCount(next);
				break;
			default:
				break;
			}
		}
		void FrequenciesFacade::BackCount(const code::Element &element, const std::string &key, const std::string &pre) {
			switch (element.GetType())
			{
			case code::ELEMENT_TYPE_LEXIS:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Lexis>, "Lexis invalid");
				m_children.Get<Frequency<statistics::Lexis>>(key).BackCount(pre);
				break;
			case code::ELEMENT_TYPE_LINE:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Line>, "Line invalid");
				m_children.Get<Frequency<statistics::Line>>(key).BackCount(pre);
				break;
			case code::ELEMENT_TYPE_BLOCK:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Block>, "Block invalid");
				m_children.Get<Frequency<statistics::Block>>(key).BackCount(pre);
				break;
			case code::ELEMENT_TYPE_REGION:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Region>, "Region invalid");
				m_children.Get<Frequency<statistics::Region>>(key).BackCount(pre);
				break;
			case code::ELEMENT_TYPE_CODE:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Code>, "Code invalid");
				m_children.Get<Frequency<statistics::Code>>(key).BackCount(pre);
				break;
			case code::ELEMENT_TYPE_FILE:
				static_assert(std::is_base_of_v<statistics::Element, statistics::File>, "File invalid");
				m_children.Get<Frequency<statistics::File>>(key).BackCount(pre);
				break;
			case code::ELEMENT_TYPE_PATH:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Path>, "Path invalid");
				m_children.Get<Frequency<statistics::Path>>(key).BackCount(pre);
				break;
			default:
				break;
			}
		}
		
	}
}