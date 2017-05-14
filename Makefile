all:
	clang++ -Wall -I. pugixml_tree_visitor.cpp pugixml_tree_visitor_test.cpp -o ptvt -lpugixml
