#include "pch.h"
#include "..\graph_class/Graph.h"


using namespace std;
// Тестирование метода дабавления вершин для графа
TEST(TestGraph, TestInsertVertex) {

	// Создаем граф с максимальным размером 2
	Graph<int> g1(2);
	EXPECT_EQ(g1.NumberOfVertices(), 0); // Вначале граф пуст
	EXPECT_EQ(g1.GetMaxSize(), 2); // Максимальный размер графа задан как 2

	// Добавляем вершины
	g1.InsertVertex(1);
	g1.InsertVertex(5);

	// Проверяем количество вершин и динамическое изменение размера
	EXPECT_EQ(g1.NumberOfVertices(), 2);
	EXPECT_EQ(g1.GetMaxSize(), 4); // Должен увеличиться

	// Добавляем еще одну вершину
	g1.InsertVertex(8);
	EXPECT_EQ(g1.NumberOfVertices(), 3);
	EXPECT_EQ(g1.GetMaxSize(), 4); // Размер остается 4

	// Проверяем корректность списка вершин
	vector<int> v1 = { 1, 5, 8 }; // Ожидаемый список вершин
	vector<int> v2 = g1.GetVertexList(); // Полученный список вершин
	EXPECT_EQ(v1, v2);
}


// Тестирование метода добавления ребер для графа
TEST(TestGraph, TestInsertEdge) {

	// Создаем граф с максимальным размером 2
	Graph<int> g1(2);

	// Добавляем вершины
	g1.InsertVertex(1);
	g1.InsertVertex(5);
	g1.InsertVertex(8);

	// Добавляем рёбра с соответствующими весами
	g1.InsertEdge(1, 5, 20);
	g1.InsertEdge(5, 8, 45);
	g1.InsertEdge(5, 1, 12);

	// Проверяем корректность весов рёбер
	EXPECT_EQ(20, g1.GetWeight(1, 5)); // Ребро 1 -> 5 весом 20
	EXPECT_EQ(12, g1.GetWeight(5, 1)); // Ребро 5 -> 1 весом 12
	EXPECT_EQ(45, g1.GetWeight(5, 8)); // Ребро 5 -> 8 весом 45
	EXPECT_EQ(0, g1.GetWeight(1, 8));  // 0 означает, что ребро отсутствует

	// Проверяем выброс исключения при запросе веса для несуществующей вершины
	try {
		g1.GetWeight(5, 9);
	}
	catch (invalid_argument const& ex) {
		string s = ex.what();
		EXPECT_EQ(s, "Отсутствует требуемая вершина");
	}
}


// Тестирование метода удаления вершин для графа
TEST(TestGraph, TestDeleteVertex) {
	// Создаем граф с максимальным размером 2
	Graph<int> g1(2);

	// Попытка удаления несуществующей вершины
	try {
		g1.DeleteVertex(13);
	}
	catch (invalid_argument const& ex) {
		string s = ex.what();
		EXPECT_EQ(s, "Отсутствует требуемая вершина");
	}

	// Добавляем вершины
	g1.InsertVertex(1);
	g1.InsertVertex(5);
	g1.InsertVertex(8);
	g1.InsertVertex(2);
	g1.InsertVertex(13);

	// Удаляем вершину и проверяем список оставшихся вершин
	g1.DeleteVertex(2);
	vector<int> v1 = { 1, 5, 8, 13 };
	EXPECT_EQ(v1, g1.GetVertexList());

	// Добавляем рёбра между вершинами
	g1.InsertEdge(1, 5, 20);
	g1.InsertEdge(5, 8, 45);
	g1.InsertEdge(5, 1, 12);
	g1.InsertEdge(8, 13, 99);
	g1.InsertEdge(13, 1, 49);

	// Удаляем вершину с рёбрами и проверяем обновленный список смежных вершин
	g1.DeleteVertex(5);

	v1 = { 13 }; // Ожидаемый список соседей вершины 1
	EXPECT_EQ(v1, g1.GetNeighbors(1));
	EXPECT_EQ(v1, g1.GetNeighbors(8));

	v1 = { 1, 8 }; // Ожидаемый список соседей вершины 13
	EXPECT_EQ(v1, g1.GetNeighbors(13));
}

// Тестирование метода удаления ребер для графа
TEST(TestGraph, TestDeleteEdge) {
	// Создаем граф с максимальным размером 2
	Graph<int> g1(2);

	// Попытка удаления ребра между несуществующими вершинами
	try {
		g1.DeleteEdge(13, 1);
	}
	catch (invalid_argument const& ex) {
		string s = ex.what();
		EXPECT_EQ(s, "Отсутствует требуемая вершина");
	}

	// Добавляем вершины
	g1.InsertVertex(1);
	g1.InsertVertex(5);
	g1.InsertVertex(8);
	g1.InsertVertex(2);
	g1.InsertVertex(13);

	// Добавляем рёбра с весами
	g1.InsertEdge(1, 5, 20);
	g1.InsertEdge(5, 8, 45);
	g1.InsertEdge(5, 1, 12);
	g1.InsertEdge(8, 13, 99);
	g1.InsertEdge(2, 13, 125);
	g1.InsertEdge(2, 5, 54);
	g1.InsertEdge(13, 1, 49);

	// Удаляем ребро между вершинами 5 и 13 (отсутствует в графе)
	g1.DeleteEdge(5, 13);
	EXPECT_EQ(0, g1.GetWeight(5, 13)); // 0 означает отсутствие ребра

	// Проверяем удаление существующего ребра
	EXPECT_EQ(20, g1.GetWeight(1, 5)); // Ребро 1 -> 5 весом 20
	g1.DeleteEdge(1, 5); // Удаляем ребро 1 -> 5
	EXPECT_EQ(0, g1.GetWeight(1, 5)); // Проверяем, что ребро удалено
}

// Тестирование метода нахождения соседей для графа
TEST(TestGraph, TestNeighbors) {
	// Создаем граф с максимальным размером 2
	Graph<int> g1(2);

	// Добавляем вершины
	g1.InsertVertex(1);
	g1.InsertVertex(5);
	g1.InsertVertex(8);
	g1.InsertVertex(2);
	g1.InsertVertex(13);

	// Добавляем рёбра между вершинами
	g1.InsertEdge(1, 5, 20);
	g1.InsertEdge(5, 8, 45);
	g1.InsertEdge(5, 1, 12);
	g1.InsertEdge(8, 13, 99);
	g1.InsertEdge(2, 13, 125);
	g1.InsertEdge(2, 5, 54);
	g1.InsertEdge(13, 1, 49);

	// Проверяем соседей и подписчиков для вершины 1
	vector<int> v1 = { 5, 13 }; // Соседи вершины 1
	vector<int> v2 = { 5 };     // Подписчики вершины 1
	EXPECT_EQ(v1, g1.GetNeighbors(1));
	EXPECT_EQ(v2, g1.GetFolowers(1));

	// Для вершины 5
	v1 = { 1, 8, 2 }; v2 = { 1, 8 };
	EXPECT_EQ(v1, g1.GetNeighbors(5));
	EXPECT_EQ(v2, g1.GetFolowers(5));

	// Для вершины 8
	v1 = { 5, 13 }; v2 = { 13 };
	EXPECT_EQ(v1, g1.GetNeighbors(8));
	EXPECT_EQ(v2, g1.GetFolowers(8));

	// Для вершины 2
	v1 = { 5, 13 }; v2 = { 5, 13 };
	EXPECT_EQ(v1, g1.GetNeighbors(2));
	EXPECT_EQ(v2, g1.GetFolowers(2));

	// Для вершины 13
	v1 = { 1, 8, 2 }; v2 = { 1 };
	EXPECT_EQ(v1, g1.GetNeighbors(13));
	EXPECT_EQ(v2, g1.GetFolowers(13));

	// Проверка обработки исключения при запросе соседей несуществующей вершины
	try {
		v1 = g1.GetNeighbors(9);
	}
	catch (invalid_argument const& ex) {
		string s = ex.what();
		EXPECT_EQ(s, "Отсутствует требуемая вершина");
	}

	// Проверка обработки исключения при запросе подписчиков несуществующей вершины
	try {
		v1 = g1.GetFolowers(9);
	}
	catch (invalid_argument const& ex) {
		string s = ex.what();
		EXPECT_EQ(s, "Отсутствует требуемая вершина");
	}
}

// Тестирование методов обхода графа в глубину и в ширину
TEST(TestGraph, TestSearch) {
	// Создаем граф с максимальным размером 2
	Graph<int> g1(2);

	// Добавляем вершины
	g1.InsertVertex(1);
	g1.InsertVertex(5);
	g1.InsertVertex(8);
	g1.InsertVertex(2);
	g1.InsertVertex(13);

	// Добавляем рёбра между вершинами
	g1.InsertEdge(1, 5, 20);
	g1.InsertEdge(5, 8, 45);
	g1.InsertEdge(5, 1, 12);
	g1.InsertEdge(8, 13, 99);
	g1.InsertEdge(2, 13, 125);
	g1.InsertEdge(2, 5, 54);
	g1.InsertEdge(13, 1, 49);

	// Проверяем поиск в глубину (DFS) и в ширину (BFS) от вершины 5
	vector<int> v = { 5, 8, 13, 1 }; // Ожидаемый результат DFS
	vector<int> v1 = g1.DepthFirstSearch(5);
	EXPECT_EQ(v1, v);

	v = { 5, 1, 8, 13 }; // Ожидаемый результат BFS
	v1 = g1.BreadthFirstSearch(5);
	EXPECT_EQ(v1, v);

	// Проверяем поиск в глубину (DFS) и в ширину (BFS) от вершины 2
	v = { 2, 13, 1, 5, 8 }; // Ожидаемый результат DFS
	v1 = g1.DepthFirstSearch(2);
	EXPECT_EQ(v1, v);

	v = { 2, 5, 13, 1, 8 }; // Ожидаемый результат BFS
	v1 = g1.BreadthFirstSearch(2);
	EXPECT_EQ(v1, v);
}


// Тестирование алгоритма Дейкстры для поиска кратчайших путей
TEST(TestGraph, TestDijkstra) {
	// Создаем граф с максимальным размером 2
	Graph<int> g1(2);

	// Добавляем вершины
	g1.InsertVertex(1);
	g1.InsertVertex(5);
	g1.InsertVertex(8);
	g1.InsertVertex(2);
	g1.InsertVertex(13);

	// Добавляем рёбра с весами
	g1.InsertEdge(1, 5, 20);
	g1.InsertEdge(5, 8, 45);
	g1.InsertEdge(5, 1, 12);
	g1.InsertEdge(8, 13, 99);
	g1.InsertEdge(2, 13, 125);
	g1.InsertEdge(2, 5, 54);
	g1.InsertEdge(13, 1, 49);

	// Проверяем алгоритм Дейкстры от вершины 5
	vector<int> v = { 12, 0, 45, INT_MAX, 144 }; // Ожидаемые кратчайшие пути
	vector<int> v1 = g1.dijkstra(5);
	EXPECT_EQ(v1, v);

	// Проверяем алгоритм Дейкстры от вершины 2
	v = { 66, 54, 99, 0, 125 };
	v1 = g1.dijkstra(2);
	EXPECT_EQ(v1, v);

	// Проверяем алгоритм Дейкстры от вершины 1
	v = { 0, 20, 65, INT_MAX, 164 };
	v1 = g1.dijkstra(1);
	EXPECT_EQ(v1, v);

	// Проверяем обработку исключения при запросе кратчайших путей из несуществующей вершины
	try {
		v1 = g1.dijkstra(5);
	}
	catch (invalid_argument const& ex) {
		string s = ex.what();
		EXPECT_EQ(s, "Отсутствует требуемая вершина");
	}
}

// Тестирование записи и чтения графа из файла
TEST(TestGraph, TestToFromFile) {

	// Создаем граф с максимальным размером 2
	Graph<int> g1(2);
	vector<int> v;

	// Проверяем запись пустого графа (должно возникнуть исключение)
	try {
		g1.WriteToFile("errortest1.txt");
	}
	catch (invalid_argument const& ex) {
		string s = ex.what();
		EXPECT_EQ(s, "Пустой граф");
	}

	// Добавляем вершины
	g1.InsertVertex(1);
	g1.InsertVertex(5);
	g1.InsertVertex(8);
	g1.InsertVertex(2);
	g1.InsertVertex(13);

	// Добавляем рёбра с весами
	g1.InsertEdge(1, 5, 20);
	g1.InsertEdge(5, 8, 45);
	g1.InsertEdge(5, 1, 12);
	g1.InsertEdge(8, 13, 99);
	g1.InsertEdge(2, 13, 125);
	g1.InsertEdge(2, 5, 54);
	g1.InsertEdge(13, 1, 49);

	// Записываем граф в файл
	g1.WriteToFile("graphtest1.txt");

	// Создаем новый граф и загружаем данные из файла
	Graph<int> g2;
	g2.ReadFromFile("graphtest1.txt");

	// Проверяем, что вершины совпадают
	EXPECT_EQ(g1.GetVertexList(), g2.GetVertexList());

	// Проверяем, что матрицы смежности совпадают
	int** matr1 = g1.GetEdges();
	int** matr2 = g2.GetEdges();

	for (int i = 0; i < g1.NumberOfVertices(); i++) {
		for (int j = 0; j < g1.NumberOfVertices(); j++) {
			EXPECT_EQ(matr1[i][j], matr2[i][j]);
		}
	}
}