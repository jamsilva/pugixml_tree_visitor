#include <vector>

#include <pugixml.hpp>

namespace pugi
{
	class xml_tree_visitor
	{
	private:
		std::vector<xml_node> _path;

	public:
		std::string get_path_str();
		void visit(xml_node& node);

		virtual ~xml_tree_visitor()              {}
		const std::vector<xml_node>& get_path()  { return _path; }

	protected:
		// Event produced when entering a node; returns whether to continue descending (true) or skip the subtree (false)
		virtual bool visit_enter(xml_node& node) { return true; }

		// Event produced when exiting a node; returns whether to continue the visit (true) or end it (false)
		virtual bool visit_exit(xml_node& node)  { return true; }
	};
}
