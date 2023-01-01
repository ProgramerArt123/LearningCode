#ifndef __CODE_LEARNING_LIST_MAP_HPP__
#define __CODE_LEARNING_LIST_MAP_HPP__

#include <memory>
#include <map>
#include <list>
#include <string>

namespace code_learning {
	
	class Config;

	template<typename Element>
	class ListMap {
	public:
		ListMap(Config &cfg) :
			m_cfg(cfg) {
		}
		typename std::list<std::shared_ptr<Element>>::const_iterator begin() const {
			return m_list.begin();
		}
		typename std::list<std::shared_ptr<Element>>::const_iterator end() const {
			return m_list.end();
		}
		Element &operator[](const std::string &key) {
			if (m_map.end() == m_map.find(key)) {
				std::shared_ptr<Element> word(new Element(key, m_cfg));
				m_map.insert(std::make_pair(key, word));
				m_list.push_back(word);
			}
			return *m_map[key];
		}

		Element &Get(const std::string &key, const std::string &content) {
			if (m_map.end() == m_map.find(key)) {
				std::shared_ptr<Element> word(new Element(content, m_cfg));
				m_map.insert(std::make_pair(key, word));
				m_list.push_back(word);
			}
			return *m_map[key];
		}

		static bool compare(const std::shared_ptr<Element> &one, const std::shared_ptr<Element> &other) {
			return one->GetCount() > other->GetCount();
		}
		void Sort() {
			m_list.sort(compare);
			for (const auto &element : m_list) {
				element->m_element.Sort();
			}
		}
		Config &m_cfg;
	private:
		std::map<std::string, std::shared_ptr<Element>> m_map;
		std::list<std::shared_ptr<Element>> m_list;
	};

}

#endif