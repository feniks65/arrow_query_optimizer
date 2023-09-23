#include <algorithm>
#include <cctype>

#include "ast_node.h"
#include "helpers.h"

#pragma once
class SQLParser {
public:
    std::unique_ptr<ASTNode> parse(const std::string& query) {
        size_t selectPos = query.find("SELECT");
        if (selectPos != std::string::npos) {
            auto selectNode = std::make_unique<SelectNode>();

            // Parse SELECT clause
            size_t fromPos = query.find("FROM", selectPos);
            std::string selectClause = query.substr(selectPos + 6, fromPos - selectPos - 6);
            parseColumns(selectClause, selectNode->columns);

            // Parse FROM clause
            size_t wherePos = query.find("WHERE", fromPos);
            if (wherePos == std::string::npos) {
                wherePos = query.length();
            }
            selectNode->table = trim(query.substr(fromPos + 4, wherePos - fromPos - 4));

            // Parse WHERE clause (if present)
            if (wherePos != query.length()) {
                std::string whereClause = query.substr(wherePos + 5);
                selectNode->whereClause = parseWhereClause(whereClause);
            }

            return selectNode;
        }
        return nullptr;
    }

private:
    void parseColumns(const std::string& clauseStr, std::vector<std::string>& columns) {
        size_t start = 0;
        size_t end = clauseStr.find(',');
        while (end != std::string::npos) {
            columns.push_back(trim(clauseStr.substr(start, end - start)));
            start = end + 1;
            end = clauseStr.find(',', start);
        }
        columns.push_back(trim(clauseStr.substr(start)));
    }

    std::unique_ptr<WhereNode> parseWhereClause(const std::string& clauseStr) {
        auto whereNode = std::make_unique<WhereNode>();
        size_t opPos = std::string::npos;
        
        // Check for different operators
        std::vector<std::string> operators = {"=", ">", "<", ">=", "<=", "<>"};
        for (const auto& op : operators) {
            opPos = clauseStr.find(op);
            if (opPos != std::string::npos) {
                whereNode->left = trim(clauseStr.substr(0, opPos));
                whereNode->op = op;
                whereNode->right = trim(clauseStr.substr(opPos + op.length()));
                break;
            }
        }
        
        return whereNode;
    }
};
