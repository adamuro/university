using System;

class Program {
	public class SymbolCollection {
		string Symbols;
		Random Rnd;

		public SymbolCollection (string Symbols) {
			this.Symbols = Symbols;
			Rnd = new Random();
		}

		public string RndSymbol () {
			string Symbol = "" + Symbols[Rnd.Next(Symbols.Length)];
			return Symbol;
		}
	}

	public class Gramatyka { // Gramatyka jest zbiorem wszystkich palindromów.
		SymbolCollection Terminal; // T

		public Gramatyka (string Terminal) {
			this.Terminal = new SymbolCollection(Terminal);
		}

		public string GenerateRndWord (int Length) {
			if(Length < 1) {
				ArgumentException Exception = new ArgumentException("Podana dlugosc slowa jest mniejsza od 1.");
				throw Exception;
			}
                                // Produkcje:
			string Word = "S";  // S -> aSa | a | Epsilon
                                // S należy do N, a należy do T
			while(Word.Length < Length) {
				string Symbol = Terminal.RndSymbol();
				string Production = Symbol + "S" + Symbol;

				Word = Word.Replace("S", Production);
			}
			if(Word.Length == Length) {
				Word = Word.Replace("S", Terminal.RndSymbol());
				return Word;
			}
			else {
				Word = Word.Replace("S", "");
				return Word;
			}
		}
	}

	static void Main () {
		Gramatyka g = new Gramatyka("abcd");
		try {
			Console.WriteLine(g.GenerateRndWord(0));
		}
		catch(ArgumentException Exception) {
			Console.WriteLine("Nie udalo sie wygenerowac slowa: {0}", Exception.Data);
		}
		Console.WriteLine(g.GenerateRndWord(1));
		Console.WriteLine(g.GenerateRndWord(5));
		Console.WriteLine(g.GenerateRndWord(10));
		
		return;
	}
}