using System;

class Testy {
	static void Main () {
		Slownik<int, string> s = new Slownik<int, string> ();

		s.Add(1, "jeden");
		Console.WriteLine(s.Find(1));
		try {
			s.Find(2);
		}
		catch (System.IndexOutOfRangeException indEx) {
			Console.WriteLine(indEx.Message);
		}
		s.Delete(2);
		s.Delete(1);
		try {
			s.Find(1);
		}
		catch (System.IndexOutOfRangeException indEx) {
			Console.WriteLine(indEx.Message);
		}
		s.Add(1, "jeden");
		s.Add(2, "dwa");
		Console.WriteLine(s.Find(1));
		Console.WriteLine(s.Find(2));
		return;
	}
}