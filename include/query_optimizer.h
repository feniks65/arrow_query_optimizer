#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>

class QueryOptimizer {
public:
    void optimize(std::unique_ptr<ASTNode>& ast) {
        if (auto selectNode = dynamic_cast<SelectNode*>(ast.get())) {
            // Perform optimization techniques
            // 1. Projection pushdown
            projectPushdown(*selectNode);
            // 2. Predicate pushdown
            predicatePushdown(*selectNode);
            // 3. Join reordering (commented out for now)
            // joinReordering(*selectNode);
        }
    }

    void setUnusedColumns(const std::vector<std::string>& columns) {
        unusedColumns.clear();
        unusedColumns.insert(columns.begin(), columns.end());
    }


private:
    std::unordered_set<std::string> unusedColumns;

    void projectPushdown(SelectNode& selectNode) {
        selectNode.columns.erase(
        std::remove_if(selectNode.columns.begin(), selectNode.columns.end(),
                       [this](const std::string& column) {
                           return unusedColumns.find(column) != unusedColumns.end();
                       }),
        selectNode.columns.end());
    }

    void predicatePushdown(SelectNode& selectNode) {
        // Push down predicates to the WHERE clause
        if (selectNode.whereClause) {
            if (auto whereNode = dynamic_cast<WhereNode*>(selectNode.whereClause.get())) {
                // Perform predicate pushdown based on the where clause conditions
                // ...
            }
        }
    }
};
