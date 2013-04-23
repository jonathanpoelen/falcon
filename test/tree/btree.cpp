#include <test/test.hpp>
#include <falcon/tree/btree.hpp>
#include <falcon/tree/forward_btree.hpp>
#include "btree.hpp"

void btree_test()
{
	typedef falcon::btree<int> btree_type;
	btree_type btree_root;
	btree_type rbtree(10);
	btree_type lbtree(20);
	btree_type btree(&rbtree, &lbtree, 1, &btree_root);
	btree_root.left(&btree);

	CHECK_EQUAL_VALUE(0, btree_root.get());
	CHECK_VALUE(!=, nullptr, btree_root.left());
	CHECK_EQUAL_VALUE(1, btree_root.left()->get());
	CHECK_EQUAL_VALUE(10, btree.left()->get());
	CHECK_VALUE(==, nullptr, btree_root.right());
	CHECK_VALUE(!=, nullptr, btree.right());
	CHECK_EQUAL_VALUE(20, btree.right()->get());
}
FALCON_TEST_TO_MAIN(btree_test)
