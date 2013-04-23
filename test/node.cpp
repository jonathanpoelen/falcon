#include <test/test.hpp>
#include <falcon/node/unique_node.hpp>
#include <falcon/node/rope_node.hpp>
#include <falcon/node/tri_node.hpp>
#include <falcon/node/cross_node.hpp>
#include "node.hpp"

void node_test()
{
	{
		typedef falcon::node::unique_node<int> node_type;
		typedef typename node_type::iterator iterator_type;
		node_type node2(3, 0);
		node_type node1(2, &node2);
		node_type node0(1, &node1);
		//iterator_type it = node0.begin();
		iterator_type it = falcon::node::make_range_next_node<>(node0).begin();
		iterator_type end;

		CHECK_EQUAL_VALUE(1, *it);
		CHECK_EQUAL_VALUE(true, end != it);
		CHECK_EQUAL_VALUE(2, *++it);
		CHECK_EQUAL_VALUE(true, end != it);
		CHECK_EQUAL_VALUE(3, *++it);
		CHECK_EQUAL_VALUE(true, end != it);
		CHECK_EQUAL_VALUE(true, end == ++it);
		node2.next(&node0);
		it = &node2;
		CHECK_EQUAL_VALUE(1, *++it);
		CHECK_EQUAL_VALUE(true, end != it);
	}

	{
		typedef falcon::node::rope_node<int> node_type;
		node_type node2(3, 0, 0);
		node_type node1(2, 0, &node2);
		node_type node0(1, 0, &node1);

		{
			typedef falcon::node::basic_node_iterator<falcon::node::right_node_access_traits<node_type*> > iterator_type;
			//iterator_type it(node0);
			iterator_type it = falcon::node::make_left_to_right_node<>(node0).begin();
			iterator_type end;

			CHECK_EQUAL_VALUE(1, *it);
			CHECK_EQUAL_VALUE(true, end != it);
			CHECK_EQUAL_VALUE(2, *++it);
			CHECK_EQUAL_VALUE(true, end != it);
			CHECK_EQUAL_VALUE(3, *++it);
			CHECK_EQUAL_VALUE(true, end != it);
			CHECK_EQUAL_VALUE(true, end == ++it);
			node2.right(&node0);
			it = &node2;
			CHECK_EQUAL_VALUE(1, *++it);
			CHECK_EQUAL_VALUE(true, end != it);
			CHECK_EQUAL_VALUE(2, *++it);
			CHECK_EQUAL_VALUE(true, end != it);
		}
		{
			typedef falcon::node::basic_node_iterator<falcon::node::left_node_access_traits<node_type*> > iterator_type;
			iterator_type it = falcon::node::make_right_to_left_node<>(node0).begin();
			iterator_type end;

			CHECK_EQUAL_VALUE(1, *it);
			CHECK_EQUAL_VALUE(true, end != it);
			CHECK_EQUAL_VALUE(3, *++it);
			CHECK_EQUAL_VALUE(true, end != it);
			CHECK_EQUAL_VALUE(2, *++it);
			CHECK_EQUAL_VALUE(true, end != it);
			CHECK_EQUAL_VALUE(1, *++it);
			CHECK_EQUAL_VALUE(true, end != it);
		}
	}
}
FALCON_GROUP_TEST_TO_MAIN(node_test)
