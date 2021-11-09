package obliczenia;

public class Stala extends Wyrazenie{
  public static enum Wartosc {
    MINUS_JEDEN, ZERO, JEDEN;
  }

  private int wartosc;

  public Stala(Wartosc w) {
    switch (w) {
      case MINUS_JEDEN:
        this.wartosc = -1;
        break;
      case ZERO:
        this.wartosc = 0;
        break;
      case JEDEN:
        this.wartosc = 1;
        break;
    }
  }

  @Override
  public int oblicz() {
    return this.wartosc;
  }

  @Override
  public String toString() {
    return String.valueOf(this.wartosc);
  }
}