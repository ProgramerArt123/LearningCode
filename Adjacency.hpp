#ifndef __CODE_LEARNING_ADJACENCY_HPP__
#define __CODE_LEARNING_ADJACENCY_HPP__

#include <string>
#include <map>
#include "LexisType.h"
#include "Code/Element.h"
namespace code_learning {

	class Glob;

	class AdjacencyBase {
	public:
		virtual void Sort() = 0;
		virtual void Summary() = 0;
		virtual std::map<char, uint64_t> &GetSymmetries() = 0;
		virtual void FrontCount(const std::string &next) {};
		virtual void BackCount(const std::string &pre) {};
		virtual void Statistics(code::Element &element) = 0;
		virtual const std::string &GetContent()const = 0;
		AdjacencyBase &operator++(int) {
			m_count++;
			return *this;
		}
		uint64_t GetCount()const {
			return m_count;
		}
	protected:
		uint64_t m_count = 0;
	};

	template<typename Element>
	class Adjacency : public AdjacencyBase {
	public:
		Adjacency(const std::string &content, Glob &glob) :
			m_element(new Element(content, glob)) {
		}
		void Sort() override {
			m_element->Sort();
		}
		void Summary() override {
			m_element->Summary();
		}
		std::map<char, uint64_t> &GetSymmetries() override {
			return m_element->m_symmetries;
		}
		void Statistics(code::Element &element) override {
			m_element->Statistics(element);
		}
		const std::string &GetContent()const override {
			return m_element->GetContent();
		}
		std::shared_ptr<Element> m_element;
	
	};

}

#endif