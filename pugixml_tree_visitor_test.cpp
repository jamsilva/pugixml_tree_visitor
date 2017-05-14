#include <iostream>

#include <pugixml.hpp>
#include <pugixml_tree_visitor.hpp>

struct path_printer
: public pugi::xml_tree_visitor
{
	bool visit_enter(pugi::xml_node& node);
	bool visit_exit(pugi::xml_node& node);
};

bool path_printer::visit_enter(pugi::xml_node& node)
{
	std::cout << get_path_str() << " entered:\n";
	node.print(std::cout);
	std::cout << std::endl;
	return true;
}

bool path_printer::visit_exit(pugi::xml_node& node)
{
	(void) node;
	std::cout << get_path_str() << " exited.\n" << std::endl;
	return true;
}

int main()
{
	pugi::xml_document doc;

	// add node with some name
	pugi::xml_node node = doc.append_child("node");

	// add description node with text child
	pugi::xml_node descr = node.append_child("description");
	descr.append_child(pugi::node_pcdata).set_value("Simple node");

	// add param node before the description
	pugi::xml_node param = node.insert_child_before("param", descr);

	// add attributes to param node
	param.append_attribute("name") = "version";
	param.append_attribute("value") = 1.1;
	param.insert_attribute_after("type", param.attribute("name")) = "float";

	// visit the document with path_printer
	path_printer().visit(doc);
}
