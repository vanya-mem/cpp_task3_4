#include "RedBlackTree.h"

int main() {
    RedBlackTree<int> intTree;
    intTree.insert(10);
    intTree.insert(20);
    intTree.insert(30);
    intTree.insert(15);

    std::cout << "Неупорядоченный обход дерева int: ";
    intTree.inorder();

    std::cout << "Поиск 20 в дереве int: " << (intTree.search(20) ? "Найдено" : "Не найдено") << std::endl;

    RedBlackTree<std::string> stringTree;
    stringTree.insert("яблоко");
    stringTree.insert("банан");
    stringTree.insert("вишня");

    std::cout << "Неупорядоченный обход дерева строк: ";
    stringTree.inorder();

    std::cout << "Поиск «банан» в дереве строк: " << (stringTree.search("банан") ? "Найдено" : "Не найдено") << std::endl;

    return 0;
}
