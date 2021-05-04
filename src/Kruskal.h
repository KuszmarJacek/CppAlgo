#pragma once

#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <filesystem>

class Edge
{
public:
	Edge(int source, int dest, double weight) :
		source{ source },
		dest{ dest },
		weight{ weight }
	{}

	Edge() = default;

	int source;
	int dest;
	double weight;
};

class Vertex
{
public:
	Vertex(double x, double y) :
		x{ x },
		y{ y }
	{}

	double x;
	double y;
};

class DisjointSet
{
public:
	DisjointSet(int vertexCnt) :
		vertexCnt{ vertexCnt },
		parents(vertexCnt, 0),
		ranks(vertexCnt, 1)
	{
		for(int i = 0; i < vertexCnt; ++i)
		{
			parents[i] = i;
		}
	}

	DisjointSet() = default;

	int vertexCnt;
	std::vector<int> parents;
	std::vector<int> ranks;

	int find(int vertexId, bool enablePathCompression)
	{
		int root = vertexId;

		while(root != parents[root])
		{
			root = parents[root];
		}

		if(enablePathCompression)
		{
			while(vertexId != root)
			{
				int next = parents[vertexId];
				parents[vertexId] = root;
				vertexId = next;
			}
		}

		return root;
	}

	void unify(int set1, int set2)
	{
		int root1 = find(set1, true);
		int root2 = find(set2, true);

		if(root1 == root2)
		{
			return;
		}

		if(ranks[root1] < ranks[root2])
		{
			ranks[root2] += ranks[root1];
			parents[root1] = root2;
		}
		else
		{
			ranks[root1] += ranks[root2];
			parents[root2] = root1;
		}

		if(ranks[root1] == ranks[root2])
		{
			//parent[root1] = root2;???
			ranks[root1]++;
		}
	}
};

class Graph
{
public:
	Graph(std::filesystem::path filePath) :
		filePath{ filePath },
		mstWeight{ 0.0 }
	{
		std::fstream file(filePath.string(), std::ios_base::in);

		double tmp1;
		double tmp2;
		int tmpIndex1;
		int tmpIndex2;

		file >> vertexCnt;

		for(int i = 0; i < vertexCnt; i++)
		{
			file >> tmp1;
			file >> tmp2;
			vertices.emplace_back(Vertex(tmp1, tmp2));
		}

		file >> edgeCnt;

		for(int i = 0; i < edgeCnt; i++)
		{
			file >> tmpIndex1;
			file >> tmpIndex2;
			file >> tmp1;
			edges.emplace_back(Edge(tmpIndex1, tmpIndex2, tmp1));
		}

		file.close();
	}

	Graph() = default;

	std::filesystem::path filePath;
	std::list<std::pair<std::pair<int, int>, double>> mst;
	std::vector<Vertex> vertices;
	std::vector<Edge> edges;
	double mstWeight;
	int vertexCnt;
	int edgeCnt;

	void kruskal()
	{
		std::sort(edges.begin(), edges.end(), [](Edge& lhs, Edge& rhs) -> bool
		{
			return lhs.weight < rhs.weight;
		});

		DisjointSet ds(vertexCnt);

		for(auto it = edges.begin(); it != edges.end(); ++it)
		{
			int setSource = ds.find(it->source, true);
			int setDest = ds.find(it->dest, true);

			if(setSource != setDest)
			{
				mst.push_back({ {it->source, it->dest}, it->weight });
				mstWeight += it->weight;
				ds.unify(setSource, setDest);
			}
		}
	}

	void displayMST()
	{
		for(const auto& line : mst)
		{
			std::cout << line.first.first << " - " << line.first.second << " " << line.second << "\n";
		}
		std::cout << mstWeight;
	}
};
