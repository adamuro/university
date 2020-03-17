using System;

class Program {
	class Node {
		public int Index {get;}
		public int Value {get; set;}
		public Node Next {get; set;}
		public Node Prev {get; set;}

		public Node (int ind, int val) {
			Index = ind;
			Value = val;
			Next = null;
			Prev = null;
		}
	}

	class Array {
		Node List;
		int start;
		int end;

		public Array (int s, int e) {
			if(s > e) {
				Console.WriteLine("Niepoprawna inicjalizacja tablicy: pierwszy indeks wiekszy od ostatniego.");
			}
			else {
				start = s;
				end = e;
				List = new Node(start, 0);
				for(int i = start + 1; i <= end; i++) {
					List.Next = new Node(i, 0);
					Node temp = List;
					List = List.Next;
					List.Prev = temp;
				}
			}
		}
		public int get (int ind) {
			goToIndex(ind);
			if(List.Index == ind) {
				return List.Value;
			}
			else {
				Console.WriteLine("Indeks poza granicami tablicy.");
				return 0;
			}
		}
		public void set (int ind, int val) {
			goToIndex(ind);
			if(List.Index == ind) {
				List.Value = val;
			}
			else {
				Console.WriteLine("Indeks poza granicami tablicy.");
			}
		}
		public void changeBounds (int newStart, int newEnd) {
			if(newStart > newEnd) {
				Console.WriteLine("Niepoprawne granice tablicy: pierwszy indeks wiekszy od ostatniego.");
				return;
			}
			if(newEnd < start || newStart > end) {
				start = newStart;
				end = newEnd;
				List = new Node(start, 0);
				for(int i = start + 1; i <= end; i++) {
					List.Next = new Node(i, 0);
					Node temp = List;
					List = List.Next;
					List.Prev = temp;
				}
				return;
			}
			if(newStart < start) {
				goToIndex(start);
				for(int i = start - 1; i >= newStart; i--) {
					List.Next = new Node(i, 0);
					Node temp = List;
					List = List.Prev;
					List.Next = temp;
				}
				start = newStart;
			}
			else {
				goToIndex(newStart);
				start = newStart;
				List.Prev = null;
			}
			if(newEnd > end) {
				goToIndex(newEnd);
				for(int i = end + 1; i <= newEnd; i++) {
					List.Next = new Node(i, 0);
					Node temp = List;
					List = List.Next;
					List.Prev = temp;
				}
				end = newEnd;
			}
			else {
				goToIndex(newEnd);
				List.Next = null;
				end = newEnd;
			}
		}
		private void goToIndex(int index) {
			if(index > List.Index) {
				while(List.Index != index && List.Index != end) {
					List = List.Next;
				}
			}
			else if(index < List.Index) {
				while(List.Index != index && List.Index != start) {
					List = List.Prev;
				}
			}
		}
	}

	static void Main () {
		Array arr = new Array(0,5);
		arr.set(5, 1);
		arr.set(0, 2);
		arr.set(2, 3);
		Console.WriteLine(arr.get(5));
		Console.WriteLine(arr.get(0));
		Console.WriteLine(arr.get(2));
		arr.changeBounds(3, 7);
		arr.set(7, 1);
		Console.WriteLine(arr.get(7));
		Console.WriteLine(arr.get(2));
		arr.changeBounds(7, 7);
		Console.WriteLine(arr.get(7));
		arr.changeBounds(1, 3);
		arr.set(2, 5);
		Console.WriteLine(arr.get(2));

		return;
	}
}