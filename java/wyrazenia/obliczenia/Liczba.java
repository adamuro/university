package obliczenia;

public class Liczba extends Wyrazenie {
  private final int liczba;

  public Liczba(int l) {
    this.liczba = l;
  }

  @Override
  public int oblicz() {
    return this.liczba;
  }

  @Override
  public String toString() {
    return String.valueOf(liczba);
  }
}