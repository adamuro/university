package obliczenia;

public class Silnia extends OperatorJednoArg {
  public Silnia(Wyrazenie w) {
    super(w);
  }

  @Override
  public int oblicz() {
    int wynikWyrazenia = this.wyrazenie.oblicz();
    if (wynikWyrazenia < 0) {
      throw new ArithmeticException("Próba obliczenia silni liczby ujemnej");
    }

    int wynik = 1;
    for (int i = 2; i <= wynikWyrazenia; i++) {
      wynik *= i;
    }

    return wynik;
  }

  @Override
  public String toString() {
    return this.wyrazenie.toString() + "!";
  }
}