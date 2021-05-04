#include "DemoClasses.h"
#include "Fourier.h"
#include "LinkedList.h"
#include "ArrayList.h"
#include "BST.h"
#include "RBT.h"
#include "HashTable.h"
#include "Sorting.h"
#include "Kruskal.h"
#include "ConvexHull.h"


//Main contains some demo code for each algorithm/data structure
int main()
{
	//Fourier
	/*std::vector<std::complex<double>> arr{ (1. + 0.0i), (2.0 - 1.0i), (0.0 - 1.0i), (-1.0 + 2.0i) };

	std::vector<std::complex<double>> x = dft(arr);

	for(auto& val : x)
	{
		std::cout << val << '\n';
	}

	fft(arr);

	for(auto& val : arr)
	{
		std::cout << val << '\n';
	}*/


	//LinkedList
	/*LinkedList<Foo> foo_ll;
	foo_ll.push_front(Foo(0, "Foo0"));
	foo_ll.push_back(Foo(1, "Foo1"));
	foo_ll.push_back(Foo(3, "Foo2"));
	foo_ll.push_back(Foo(5, "Foo3"));
	foo_ll.push_back(Foo(7, "Foo7"));
	foo_ll.push_back(Foo(10, "Foo10"));

	Foo example(1, "Foo1");
	foo_ll.ordered_insert(example);

	Foo example2(1, "Foo4");

	auto comparator = [foo_ll](Foo& lhs, Foo& rhs) -> bool
	{
		return lhs.getName() < rhs.getName();
	};

	foo_ll.ordered_insert(example2, comparator);

	std::cout << foo_ll;

	foo_ll.pop_front();
	foo_ll.pop_back();

	Foo foo2 = foo_ll[1];
	foo_ll[1] = { 69420, "newCoolerFoo" };

	Foo match(69420, "newCoolerFoo");
	LinkedList<Foo>::Elem* foo_elem_ptr = foo_ll.fetch_match(match);

	foo_ll.remove_match(match);

	std::cout << foo_ll;

	foo_ll.erase();

	for(int i = 0; i < 50; ++i)
	{
		foo_ll.push_back(Foo(i + 10, "Fooloop"));
	}

	Foo forMatch(0, "Fooloop");
	LinkedList<Foo>::Elem* loop_ptr;

	auto timePoint1 = std::chrono::system_clock::now();
	for(int i = 0; i < 50; ++i)
	{
		forMatch = { i, "Fooloop" };
		loop_ptr = foo_ll.fetch_match(forMatch);
	}
	auto timePoint2 = std::chrono::system_clock::now();

	std::chrono::duration<double> diff = timePoint2 - timePoint1;

	std::cout << foo_ll;

	std::cout << diff.count() << '\n';

	timePoint1 = std::chrono::system_clock::now();
	for(int i = 0; i < 50; ++i)
	{
		forMatch = { i, "Fooloop" };
		foo_ll.remove_match(forMatch);
	}
	timePoint2 = std::chrono::system_clock::now();

	diff = timePoint2 - timePoint1;

	std::cout << diff.count();*/

	//ArrayList
	/*ArrayList<Bar> fooAl;
	fooAl.emplaceBack(Bar(420));

	std::cout << fooAl;

	ArrayList<int> al;
	al.emplaceBack(20);
	al.emplaceBack(2);
	al.emplaceBack(5);
	al.emplaceBack(6);
	al.emplaceBack(100);
	al.emplaceBack(1);
	al.emplaceBack(91);
	al.emplaceBack(19);
	al.emplaceBack(1);
	al.emplaceBack(15);
	al.emplaceBack(14);
	al.sort();
	std::cout << al[10];

	ArrayList<std::string> strAL;
	strAL.emplaceBack("za");
	strAL.emplaceBack("ya");
	strAL.emplaceBack("xa");
	strAL.emplaceBack("wa");
	strAL.emplaceBack("va");
	strAL.emplaceBack("ua");

	std::cout << strAL;
	std::cout << "----\n";
	strAL.sort();
	std::cout << strAL;

	al.clear();
	strAL.clear();*/

	//BST
	/*BST<int> tree;
	tree.insert(12);
	tree.insert(10);
	tree.insert(20);
	tree.insert(8);
	tree.insert(11);
	tree.insert(15);
	tree.insert(28);
	tree.insert(4);
	tree.insert(2);
	tree.inOrder(true);
	std::cout << tree.depth();
	tree.clear();
	tree.inOrder(true);

	BST<std::string> dict;
	dict.insert("a");
	dict.insert("b");
	dict.insert("c");
	dict.insert("d");
	dict.insert("e");
	dict.inOrder(true);
	dict.clear();*/

	//Red-Black Tree
	/*RBT<int> rbt;
	auto comparator = [](int l, int r) -> int
	{
		return l > r ? 0 : 1;
	};

	rbt.insert(5, comparator);
	rbt.insert(1, comparator);
	rbt.insert(3, comparator);
	rbt.insert(4, comparator);
	rbt.insert(2, comparator);
	rbt.insert(2, comparator);
	RBT<int>::Node* n = rbt.find(5);
	rbt.print();
	rbt.clear();*/

	//HashTable
	/*HashTable<int> ht;
	int a = ht.hash("asdfgh");
	ht.insert("a", 10);
	ht.insert("b", 1);
	ht.insert("c", 2);
	ht.insert("d", 3);
	ht.insert("e", 4);
	ht.insert("f", 4);
	ht.insert("g", 4);
	ht.insert("gh", 12);
	ht.insert("h", 4);
	ht.insert("i", 4);
	ht.insert("j", 4);
	ht.insert("k", 4);
	ht.insert("l", 4);
	ht.insert("m", 4);
	ht.remove("mmm");
	HashTable<int>::Pair* pair2 = ht.search("ga");
	ht.print();*/

	//Sorting algorithms
	//MaxHeap<int> mh1(
	//	new std::vector<int>{ 1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17 },
	//	MaxHeap<int>::FixMethod::Williams
	//);
	//mh1.sort();

	//MaxHeap<int> mh2(
	//	new std::vector<int>{ 1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17 },
	//	MaxHeap<int>::FixMethod::Floyd
	//);
	//mh2.sort();

	//MaxHeap<int> mh3(
	//	new std::vector<int>{ 9, 8, 5, 7, 1, 2, 4, 3, 6 },
	//	MaxHeap<int>::FixMethod::Floyd
	//);
	//mh3.sort();

	//int nmax = 6;
	//std::vector<int> a{ 5, 3, 4, 2, 3, 1, 3, 5, 2, 4 };
	//countingSortNatural(a, nmax);

	//std::vector<int> b{ 5, 3, 4, 2, 3, 1, -1, 3, 5, 2, 4 };
	//int max = *std::max_element(b.begin(), b.end());
	//int min = *std::min_element(b.begin(), b.end());
	//countingSortInteger(b, 7, max, min);

	//double arr[]{ 36.1, 5.7, 94.2, 7.6, 48.2, 16.9, 16.1, 7.8, 25.5, 92.1, 33.3, 44.1, 57.1, 22.0, 12.0 , 16.0, 90.95, 90.96, 90.97, 10.0002 };
	//bucketSort<20>(arr, 100);
	//bucketSort<double, 20>(arr, 100, [](const double& lhs, const double& rhs) -> bool { return lhs > rhs; });

	//TODO: Add kruskal and convex hull

	return 0;
}