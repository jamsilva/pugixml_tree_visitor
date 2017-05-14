#include <pugixml.hpp>
#include <pugixml_tree_visitor.hpp>

namespace pugi
{
	std::string xml_tree_visitor::get_path_str()
	{
		std::string str;

		for(std::vector<xml_node>::iterator it = _path.begin(), end = _path.end() ; it != end ; ++it)
			str.append(it->name()).append("/");

		return str;
	}

	void xml_tree_visitor::visit(xml_node& node)
	{
		_path.push_back(node);

		do
		{
			while(!_path.back())
			{
				_path.pop_back();

				if(_path.empty() || !visit_exit(_path.back()))
					return;

				_path.back() = _path.back().next_sibling();
			}

			if(!visit_enter(_path.back()))
			{
				if(!visit_exit(_path.back()))
					return;

				_path.back() = _path.back().next_sibling();
			}
			else
				_path.push_back(_path.back().first_child());
		} while(true);
	}
}
