#include "SkipList.cpp"
#include "RBTree.cpp"
#include "AVL.cpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>
#include <map>

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << "<levels> <coinflip_chance> <tests>" << std::endl;
        return 1;
    }

    int levels = std::stoi(argv[1]);
    int total_numbers = std::stoi(argv[3]);
    std::vector<int> operations(total_numbers);
    map<std::string ,double> mymap;

    SkipList myList(levels, std::stod(argv[2]));
    RedBlackTree rbTree;
    AVLTree avlTree;

    std::cout << "Generating numbers for trees..." << std::endl;
    auto ti = std::chrono::high_resolution_clock::now();


    srand((unsigned)time(0));
    for (int i = 0; i < total_numbers; ++i) {
        operations[i] = rand() % 6 + 1;
    }

    auto tj = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(tj - ti);
    std::cout << "Numbers generated. Time = " << time_span.count() << " seconds." << std::endl;

    std::cout << "Adding numbers to SkipList..." << std::endl;
    ti = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < total_numbers; ++i) {
        int operation = operations[i];
        int x = rand() % 1000 + 1;
        int y = rand() % 1000 + 1;
        bool coinflip = true;
        auto op_time_sl = std::chrono::high_resolution_clock::now();

        switch (operation) {
            case 1:
                myList.addNum(x, myList.get_base(), coinflip);
                break;
            case 2:
                myList.deleteNum(x, myList.get_base());
                break;
            case 3:
                myList.search(x, myList.get_base());
                break;
            case 4:
                myList.lowerBound(x,myList.get_base());
                break;
            case 5:
                myList.upperBound(x, myList.get_base());
                break;
            case 6:
                myList.printRange(x, y,myList.get_base());
                break;
            default:
                break;
        }
        auto cl_time_sl = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span_sl = std::chrono::duration_cast<std::chrono::duration<double>>(cl_time_sl - op_time_sl);
        mymap["Skip List " + std::to_string(operation)] += time_span_sl.count();
    }

    tj = std::chrono::high_resolution_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(tj - ti);
    std::cout << "Time for SkipList = " << time_span.count() << " seconds." << std::endl;

    ti = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < total_numbers; ++i) {
        int operation = operations[i];
        int x = rand() % 1000 + 1;
        int y = rand() % 1000 + 1;
        auto op_time_rb = std::chrono::high_resolution_clock::now();

        switch (operation) {
            case 1:
                rbTree.insert(x);
                break;
            case 2:
                rbTree.deleteNode(x);
                break;
            case 3:
                rbTree.find(x);
                break;
            case 4:
                rbTree.findSmallestGreaterThanOrEqual(x);
                break;
            case 5:
                rbTree.findLargestLessThanOrEqual(x);
                break;
            case 6:
                rbTree.printRange(x, y);
                break;
            default:
                break;
        }
        auto cl_time_rb = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span_rb = std::chrono::duration_cast<std::chrono::duration<double>>(cl_time_rb - op_time_rb);
        mymap["RedBlackTree " + std::to_string(operation)] += time_span_rb.count();
    }
    auto tj_rb = std::chrono::high_resolution_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(tj_rb - ti);
    std::cout << "Time for RedBlackTree = " << time_span.count() << " seconds." << std::endl;

    ti = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < total_numbers; ++i) {
        int operation = operations[i];
        int x = rand() % 1000 + 1;
        int y = rand() % 1000 + 1;
        auto op_time_rb = std::chrono::high_resolution_clock::now();

        switch (operation) {
            case 1:
                avlTree.insert(x);
                break;
            case 2:
                avlTree.remove(x);
                break;
            case 3:
                avlTree.search(x);
                break;
            case 4:
                rbTree.findSmallestGreaterThanOrEqual(x);
                break;
            case 5:
                rbTree.findLargestLessThanOrEqual(x);
                break;
            case 6:
                rbTree.printRange(x, y);
                break;
            default:
                break;
        }
        auto cl_time_rb = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span_rb = std::chrono::duration_cast<std::chrono::duration<double>>(cl_time_rb - op_time_rb);
        mymap["AVLTree " + std::to_string(operation)] += time_span_rb.count();
    }

    tj_rb = std::chrono::high_resolution_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(tj_rb - ti);
    std::cout << "Time for RedBlackTree = " << time_span.count() << " seconds." << std::endl;


    for(const auto& i : mymap){
        std::cout << i.first << " " << i.second << "\n";
    }

    fout.close();
    gout.close();

    return 0;
}
