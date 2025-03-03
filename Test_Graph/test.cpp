#include "pch.h"
#include "..\graph_class/Graph.h"


using namespace std;
// ������������ ������ ���������� ������ ��� �����
TEST(TestGraph, TestInsertVertex) {

	// ������� ���� � ������������ �������� 2
	Graph<int> g1(2);
	EXPECT_EQ(g1.NumberOfVertices(), 0); // ������� ���� ����
	EXPECT_EQ(g1.GetMaxSize(), 2); // ������������ ������ ����� ����� ��� 2

	// ��������� �������
	g1.InsertVertex(1);
	g1.InsertVertex(5);

	// ��������� ���������� ������ � ������������ ��������� �������
	EXPECT_EQ(g1.NumberOfVertices(), 2);
	EXPECT_EQ(g1.GetMaxSize(), 4); // ������ �����������

	// ��������� ��� ���� �������
	g1.InsertVertex(8);
	EXPECT_EQ(g1.NumberOfVertices(), 3);
	EXPECT_EQ(g1.GetMaxSize(), 4); // ������ �������� 4

	// ��������� ������������ ������ ������
	vector<int> v1 = { 1, 5, 8 }; // ��������� ������ ������
	vector<int> v2 = g1.GetVertexList(); // ���������� ������ ������
	EXPECT_EQ(v1, v2);
}


// ������������ ������ ���������� ����� ��� �����
TEST(TestGraph, TestInsertEdge) {

	// ������� ���� � ������������ �������� 2
	Graph<int> g1(2);

	// ��������� �������
	g1.InsertVertex(1);
	g1.InsertVertex(5);
	g1.InsertVertex(8);

	// ��������� ���� � ���������������� ������
	g1.InsertEdge(1, 5, 20);
	g1.InsertEdge(5, 8, 45);
	g1.InsertEdge(5, 1, 12);

	// ��������� ������������ ����� ����
	EXPECT_EQ(20, g1.GetWeight(1, 5)); // ����� 1 -> 5 ����� 20
	EXPECT_EQ(12, g1.GetWeight(5, 1)); // ����� 5 -> 1 ����� 12
	EXPECT_EQ(45, g1.GetWeight(5, 8)); // ����� 5 -> 8 ����� 45
	EXPECT_EQ(0, g1.GetWeight(1, 8));  // 0 ��������, ��� ����� �����������

	// ��������� ������ ���������� ��� ������� ���� ��� �������������� �������
	try {
		g1.GetWeight(5, 9);
	}
	catch (invalid_argument const& ex) {
		string s = ex.what();
		EXPECT_EQ(s, "����������� ��������� �������");
	}
}


// ������������ ������ �������� ������ ��� �����
TEST(TestGraph, TestDeleteVertex) {
	// ������� ���� � ������������ �������� 2
	Graph<int> g1(2);

	// ������� �������� �������������� �������
	try {
		g1.DeleteVertex(13);
	}
	catch (invalid_argument const& ex) {
		string s = ex.what();
		EXPECT_EQ(s, "����������� ��������� �������");
	}

	// ��������� �������
	g1.InsertVertex(1);
	g1.InsertVertex(5);
	g1.InsertVertex(8);
	g1.InsertVertex(2);
	g1.InsertVertex(13);

	// ������� ������� � ��������� ������ ���������� ������
	g1.DeleteVertex(2);
	vector<int> v1 = { 1, 5, 8, 13 };
	EXPECT_EQ(v1, g1.GetVertexList());

	// ��������� ���� ����� ���������
	g1.InsertEdge(1, 5, 20);
	g1.InsertEdge(5, 8, 45);
	g1.InsertEdge(5, 1, 12);
	g1.InsertEdge(8, 13, 99);
	g1.InsertEdge(13, 1, 49);

	// ������� ������� � ������ � ��������� ����������� ������ ������� ������
	g1.DeleteVertex(5);

	v1 = { 13 }; // ��������� ������ ������� ������� 1
	EXPECT_EQ(v1, g1.GetNeighbors(1));
	EXPECT_EQ(v1, g1.GetNeighbors(8));

	v1 = { 1, 8 }; // ��������� ������ ������� ������� 13
	EXPECT_EQ(v1, g1.GetNeighbors(13));
}

// ������������ ������ �������� ����� ��� �����
TEST(TestGraph, TestDeleteEdge) {
	// ������� ���� � ������������ �������� 2
	Graph<int> g1(2);

	// ������� �������� ����� ����� ��������������� ���������
	try {
		g1.DeleteEdge(13, 1);
	}
	catch (invalid_argument const& ex) {
		string s = ex.what();
		EXPECT_EQ(s, "����������� ��������� �������");
	}

	// ��������� �������
	g1.InsertVertex(1);
	g1.InsertVertex(5);
	g1.InsertVertex(8);
	g1.InsertVertex(2);
	g1.InsertVertex(13);

	// ��������� ���� � ������
	g1.InsertEdge(1, 5, 20);
	g1.InsertEdge(5, 8, 45);
	g1.InsertEdge(5, 1, 12);
	g1.InsertEdge(8, 13, 99);
	g1.InsertEdge(2, 13, 125);
	g1.InsertEdge(2, 5, 54);
	g1.InsertEdge(13, 1, 49);

	// ������� ����� ����� ��������� 5 � 13 (����������� � �����)
	g1.DeleteEdge(5, 13);
	EXPECT_EQ(0, g1.GetWeight(5, 13)); // 0 �������� ���������� �����

	// ��������� �������� ������������� �����
	EXPECT_EQ(20, g1.GetWeight(1, 5)); // ����� 1 -> 5 ����� 20
	g1.DeleteEdge(1, 5); // ������� ����� 1 -> 5
	EXPECT_EQ(0, g1.GetWeight(1, 5)); // ���������, ��� ����� �������
}

// ������������ ������ ���������� ������� ��� �����
TEST(TestGraph, TestNeighbors) {
	// ������� ���� � ������������ �������� 2
	Graph<int> g1(2);

	// ��������� �������
	g1.InsertVertex(1);
	g1.InsertVertex(5);
	g1.InsertVertex(8);
	g1.InsertVertex(2);
	g1.InsertVertex(13);

	// ��������� ���� ����� ���������
	g1.InsertEdge(1, 5, 20);
	g1.InsertEdge(5, 8, 45);
	g1.InsertEdge(5, 1, 12);
	g1.InsertEdge(8, 13, 99);
	g1.InsertEdge(2, 13, 125);
	g1.InsertEdge(2, 5, 54);
	g1.InsertEdge(13, 1, 49);

	// ��������� ������� � ����������� ��� ������� 1
	vector<int> v1 = { 5, 13 }; // ������ ������� 1
	vector<int> v2 = { 5 };     // ���������� ������� 1
	EXPECT_EQ(v1, g1.GetNeighbors(1));
	EXPECT_EQ(v2, g1.GetFolowers(1));

	// ��� ������� 5
	v1 = { 1, 8, 2 }; v2 = { 1, 8 };
	EXPECT_EQ(v1, g1.GetNeighbors(5));
	EXPECT_EQ(v2, g1.GetFolowers(5));

	// ��� ������� 8
	v1 = { 5, 13 }; v2 = { 13 };
	EXPECT_EQ(v1, g1.GetNeighbors(8));
	EXPECT_EQ(v2, g1.GetFolowers(8));

	// ��� ������� 2
	v1 = { 5, 13 }; v2 = { 5, 13 };
	EXPECT_EQ(v1, g1.GetNeighbors(2));
	EXPECT_EQ(v2, g1.GetFolowers(2));

	// ��� ������� 13
	v1 = { 1, 8, 2 }; v2 = { 1 };
	EXPECT_EQ(v1, g1.GetNeighbors(13));
	EXPECT_EQ(v2, g1.GetFolowers(13));

	// �������� ��������� ���������� ��� ������� ������� �������������� �������
	try {
		v1 = g1.GetNeighbors(9);
	}
	catch (invalid_argument const& ex) {
		string s = ex.what();
		EXPECT_EQ(s, "����������� ��������� �������");
	}

	// �������� ��������� ���������� ��� ������� ����������� �������������� �������
	try {
		v1 = g1.GetFolowers(9);
	}
	catch (invalid_argument const& ex) {
		string s = ex.what();
		EXPECT_EQ(s, "����������� ��������� �������");
	}
}

// ������������ ������� ������ ����� � ������� � � ������
TEST(TestGraph, TestSearch) {
	// ������� ���� � ������������ �������� 2
	Graph<int> g1(2);

	// ��������� �������
	g1.InsertVertex(1);
	g1.InsertVertex(5);
	g1.InsertVertex(8);
	g1.InsertVertex(2);
	g1.InsertVertex(13);

	// ��������� ���� ����� ���������
	g1.InsertEdge(1, 5, 20);
	g1.InsertEdge(5, 8, 45);
	g1.InsertEdge(5, 1, 12);
	g1.InsertEdge(8, 13, 99);
	g1.InsertEdge(2, 13, 125);
	g1.InsertEdge(2, 5, 54);
	g1.InsertEdge(13, 1, 49);

	// ��������� ����� � ������� (DFS) � � ������ (BFS) �� ������� 5
	vector<int> v = { 5, 8, 13, 1 }; // ��������� ��������� DFS
	vector<int> v1 = g1.DepthFirstSearch(5);
	EXPECT_EQ(v1, v);

	v = { 5, 1, 8, 13 }; // ��������� ��������� BFS
	v1 = g1.BreadthFirstSearch(5);
	EXPECT_EQ(v1, v);

	// ��������� ����� � ������� (DFS) � � ������ (BFS) �� ������� 2
	v = { 2, 13, 1, 5, 8 }; // ��������� ��������� DFS
	v1 = g1.DepthFirstSearch(2);
	EXPECT_EQ(v1, v);

	v = { 2, 5, 13, 1, 8 }; // ��������� ��������� BFS
	v1 = g1.BreadthFirstSearch(2);
	EXPECT_EQ(v1, v);
}


// ������������ ��������� �������� ��� ������ ���������� �����
TEST(TestGraph, TestDijkstra) {
	// ������� ���� � ������������ �������� 2
	Graph<int> g1(2);

	// ��������� �������
	g1.InsertVertex(1);
	g1.InsertVertex(5);
	g1.InsertVertex(8);
	g1.InsertVertex(2);
	g1.InsertVertex(13);

	// ��������� ���� � ������
	g1.InsertEdge(1, 5, 20);
	g1.InsertEdge(5, 8, 45);
	g1.InsertEdge(5, 1, 12);
	g1.InsertEdge(8, 13, 99);
	g1.InsertEdge(2, 13, 125);
	g1.InsertEdge(2, 5, 54);
	g1.InsertEdge(13, 1, 49);

	// ��������� �������� �������� �� ������� 5
	vector<int> v = { 12, 0, 45, INT_MAX, 144 }; // ��������� ���������� ����
	vector<int> v1 = g1.dijkstra(5);
	EXPECT_EQ(v1, v);

	// ��������� �������� �������� �� ������� 2
	v = { 66, 54, 99, 0, 125 };
	v1 = g1.dijkstra(2);
	EXPECT_EQ(v1, v);

	// ��������� �������� �������� �� ������� 1
	v = { 0, 20, 65, INT_MAX, 164 };
	v1 = g1.dijkstra(1);
	EXPECT_EQ(v1, v);

	// ��������� ��������� ���������� ��� ������� ���������� ����� �� �������������� �������
	try {
		v1 = g1.dijkstra(5);
	}
	catch (invalid_argument const& ex) {
		string s = ex.what();
		EXPECT_EQ(s, "����������� ��������� �������");
	}
}

// ������������ ������ � ������ ����� �� �����
TEST(TestGraph, TestToFromFile) {

	// ������� ���� � ������������ �������� 2
	Graph<int> g1(2);
	vector<int> v;

	// ��������� ������ ������� ����� (������ ���������� ����������)
	try {
		g1.WriteToFile("errortest1.txt");
	}
	catch (invalid_argument const& ex) {
		string s = ex.what();
		EXPECT_EQ(s, "������ ����");
	}

	// ��������� �������
	g1.InsertVertex(1);
	g1.InsertVertex(5);
	g1.InsertVertex(8);
	g1.InsertVertex(2);
	g1.InsertVertex(13);

	// ��������� ���� � ������
	g1.InsertEdge(1, 5, 20);
	g1.InsertEdge(5, 8, 45);
	g1.InsertEdge(5, 1, 12);
	g1.InsertEdge(8, 13, 99);
	g1.InsertEdge(2, 13, 125);
	g1.InsertEdge(2, 5, 54);
	g1.InsertEdge(13, 1, 49);

	// ���������� ���� � ����
	g1.WriteToFile("graphtest1.txt");

	// ������� ����� ���� � ��������� ������ �� �����
	Graph<int> g2;
	g2.ReadFromFile("graphtest1.txt");

	// ���������, ��� ������� ���������
	EXPECT_EQ(g1.GetVertexList(), g2.GetVertexList());

	// ���������, ��� ������� ��������� ���������
	int** matr1 = g1.GetEdges();
	int** matr2 = g2.GetEdges();

	for (int i = 0; i < g1.NumberOfVertices(); i++) {
		for (int j = 0; j < g1.NumberOfVertices(); j++) {
			EXPECT_EQ(matr1[i][j], matr2[i][j]);
		}
	}
}