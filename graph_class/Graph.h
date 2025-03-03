//author:�������� �����
#pragma once


#include <stdexcept> // ��� ����������
#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <fstream>
#include <string>
#include <sstream>
#include <climits> 

#include "LinkedList.h"

using namespace std;

// ����� �����
template <typename T>
class Graph
{
private:
	// �������� ������ �������� ������ ������, ������� ���������
	//� ������� ������ (����� ������) �����
	LinkedList<T> vertexList; // ������ ������
	int** edge;  // ������� ���������
	int graphsize; // ����� ������ � �����
	int maxGraphSize; // ������������ ����� ������ � �����

	// ������ ��� ������ ������� � �������� �� ������� � ������
	//int FindVertex(LinkedList<T>& L1, const T& vertex1);
	int GetVertexPos(const T& vertex1) const;

public:
	// ����������� � �������� ������������� ����� ������ maxsize
	Graph(int maxsize = 1);

	// ����������� ����������� � �.�

	// ����������
	~Graph();

	// ������ �������� �����
	bool GraphEmpty() const; // true, ���� ���� ����

	// ������ ��������� ������

	// ���������� ������
	int NumberOfVertices() const;

	// ���������� ����
	int NumberOfEdges() const;

	// ��������� ���� �����
	int GetWeight(const T& vertex1, const T& vertex2) const;
	int GetWeightByInd(int ver1, int ver2) const;

	// ��������� ������ �� �������� ������
	vector<T> GetNeighbors(const T& vertex) const;
	// ��������� �������� ������, � ������� ���� ����
	vector<T> GetFolowers(const T& vertex) const;

	// ������ ����������� �����

	// ������� �������
	void InsertVertex(const T& vertex);

	// ������� �����
	void InsertEdge(const T& vertex1, const T& vertex2, int weight);

	// �������� �������
	void DeleteVertex(const T& vertex);

	// �������� �����
	void DeleteEdge(const T& vertex1, const T& vertex2);

	// �������
	//void ReadGraph(char* filename);
	//int MinimumPath(const T& sVertex, const T& sVertex);

	// ����� � �������
	vector<T> DepthFirstSearch(const T& beginVertex) const;

	// ����� � ������
	vector<T> BreadthFirstSearch(const T& beginVertex) const;

	// ������ �� �����
	void ReadFromFile(const string& filename);
	// ������ � ����
	void WriteToFile(const string& filename) const;

	// �������� ��������
	// ���������� ������ �� ���������� ����� �� ������ ������� �� ������� beginVertex
	vector<T> dijkstra(const T& beginVertex) const;

	// �������� ��� ������ ������
	//friend class VertexIterator<T>;

	// ������ ������������� ���������� ������
	int GetMaxSize() const;

	// ��������� ������ ������
	vector<T> GetVertexList() const;

	// ��������� ������� ���������
	T** GetEdges() const;

	// ������� �����
	void ClearGraph();
};

// �����������, �������� ������� ��������� � ���������� graphsize
// �������� ������ ��� ������� ���������
template <typename T>
Graph<T>::Graph(int maxsize)
{
	edge = nullptr;

	// ������ cout ����������� ����������
	if (maxsize <= 0) {
		throw invalid_argument("������������ ������������ ���������� ������");
		//std::cout << "������������ ����������� �������";
	}
	maxGraphSize = maxsize;

	// ��������� ������ ��� �������
	edge = new int* [maxGraphSize];//���������� ������ ��� ������� ����������.

	//��� ������� ��������� ���������� ������ ��� ������ int, ������ �������� ����� maxGraphSize.
	for (int i = 0; i < maxGraphSize; i++) {
		edge[i] = new int[maxGraphSize];
	}

	// ���������� ������� ��������� ������
	for (int i = 0; i < maxGraphSize; i++)
		for (int j = 0; j < maxGraphSize; j++)
			edge[i][j] = 0;
	// memset ��� memfill

	// ����������� ���������� ������ � ����� = 0
	graphsize = 0;

}

// ����������
template <typename T>
Graph<T>::~Graph() {
	// ���������� ������, ���������� ��� �������
	// ���� ��� ������ ���� ���������
	if (edge != nullptr) {

		for (int i = 0; i < maxGraphSize; i++) {
			delete[] edge[i];
		}

		delete[] edge;
	}

}

// ����� �������� ����� �� ���������� ������, true, ���� ���� ����
template <typename T>
bool Graph<T>::GraphEmpty() const {
	if (graphsize == 0) {
		return true;
	}
	else return false;
}

// ������� �����
template <typename T>
void Graph<T>::ClearGraph() {
	vertexList.ClearList();

	// ���������� ������� ��������� ������
	for (int i = 0; i < maxGraphSize; i++)
		for (int j = 0; j < maxGraphSize; j++)
			edge[i][j] = 0;

	graphsize = 0;

}

// ���������� ������
template <typename T>
int  Graph<T>::NumberOfVertices() const {
	return graphsize;
}

// ���������� ����
template <typename T>
int Graph<T>::NumberOfEdges() const {
	int res = 0;
	for (int i = 0; i < graphsize; i++) {
		for (int j = 0; j < graphsize; j++) {
			if (edge[i][j] != 0)
				res++;
		}
	}
	return res;
}

// ����������� ���������� ������
template <typename T>
int Graph<T>::GetMaxSize() const {
	return maxGraphSize;
}

// ��������� ������ ������
template <typename T>
vector<T> Graph<T>::GetVertexList() const {
	return vertexList.ListToVec();
}


// ��������� ������� ���������
template <typename T>
T** Graph<T>::GetEdges() const {
	return edge;
}

// ��������� ������� ������� � ������
// ���� ������� ���, �� ���������� -1
template <typename T>
int Graph<T>::GetVertexPos(const T& vertex1) const {

	return vertexList.searchNodeInd(vertex1);

}

// ��������� ���� �����
template <typename T>
int Graph<T>::GetWeight(const T& vertex1, const T& vertex2) const {

	int ver1 = GetVertexPos(vertex1);
	int ver2 = GetVertexPos(vertex2);

	if ((ver1 == -1) || (ver2 == -1)) {
		throw invalid_argument("����������� ��������� �������");
	}
	else
		return edge[ver1][ver2];

}

// ��������� ���� ����� �� �������� ������
template <typename T>
int Graph<T>::GetWeightByInd(int ver1, int ver2) const {


	if ((ver1 == -1) || (ver2 == -1)) {
		throw invalid_argument("����������� ��������� �������");
	}
	else
		return edge[ver1][ver2];

}

// ��������� �������
template <typename T>
vector<T> Graph<T>::GetNeighbors(const T& vertex) const {
	vector<T> v = {};// ������� ������ ������ ��� �������� �������
	int pos = GetVertexPos(vertex);// �������� ������� ������� � ������ ������

	if (pos <= -1) {
		throw invalid_argument("����������� ��������� �������");
	}
	else {
		for (int i = 0; i < graphsize; i++)// �������� �� ���� ��������
		{
			if (edge[pos][i] != 0)// ���� ���������� ����� �� vertex � ������� i
				v.push_back(vertexList.dataByInd(i));// ��������� ������� i � ������ �������
			else if (edge[i][pos] != 0)// ���� ���������� ����� �� ������� i � vertex
				v.push_back(vertexList.dataByInd(i));// ��������� ������� i � ������ �������
		}
		return v;
	}

}

//�������, � ������� ������� ����� �� ������� vertex
template <typename T>
vector<T> Graph<T>::GetFolowers(const T& vertex) const {
	vector<T> v = {}; // ������� ������ ������ ��� �������� �������
	int pos = GetVertexPos(vertex);// �������� ������ �������

	if (pos <= -1) {
		throw invalid_argument("����������� ��������� �������");
	}
	else {
		for (int i = 0; i < graphsize; i++)
		{
			if (edge[pos][i] != 0)// ���� ���������� ����� �� vertex � ������� i
				v.push_back(vertexList.dataByInd(i));
			//else if (edge[i][pos] != 0)
				//v.push_back(vertexList.dataByInd(i));
		}
		return v;
	}
}

// ����� ������� �������
template <typename T>
void Graph<T>::InsertVertex(const T& vertex)
{
	// ���������, �������� �� ���� �, ���� ��, ��������� maxGraphSize
	if ((graphsize + 1) == maxGraphSize) {

		int newmaxGraphSize = maxGraphSize * 2;

		// �������� ����� ������� ��������� � ����������� ��������
		int** temp = new int* [newmaxGraphSize];
		for (int i = 0; i < newmaxGraphSize; i++) {
			temp[i] = new int[newmaxGraphSize];
		}

		// ���������� ������� ��������� ������
		for (int i = 0; i < newmaxGraphSize; i++)
			for (int j = 0; j < newmaxGraphSize; j++)
				temp[i][j] = 0;
		// memset ��� memfill

		// ����������� �������� �� ������ ������� ��������� � ����� 
		for (int i = 0; i < maxGraphSize; i++)
		{
			for (int j = 0; j < maxGraphSize; j++)
			{
				temp[i][j] = edge[i][j];
			}
			// memcpy
		}

		// ������������ ������ ������ ������� ���������
		for (int i = 0; i < maxGraphSize; i++) {
			delete[] edge[i];
		}
		delete[] edge;

		// ��������� ���� ������
		edge = temp;
		maxGraphSize = newmaxGraphSize;
	}

	// ���������� ����� ������� � ������ ������
	vertexList.addNode(vertex);

	// ���������� ���� ���������� ������ �����
	graphsize++;
}

// ������� ������� �� ������ ������ � ��������������� �������
// ���������, ������ ������������� ���� ������� �����
template <typename T>
void Graph<T>::DeleteVertex(const T& vertex)
{
	// �������� ������� ������� � ������ ������
	int pos = GetVertexPos(vertex);
	//int row, col;
	// ���� ����� ������� ���, �������� �� ���� � ������� ����������
	if (pos == -1)
	{
		throw invalid_argument("����������� ��������� �������");
	}

	// ������� ������� � ��������� graphsize
	vertexList.removeNode(vertex);



	int i = 0;
	// �������� ������� �� ������� ���������
	while (pos < graphsize) {
		// �������� ������ ������� �����, ����� ������� ������� � �������� ��������
		for (i = 0; i < graphsize; ++i) {
			edge[i][pos] = edge[i][pos + 1];// �������� �������� �� ���� ������� �����
		}

		// �������� ������� �����, ����� ������� ������ � �������� ��������
		for (i = 0; i < graphsize; ++i) {
			edge[pos][i] = edge[pos + 1][i];// �������� �������� ������ �����
		}
		pos++;// ��������� � ��������� ������ � �������
	}

	// ��������� ���������� ������ � �����, �������� graphsize
	graphsize = vertexList.ListSize();

}

// ������� �����
template <typename T>
void Graph<T>::InsertEdge(const T& vertex1, const T& vertex2, int weight) {
	int ver1 = GetVertexPos(vertex1);
	int ver2 = GetVertexPos(vertex2);

	if ((ver1 == -1) || (ver2 == -1)) {
		throw invalid_argument("����������� ��������� �������");
	}
	else {
		edge[ver1][ver2] = weight;
	}

}

// �������� �����
template <typename T>
void Graph<T>::DeleteEdge(const T& vertex1, const T& vertex2) {
	int ver1 = GetVertexPos(vertex1);
	int ver2 = GetVertexPos(vertex2);

	if ((ver1 == -1) || (ver2 == -1)) {
		throw invalid_argument("����������� ��������� �������");
	}
	else {
		edge[ver1][ver2] = 0;
	}
}


// ������ �����

// ����� � �������
template <typename T>
vector<T> Graph<T>::DepthFirstSearch(const T& beginVertex) const {

	if (GetVertexPos(beginVertex) == -1) {
		throw invalid_argument("����������� ��������� �������");
	}

	// ���� ��� ���������� �������� ������, ��������� ���������
	stack<T> st;


	// L - ������ ���������� ������. adjL �������� �������,
	// ������� � �������
	vector<T> l = {}, adjl = {};

	T vertex1;

	st.push(beginVertex);

	// ���������� �����, ���� �� �������� ����
	while (!st.empty()) {
		// ���������� ��������� �������
		vertex1 = st.top();
		st.pop();
		// ���� ������� ��� �� ���� �������� (�� ��������� � ������ ���������� ������ l)
		if (find(l.begin(), l.end(), vertex1) == l.end()) {
			//�������� ������� � L
			l.push_back(vertex1);

			//� ����� �������� ��� ������� � ��� �������
			adjl = GetFolowers(vertex1);

			// ��������� ��� ������� ������� � ����
			for (T item : adjl) {
				st.push(item);
			}
		}
	}
	// ���������� �������� ������
	return l;
}

// ����� � ������
template <typename T>
vector<T> Graph<T>::BreadthFirstSearch(const T& beginVertex) const {

	if (GetVertexPos(beginVertex) == -1) {
		throw invalid_argument("����������� ��������� �������");
	}

	// ������� ��� ���������� �������� ������, ��������� ���������
	queue<T> qu;

	// L - ������ ���������� ������. adjL �������� �������,
	// ������� � �������
	vector<T> l = {}, adjl = {};

	T vertex1;

	qu.push(beginVertex);

	// ���������� �����, ���� �� �������� �������
	while (!qu.empty()) {
		// ���������� ��������� �������
		vertex1 = qu.front();
		qu.pop();
		// ���� ������� ��� �� ���� �������� (�� ��������� � ������ ���������� ������ l)
		if (find(l.begin(), l.end(), vertex1) == l.end()) {
			//�������� ������� � L
			l.push_back(vertex1);

			//� ����� �������� ��� ������� � ��� �������
			adjl = GetFolowers(vertex1);

			// ��������� ��� ������� ������� � �������
			for (T item : adjl) {
				qu.push(item);
			}
		}
	}
	// ���������� �������� ������
	return l;
}


// �������� ����� �� �����
// todo ������� ��� ��, ��� �������� � �����
template <typename T>
void Graph<T>::ReadFromFile(const string& filename) {
	ifstream fin(filename);

	if (!fin.is_open()) // ���� ���� �� ��� ������
	{
		throw invalid_argument("���� �� ����� ���� ������");
	}
	else {
		this->ClearGraph(); // ������� ����
		string line;

		int numberOfVerticies = 0;

		//numberOfVerticies = fin.readline();
		getline(fin, line);

		numberOfVerticies = stoi(line);

		T node;
		//
		for (int i = 0; i < numberOfVerticies; i++) {
			getline(fin, line);
			//std::istringstream - ��� ������ ������ string, 
			//������� ������������ ��� �������������� ������ � ��������� ����������,
			//� ���������� ����� ����� ���� ������������� � ������.
			std::istringstream iss(line);
			if (!(iss >> node)) {
				// � ������ ������ ������ ������
				throw invalid_argument("������ ������ �����");
			}
			this->InsertVertex(node);
		}

		T vertex_1, vertex_2;
		int weight_1;

		// ������ ����� ���������
		while (std::getline(fin, line))
		{
			std::istringstream iss(line);

			// ��������� �� ������ ��� ������� � ��� �����
			if (!(iss >> vertex_1 >> vertex_2 >> weight_1))
			{
				// � ������ ������ ������ ������
				throw invalid_argument("������ ������ �����");
			}

			// ��������� ����� � ����
			InsertEdge(vertex_1, vertex_2, weight_1);
		}

		// ��������� ���� ����� ������
		fin.close();

		// ��������� ���� ������
		graphsize = numberOfVerticies;
	}
}

// ������ ����� � ����.
template <typename T>
void Graph<T>::WriteToFile(const string& filename) const {
	ofstream fout(filename);

	if (!fout.is_open()) // ���� ���� �� ��� ������
	{
		throw invalid_argument("���� �� ����� ���� ������");
	}
	else if (graphsize == 0) {
		fout.close();
		throw invalid_argument("������ ����");
	}
	else {
		int number = this->NumberOfVertices();
		fout << number << endl;

		vector<T> vec = this->vertexList.ListToVec();
		for (int i = 0; i < number; i++) {
			fout << vec[i] << endl;
		}

		int numberEdge = 0;// ���������� �����
		/// ������ �� ������� ���������
		for (int i = 0; i < NumberOfVertices(); i++)
		{
			for (int j = 0; j < NumberOfVertices(); j++)
			{
				if (edge[i][j] != 0) {
					// ������� 2 ������� � �����
					fout << vertexList.dataByInd(i) << " " << vertexList.dataByInd(j) << " " << edge[i][j] << "\n";
					numberEdge++;
				}
			}
		}


		fout.close();

	}
}


// �������� ��������
// ���������� ������ �� ���������� ����� �� ������ ������� �� ������� beginVertex
template <typename T>
vector<T> Graph<T>::dijkstra(const T& beginVertex) const {
	int pos = GetVertexPos(beginVertex);
	if (pos == -1) {
		throw invalid_argument("����������� ��������� �������");
	}

	vector<int> d; // ������ ���������� ���������
	vector<bool> used; // ������ ���������

	// ���������� ���������� �� ������ ���������� (INT_MAX)
	// ��� ������� �� �������� (false)
	for (int i = 0; i < NumberOfVertices(); i++) {
		d.push_back(INT_MAX);
		used.push_back(false);
	}

	d[pos] = 0; // ���������� �� ������� �� ����� ���� ����� 0

	// ��������� ��� ���� ������ �����
	for (int k = 0; k < NumberOfVertices(); k++) {
		// ��� ������ ������� ������� ���������� �� ���� ������ ������ �� ������� ���������
		for (int i = 0; i < NumberOfVertices(); i++) {
			int w = GetWeightByInd(pos, i);

			if (w < 0) {
				throw invalid_argument("�������� �������� �� ������������ ������������� ����");
			}

			// ���� ���� �� ������� ����, ���� ������� ��� �� ���� �������� �
			// ���� ������ ������� ���������� �� ������ �������
			if ((w != 0) && (used[i] == false) && ((d[pos] + w) < d[i])) {
				d[i] = d[pos] + w; // ���������� ����� �������� ����������� ����
			}
		}
		// ������� ��������, ����� �� ������� ��������� ���� ��������� ��� ������� ������������ ������
		used[pos] = true;

		// ������� ������ � ����������� ��������� ���������� �� ������ ������
		// (�� ��������������� ������)
		int min1 = INT_MAX;
		for (int j = 0; j < NumberOfVertices(); j++) {
			if ((d[j] < min1) && (used[j] == false)) {
				pos = j; // ���������� ������ ������ �������
				// �� �� ����������� ����� ���������� ����� �� ��������� ������
			}
		}

	}
	return d;


}
