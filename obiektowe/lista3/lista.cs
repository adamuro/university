public class Node<T> {
	public Node (T val) {
		Value = val;
	}

	public T Value {get;}
	public Node<T> Prev {set; get;}
	public Node<T> Next {set; get;}
}

public class Lista<T> {
	public Lista () {
		Head = null;
		Tail = null;
	}

	private Node<T> Head;
	private Node<T> Tail;

	public bool empty () {
		return (Head == null && Tail == null);
	}

	public void PushFront (T value) {
		if(empty()) {
			Node<T> newNode = new Node<T> (value);
			newNode.Next = null;
			newNode.Prev = null;
			Head = newNode;
			Tail = newNode;
		}
		else {
			Node<T> newHead = new Node<T> (value);
			newHead.Next = Head;
			Head.Prev = newHead;
			Head = newHead;
		}
	}

	public void PushBack (T value) {
		if(empty()) {
			Node<T> newNode = new Node<T> (value);
			newNode.Next = null;
			newNode.Prev = null;
			Head = newNode;
			Tail = newNode;
		}
		else {
			Node<T> newTail = new Node<T> (value);
			newTail.Prev = Tail;
			Tail.Next = newTail;
			Tail = newTail;
		}
	}

	public T PopFront () {
		if(empty()) {
			System.IndexOutOfRangeException indEx = new System.IndexOutOfRangeException("Nie mozna usunac elementu: lista jest pusta.");
			throw indEx;
		}
		T HeadValue = Head.Value;
		if(Head.Next != null) {
			Head = Head.Next;
			if(Head.Next != null) {
				Head.Next.Prev = Head;
			}
			Head.Prev = null;
		}
		else {
			Head = null;
			Tail = null;
		}
		return HeadValue;
	}

	public T PopBack () {
		if(empty()) {
			System.IndexOutOfRangeException indEx = new System.IndexOutOfRangeException("Nie mozna usunac elementu: lista jest pusta.");
			throw indEx;
		}
		T TailValue = Tail.Value;
		if(Tail.Prev != null) {
			Tail = Tail.Prev;
			if(Tail.Prev != null) {
				Tail.Prev.Next = Tail;
			}
			Tail.Next = null;
		}
		else {
			Head = null;
			Tail = null;
		}
		return TailValue;
	}
}