# Arrow Query Optimizer

This project implements a query optimizer for Apache Arrow, focusing on optimizing SQL queries for better performance.

## Project Structure
arrow_query_optimizer/  
├── CMakeLists.txt  
├── cmake/  
│   ├── FindLZ4.cmake  
│   └── Findre2.cmake  
├── include/  
│   ├── ast_node.h  
│   ├── helpers.h  
│   ├── query_optimizer.h  
│   └── sql_parser.h  
├── src/  
│   └── main.cpp  
└── test/  
├── query_optimizer_test.cpp  
├── sql_parser_test.cpp  
└── test_main.cpp  

## Prerequisites

- CMake (version 3.10 or higher)
- C++17 compatible compiler
- Apache Arrow
- LZ4
- RE2

## Building the Project

1. Clone the repository:
git clone https://github.com/feniks65/arrow_query_optimizer.git
cd arrow_query_optimizer

2. Create a build directory:
mkdir build
cd build

3. Run CMake and build the project:
cmake ..
make

## Running the Optimizer

After building the project, you can run the query optimizer:
./query_optimizer

## Running Tests

To run the tests, use the following command from the build directory:
./tests

## Components

- `SQLParser`: Parses SQL queries into an Abstract Syntax Tree (AST).
- `QueryOptimizer`: Applies optimization techniques to the parsed AST.
- `ASTNode`: Base class for nodes in the Abstract Syntax Tree.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## Acknowledgments

- Apache Arrow project
- Google Test framework for C++
