#include <memory>
#include <vector>

struct ASTNode {
    virtual ~ASTNode() = default;
};

struct SelectNode : ASTNode {
    std::vector<std::string> columns;
    std::string table;
    std::unique_ptr<ASTNode> whereClause;
};

struct WhereNode : ASTNode {
    std::string left;
    std::string op;
    std::string right;
};
