package obliczenia;

public class ZmianaZnaku extends OperatorJednoArg {
  public ZmianaZnaku(Wyrazenie w) {
    super(w);
  }

  @Override
  public int oblicz() {
    return -1 * this.wyrazenie.oblicz();
  }

  @Override
  public String toString() {
    return "-" + this.wyrazenie.toString();
  }
}