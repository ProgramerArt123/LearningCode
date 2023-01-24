#include "Frequency.hpp"
#include "Code/Element.h"
#include "Lexis.h"
#include "Line.h"
#include "Block.h"
#include "Region.h"
#include "File.h"
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
				return m_children.Get<Frequency<statistics::Lexis>>(key, content);
			case code::ELEMENT_TYPE_LINE:
				return m_children.Get<Frequency<statistics::Line>>(key, content);
			case code::ELEMENT_TYPE_BLOCK:
				return m_children.Get<Frequency<statistics::Block>>(key, content);
			case code::ELEMENT_TYPE_REGION:
				return m_children.Get<Frequency<statistics::Region>>(key, content);
			case code::ELEMENT_TYPE_FILE:
				return m_children.Get<Frequency<statistics::File>>(key, content);
			default:
				break;
			}
		}
		void FrequenciesFacade::Count(const code::Element &element, const std::string &key) {
			switch (element.GetType())
			{
			case code::ELEMENT_TYPE_LEXIS:
				m_children.Get<Frequency<statistics::Lexis>>(key)++;
				break;
			case code::ELEMENT_TYPE_LINE:
				m_children.Get<Frequency<statistics::Line>>(key)++;
				break;
			case code::ELEMENT_TYPE_BLOCK:
				m_children.Get<Frequency<statistics::Block>>(key)++;
				break;
			case code::ELEMENT_TYPE_REGION:
				m_children.Get<Frequency<statistics::Region>>(key)++;
				break;
			case code::ELEMENT_TYPE_FILE:
				m_children.Get<Frequency<statistics::File>>(key)++;
			default:
				break;
			}
		}
		void FrequenciesFacade::FrontCount(const code::Element &element, const std::string &key, const std::string &next) {
			switch (element.GetType())
			{
			case code::ELEMENT_TYPE_LEXIS:
				m_children.Get<Frequency<statistics::Lexis>>(key).FrontCount(next);
				break;
			case code::ELEMENT_TYPE_LINE:
				m_children.Get<Frequency<statistics::Line>>(key).FrontCount(next);
				break;
			case code::ELEMENT_TYPE_BLOCK:
				m_children.Get<Frequency<statistics::Block>>(key).FrontCount(next);
				break;
			case code::ELEMENT_TYPE_REGION:
				m_children.Get<Frequency<statistics::Region>>(key).FrontCount(next);
				break;
			case code::ELEMENT_TYPE_FILE:
				m_children.Get<Frequency<statistics::File>>(key).FrontCount(next);
			default:
				break;
			}
		}
		void FrequenciesFacade::BackCount(const code::Element &element, const std::string &key, const std::string &pre) {
			switch (element.GetType())
			{
			case code::ELEMENT_TYPE_LEXIS:
				m_children.Get<Frequency<statistics::Lexis>>(key).BackCount(pre);
				break;
			case code::ELEMENT_TYPE_LINE:
				m_children.Get<Frequency<statistics::Line>>(key).BackCount(pre);
				break;
			case code::ELEMENT_TYPE_BLOCK:
				m_children.Get<Frequency<statistics::Block>>(key).BackCount(pre);
				break;
			case code::ELEMENT_TYPE_REGION:
				m_children.Get<Frequency<statistics::Region>>(key).BackCount(pre);
				break;
			case code::ELEMENT_TYPE_FILE:
				m_children.Get<Frequency<statistics::File>>(key).BackCount(pre);
			default:
				break;
			}
		}
	}
}