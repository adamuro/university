package obliczenia;

public abstract class OperatorDwuArg extends Wyrazenie {
  protected final Wyrazenie wyrazenieLewe;
  protected final Wyrazenie wyrazeniePrawe;

  public OperatorDwuArg(Wyrazenie wl, Wyrazenie wp) {
    this.wyrazenieLewe = wl;
    this.wyrazeniePrawe = wp;
  }

  @Override
  public boolean equals(Object obj) {
    if (!(obj instanceof Obliczalny)) return false;

    Obliczalny o = (Obliczalny)obj;
    try {
      return o.oblicz() == this.oblicz();
    } catch (ArithmeticException exception) {
      return false;
    }
  }
}