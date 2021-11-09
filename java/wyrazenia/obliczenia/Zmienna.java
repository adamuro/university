package obliczenia;

import struktury.Para;
import struktury.ZbiorListowy;

public class Zmienna extends Wyrazenie {
  public static final ZbiorListowy zbior = new ZbiorListowy();
  private final String klucz;

  public Zmienna(String k) {
    this.klucz = k;
  }

  @Override
  public int oblicz() throws ArithmeticException {
    Para p = zbior.szukaj(this.klucz);
    if (p == null) {
      throw new ArithmeticException("Zmienna " + this.klucz + " nie ma przypisanej wartości");
    }

    return p.getWartosc();
  }

  @Override
  public String toString() {
    return this.klucz;
  }
}