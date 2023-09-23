#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <algorithm>

#include "sql_parser.h"
#include "query_optimizer.h"

int main() {
    std::string query = "SELECT name, age FROM users WHERE age = 25";

    SQLParser parser;
    auto ast = parser.parse(query);

    QueryOptimizer optimizer;
    optimizer.optimize(ast);

    // Execute the optimized query
    if (auto selectNode = dynamic_cast<SelectNode*>(ast.get())) {
        std::cout << "Optimized Query:" << std::endl;
        std::cout << "SELECT ";
        for (size_t i = 0; i < selectNode->columns.size(); ++i) {
            std::cout << selectNode->columns[i];
            if (i != selectNode->columns.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << " FROM " << selectNode->table;
        if (selectNode->whereClause) {
            if (auto whereNode = dynamic_cast<WhereNode*>(selectNode->whereClause.get())) {
                std::cout << " WHERE " << whereNode->left << " " << whereNode->op << " " << whereNode->right;
            }
        }
        std::cout << std::endl;
    }

    return 0;
}
