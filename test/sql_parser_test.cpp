#include <gtest/gtest.h>

#include <sql_parser.h>

class SQLParserTest : public ::testing::Test {
protected:
    SQLParser parser;
};

TEST_F(SQLParserTest, ParseSimpleSelectQuery) {
    std::string query = "SELECT name, age FROM users";
    auto ast = parser.parse(query);
    
    ASSERT_NE(ast, nullptr);
    auto selectNode = dynamic_cast<SelectNode*>(ast.get());
    ASSERT_NE(selectNode, nullptr);
    
    EXPECT_EQ(selectNode->columns.size(), 2);
    EXPECT_EQ(selectNode->columns[0], "name");
    EXPECT_EQ(selectNode->columns[1], "age");
    EXPECT_EQ(selectNode->table, "users");
    EXPECT_EQ(selectNode->whereClause, nullptr);
}

TEST_F(SQLParserTest, ParseSelectQueryWithWhereClause) {
    std::string query = "SELECT name, age FROM users WHERE age = 25";
    auto ast = parser.parse(query);
    
    ASSERT_NE(ast, nullptr);
    auto selectNode = dynamic_cast<SelectNode*>(ast.get());
    ASSERT_NE(selectNode, nullptr);
    
    EXPECT_EQ(selectNode->columns.size(), 2);
    EXPECT_EQ(selectNode->columns[0], "name");
    EXPECT_EQ(selectNode->columns[1], "age");
    EXPECT_EQ(selectNode->table, "users");
    
    ASSERT_NE(selectNode->whereClause, nullptr);
    auto whereNode = dynamic_cast<WhereNode*>(selectNode->whereClause.get());
    ASSERT_NE(whereNode, nullptr);
    EXPECT_EQ(whereNode->left, "age");
    EXPECT_EQ(whereNode->op, "=");
    EXPECT_EQ(whereNode->right, "25");
}

TEST_F(SQLParserTest, ParseSelectAllQuery) {
    std::string query = "SELECT * FROM users";
    auto ast = parser.parse(query);
    
    ASSERT_NE(ast, nullptr);
    auto selectNode = dynamic_cast<SelectNode*>(ast.get());
    ASSERT_NE(selectNode, nullptr);
    
    EXPECT_EQ(selectNode->columns.size(), 1);
    EXPECT_EQ(selectNode->columns[0], "*");
    EXPECT_EQ(selectNode->table, "users");
    EXPECT_EQ(selectNode->whereClause, nullptr);
}

TEST_F(SQLParserTest, ParseInvalidQuery) {
    std::string query = "INSERT INTO users VALUES ('John', 30)";
    auto ast = parser.parse(query);
    
    EXPECT_EQ(ast, nullptr);
}
