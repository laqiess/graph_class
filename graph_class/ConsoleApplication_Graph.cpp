// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "LinkedList.h"
#include "Graph.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus"); // Устанавливаем локаль для поддержки русского языка
    std::cout << "Hello World!\n";

    // Тестирование работы связного списка
    LinkedList<int> l;
    l.addNode(5);
    l.addNode(10);
    l.printList(); // Вывод списка
    std::cout << "\n";

    // Итерация через список с использованием итераторов
    for (LinkedList<int>::LinkedListIterator<int> it1 = l.begin(); it1 != l.end(); ++it1) {
        cout << *it1 << " ";
    }
    std::cout << "\n";
  

    // Использование диапазонного for (аналогично предыдущему циклу)
    for (auto it2 : l) {
        cout << it2 << " ";
    }

    // Поиск элемента по индексу
    cout << l.searchNodeInd(2) << "\n";

    // Обработка исключений при попытке доступа к несуществующему элементу
    try {
        cout << l.dataByInd(1);
    }
    catch (invalid_argument const& ex) {
        cout << ex.what();
    }
    

    cout << "\n" << l.ListSize();

    LinkedList<int> l1;
    cout << "\n" << l1.ListSize();

    // Удаление узла из списка
    l.removeNode(5);
    cout << "\n";
    for (LinkedList<int>::LinkedListIterator<int> it1 = l.begin(); it1 != l.end(); ++it1) {
        cout << *it1 << " ";
    }
    cout << "\n" << l.ListSize();

    cout << "\n\nТестирование класса Граф\n";

    try {
        Graph<int> g(5);

        g.InsertVertex(2);
        g.InsertVertex(4);
        g.InsertEdge(2, 4, 100);
        vector<int> v1 = g.GetNeighbors(2);


        g.InsertVertex(10);
        g.InsertEdge(2, 10, 50);
        g.InsertEdge(10, 4, 70);

        // Вывод веса рёбер
        cout << "\n" << g.GetWeight(10, 4);
        cout << "\n" << g.GetWeight(2, 4);
        std::cout << "\n";

        // Тест обхода графа в глубину
        vector<int> v2 = g.DepthFirstSearch(2);
        for (int item : v2) {
            cout << item << " ";
        }

        cout << "\n\n";

        // Тест обхода графа в ширину
        v2 = g.BreadthFirstSearch(2);
        for (int item : v2) {
            cout << item << " ";
        }

        cout << "\n\n";

        // Тестирование удаления вершины и работы матрицы смежности
        Graph<int> g1(2);
        g1.InsertVertex(1); g1.InsertVertex(5); g1.InsertVertex(8);
        g1.InsertVertex(2); g1.InsertVertex(13);
        g1.DeleteVertex(2);

        g1.InsertEdge(1, 5, 20);
        g1.InsertEdge(5, 8, 45);
        g1.InsertEdge(5, 1, 12);
        g1.InsertEdge(8, 13, 99);
        g1.InsertEdge(13, 1, 49);

        int** matr = g1.GetEdges();
        for (int i = 0; i < g1.NumberOfVertices(); i++) {
            for (int j = 0; j < g1.NumberOfVertices(); j++) {
                cout << matr[i][j] << " ";
            }
            cout << "\n";
        }

        cout << "\n\nЧтение из файла\n";
        g1.ReadFromFile("graph1.txt");

        vector<int> v3 = g1.GetVertexList();
        for (int item : v3) {
            cout << item << " ";
        }
        cout << "\n\n";

        // Запись в файл и повторное чтение
        Graph<int> g2(4);
        g2.InsertVertex(1); g2.InsertVertex(5); g2.InsertVertex(8);
        g2.InsertEdge(1, 5, 200);
        g2.InsertEdge(5, 8, 450);
        g2.InsertEdge(5, 1, 120);
        g2.WriteToFile("graph2.txt");

        Graph<int> g3(5);
        g3.ReadFromFile("graph2.txt");

        vector<int> v4 = g3.GetVertexList();
        for (int item : v4) {
            cout << item << " ";
        }
        cout << "\n\n";

        // Тест алгоритма Дейкстры
        cout << "\nДейкстра\n";
        vector<int> v5 = g3.dijkstra(1);
        for (int item : v5) {
            cout << item << " ";
        }
    }
    catch (invalid_argument const& ex) {
        cout << ex.what();
    }
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
