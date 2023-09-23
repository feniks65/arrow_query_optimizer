#include <gtest/gtest.h>

#include "sql_parser.h"
#include "query_optimizer.h"

class QueryOptimizerTest : public ::testing::Test {
protected:
    SQLParser parser;
    QueryOptimizer optimizer;
};

TEST_F(QueryOptimizerTest, ProjectPushdown) {
    std::string query = "SELECT name, age, address FROM users";
    auto ast = parser.parse(query);
    optimizer.optimize(ast);
    
    auto selectNode = dynamic_cast<SelectNode*>(ast.get());
    ASSERT_NE(selectNode, nullptr);
    
    // Check if all columns are still present (no unused columns in this case)
    EXPECT_EQ(selectNode->columns.size(), 3);
    EXPECT_EQ(selectNode->columns[0], "name");
    EXPECT_EQ(selectNode->columns[1], "age");
    EXPECT_EQ(selectNode->columns[2], "address");
}

TEST_F(QueryOptimizerTest, PredicatePushdown) {
    std::string query = "SELECT name, age FROM users WHERE age > 18";
    auto ast = parser.parse(query);
    optimizer.optimize(ast);
    
    auto selectNode = dynamic_cast<SelectNode*>(ast.get());
    ASSERT_NE(selectNode, nullptr);
    
    // Check if the WHERE clause is still present
    ASSERT_NE(selectNode->whereClause, nullptr);
    auto whereNode = dynamic_cast<WhereNode*>(selectNode->whereClause.get());
    ASSERT_NE(whereNode, nullptr);
    EXPECT_EQ(whereNode->left, "age");
    EXPECT_EQ(whereNode->op, ">");
    EXPECT_EQ(whereNode->right, "18");
}

TEST_F(QueryOptimizerTest, UnusedColumnRemoval) {
    std::string query = "SELECT name, age, address FROM users WHERE age > 18";
    auto ast = parser.parse(query);
    
    // Simulate a scenario where 'address' is not used in the rest of the query
    optimizer.setUnusedColumns({"address"});
    optimizer.optimize(ast);
    
    auto selectNode = dynamic_cast<SelectNode*>(ast.get());
    ASSERT_NE(selectNode, nullptr);
    
    // Check if 'address' column has been removed
    EXPECT_EQ(selectNode->columns.size(), 2);
    EXPECT_EQ(selectNode->columns[0], "name");
    EXPECT_EQ(selectNode->columns[1], "age");
}

TEST_F(QueryOptimizerTest, NoOptimization) {
    std::string query = "SELECT * FROM users";
    auto ast = parser.parse(query);
    optimizer.optimize(ast);
    
    auto selectNode = dynamic_cast<SelectNode*>(ast.get());
    ASSERT_NE(selectNode, nullptr);
    
    // Check if the query remains unchanged
    EXPECT_EQ(selectNode->columns.size(), 1);
    EXPECT_EQ(selectNode->columns[0], "*");
    EXPECT_EQ(selectNode->table, "users");
    EXPECT_EQ(selectNode->whereClause, nullptr);
}
