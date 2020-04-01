using System;
using System.Collections;

class Program {
	class PrimeCollection : IEnumerable {
		public int Number {set; get;}
		int Max;

		public PrimeCollection () {
			Number = 0;
			Max = Int32.MaxValue;
		}
		// Kolekcja liczb pierwszych większych niż start.
		public PrimeCollection (int start) {
			Number = start;
			Max = Int32.MaxValue;
		}
		// Jeśli chcielibyśmy aby foreach wypisał liczby pierwsze z jakiegoś
		// przedziału, możemy zaimplementować konstruktor z dwoma parametrami
		// oraz element Max określający maksymalną wartośc elementu Number.
		// Wtedy pozostałe konstruktory muszą ustowić Max na maks. wartość typu int.
		public PrimeCollection (int start, int end) {
			Number = start;
			Max = end;
		}
		// Tworzymy kolejne obiekty znajdując kolejną liczbę pierwszą
		// i stosując ostatni konstruktor jeśli jest ona w pożądanym zakresie.
		public PrimeCollection Next () {
			while(!isPrime(++Number) && Number >= 0);
			if(Number >= 0 && Number < Max) {
				return new PrimeCollection(Number, Max);
			}
			else {
				return null;
			}
		}
		public IEnumerator GetEnumerator () {
			return new PrimeEnum(Number, Max);
		}
		
		bool isPrime (int num) {
			if(num < 2) {
				return false;
			}
			for(int i = 2; i * i <= num; i++) {
				if(num % i == 0) {
					return false;
				}
			}
			return true;
		}
	}

	class PrimeEnum : IEnumerator {
		PrimeCollection Coll;
		public PrimeEnum (int Number, int Max) {
			Coll = new PrimeCollection(Number, Max);
		}
		public bool MoveNext () {
			Coll = Coll.Next();
			return Coll != null;
		}
		public object Current {
			get {return Coll.Number;} 
		}
		public void Reset () {
			Coll = new PrimeCollection();
		}
	}

	static void Main () {
		// Wypisuje kolejne liczby pierwsze z przedziału [0, 15].
		PrimeCollection pc = new PrimeCollection(0, 15);
		foreach(int p in pc) {
			Console.WriteLine(p);
		}
		// Analogicznie do powyższego na przedziale [15, 30].
		pc = new PrimeCollection(15, 30);
		foreach(int p in pc) {
			Console.WriteLine(p);
		}
	/*	Wypisuje kolejne liczby pierwsze.
	 	pc = new PrimeCollection();
	 	foreach(int p in pc) {
	 		Console.WriteLine(p);
	 	}
 	 
	 	* Wypisuje kolejne liczby pierwsze większe od 30.
	 	pc = new PrimeCollection(30);
	 	foreach(int p in pc) {
	 		Console.WriteLine(p);
	 	}
	*/	
		return;
	}
}