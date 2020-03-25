using System;

public class Node<K,V> where K : IComparable {
	public Node (K key, V value) {
		Key = key;
		Value = value;
		Next = null;
		Prev = null;
	}

	public K Key {get;}
	public V Value {get;}
	public Node<K,V> Next {set; get;}
	public Node<K,V> Prev {set; get;}
}

public class Slownik<K,V> where K : IComparable {
	public Slownik () {
		Head = null;
	}

	private Node<K,V> Head;

	public void Add (K key, V value) {
		if(Head == null) {
			Head = new Node<K,V> (key, value);
		}
		else {
			Node<K,V> newHead = new Node<K,V> (key, value);
			newHead.Next = Head;
			Head.Prev = newHead;
			Head = newHead;
		}
	}

	public void Delete (K key) {
		Node<K,V> Search = Head;
		while(Search != null && key.CompareTo(Search.Key) != 0) {
			Search = Search.Next;
		}
		if(Search == null) {
			Console.WriteLine("Nie znaleziono elementu o podanym kluczu.");
		}
		else {
			if(Search.Prev != null) {
				Search.Prev.Next = Search.Next;
			}
			if(Search.Next != null) {
				Search.Next.Prev = Search.Prev;
			}
		}
	}

	public V Find (K key) {
		Node<K,V> Search = Head;
		while(Search != null && key.CompareTo(Search.Key) != 0) {
			Search = Search.Next;
		}
		if(Search == null) {
			System.IndexOutOfRangeException indEx = new System.IndexOutOfRangeException("Nie znaleziono elementu o podanym kluczu.");
			throw indEx;
		}
		else {
			return Search.Value;
		}
	}
}