package obliczenia;

public class Logarytm extends OperatorDwuArg {
  public Logarytm(Wyrazenie wl, Wyrazenie wp) {
    super(wl, wp);
  }

  /* Poprawione obliczanie logarytmu */
  @Override
  public int oblicz() {
    int wyrazenieLeweWynik = this.wyrazenieLewe.oblicz();
    int wyrazeniePraweWynik = this.wyrazeniePrawe.oblicz();
    if (wyrazenieLeweWynik < 0 || wyrazeniePraweWynik < 0) {
      throw new ArithmeticException("Logarytm na liczbach ujemnych");
    }

    if (wyrazeniePraweWynik == 0) {
      throw new ArithmeticException("Logarytm z zera");
    }

    if (wyrazenieLeweWynik < 2) {
      throw new ArithmeticException("Logarytm o podstawie mniejszej od 2");
    }
    
    int wynik = 0;
    int potega = 1;
    while (potega < wyrazeniePraweWynik) {
      potega *= wyrazenieLeweWynik;
      wynik += 1;
    }

    return wynik;
  }

  @Override
  public String toString() {
    return "log" + this.wyrazenieLewe.toString() + "(" + this.wyrazeniePrawe.toString() + ")";
  }
}
