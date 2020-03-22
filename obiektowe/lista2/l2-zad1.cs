using System;

class Program
{
	class IntStream {
		int currentNumber;

		public IntStream () {
			currentNumber = 0;
		}
		public virtual int next () {
			if(!eos()) {
				return currentNumber++;
			}
			else {
				Console.WriteLine("End of stream.");
				return -1;
			}
		}
		public bool eos () {
			return (currentNumber < 0);
		}
		public virtual void reset () {
			currentNumber = 0;
		}
	}

	class PrimeStream : IntStream {
		int currentNumber;

		public PrimeStream () {
			currentNumber = 2;
		}
		public override int next () {
			if(!eos()) {
				int output = currentNumber;
				while(!(isPrime(++currentNumber)) && currentNumber >= 0);
				return output;
			}
			else {
				Console.WriteLine("End of stream.");
				return -1;
			}
		}
		public override void reset () {
			currentNumber = 2;
		}
		private bool isPrime(int number) {
			if(number == 2) {
				return true;
			}
			if(number % 2 == 0 || number < 2) {
				return false;
			}
			int numSqrt = (int)Math.Sqrt(number);
			for(int i = 3; i <= numSqrt; i += 2) {
				if(number % i == 0) {
					return false;
				}
			}
			return true;
		}
	}

	class RandomStream : IntStream {
		int currentNumber;
		Random rnd;

		public RandomStream () {
			rnd = new Random();
			currentNumber = rnd.Next();
		}
		public override int next () {
			if(!eos()) {
				int output = currentNumber;
				currentNumber = rnd.Next();
				return output;
			}
			else {
				Console.WriteLine("End of stream.");
				return -1;
			}
		}
	}

	class RandomWordStream {
		PrimeStream ps;
		string chars;
		Random rnd;

		public RandomWordStream () {
			ps = new PrimeStream();
			rnd = new Random();
			chars = "$%#@!*abcdefghijklmnopqrstuvwxyz1234567890?;:ABCDEFGHIJKLMNOPQRSTUVWXYZ^&";
		}

		public string next () {
			if(!ps.eos()) {
				string word = "";
				int length = ps.next();
				for(int i = 0; i < length; i++) {
					word += chars[rnd.Next(chars.Length)];
				}
				return word;
			}
			else {
				Console.WriteLine("End of stream.");
				return "";
			}
		}
		public void reset () {
			ps.reset();
		}
	}

	static void Main () {
		IntStream Stream  = new IntStream();
		Console.WriteLine("--- IntStream: ---");
		for(int i = 0; i < 10; i++) {
			Console.WriteLine(Stream.next());
		}
		Stream = new PrimeStream();
		Console.WriteLine("--- PrimeStream: ---");
		for(int i = 0; i < 10; i++) {
			Console.WriteLine(Stream.next());
		}
		Stream = new RandomStream();
		Console.WriteLine("--- RandomStream: ---");
		for(int i = 0; i < 10; i++) {
			Console.WriteLine(Stream.next());
		}
		RandomWordStream rws = new RandomWordStream();
		Console.WriteLine("--- RandomWordStream: ---");
		for(int i = 0; i < 10; i++) {
			Console.WriteLine(rws.next());
		}
		Console.WriteLine("--- RandomWordStream reset: ---");
		rws.reset();
		for(int i = 0; i < 10; i++) {
			Console.WriteLine(rws.next());
		}
		return;
	}
}