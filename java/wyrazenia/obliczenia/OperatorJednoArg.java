package obliczenia;

public abstract class OperatorJednoArg extends Wyrazenie {
  protected final Wyrazenie wyrazenie;

  public OperatorJednoArg(Wyrazenie w) {
    this.wyrazenie = w;
  }
}