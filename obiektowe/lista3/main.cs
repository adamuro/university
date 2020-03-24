using System;

class Testy
{
	static void Main () {
		Lista<int> list = new Lista<int> ();
		Console.WriteLine("empty: {0}", list.empty()); // Czy nowa lista jest pusta?
		Console.WriteLine("pushFront(1)");
		list.PushFront(1);
		Console.WriteLine("empty: {0}", list.empty()); // Czy lista po dodaniu elementu jest pusta?
		Console.WriteLine("popBack(): {0}", list.PopBack()); // Czy usuwanie dziala poprawnie?
		Console.WriteLine("empty: {0}", list.empty()); // Czy lista po usunieciu wszystkich elementow znow jest pusta?
		try {
			Console.WriteLine("popFront(): {0}", list.PopFront()); // Czy wyjatek przy probie usuniecia elementu
		}														   // z pustej listy jest poprawnie obslugiwany?
		catch (System.IndexOutOfRangeException indEx) {
			Console.WriteLine(indEx.Message);
		}
		Console.WriteLine("pushFront(2) [2]"); // Nieco bardziej skomplikowany test dodawania i usuwania.
		list.PushFront(2);
		Console.WriteLine("pushFront(1) [1, 2]");
		list.PushFront(1);
		Console.WriteLine("pushBack(3) [1, 2, 3]");
		list.PushBack(3);
		Console.WriteLine("popFront(): {0}", list.PopFront());
		Console.WriteLine("popBack(): {0}", list.PopBack());
		Console.WriteLine("pushBack(4) [2, 4]");
		list.PushBack(4);
		Console.WriteLine("pushFront(1) [1, 2, 4]");
		list.PushFront(1);
		Console.WriteLine("popBack(): {0}", list.PopBack());
		Console.WriteLine("popFront(): {0}", list.PopFront());
		Console.WriteLine("popFront(): {0}", list.PopFront());

		

		return;
	}
}