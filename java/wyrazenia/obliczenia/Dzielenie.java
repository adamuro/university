package obliczenia;

public class Dzielenie extends OperatorDwuArg {
  public Dzielenie(Wyrazenie wl, Wyrazenie wp) {
    super(wl, wp);
  }

  @Override
  public int oblicz() {
    return this.wyrazenieLewe.oblicz() / this.wyrazeniePrawe.oblicz();
  }

  @Override
  public String toString() {
    return "(" + this.wyrazenieLewe.toString() + " / " + this.wyrazeniePrawe.toString() + ")";
  }
}
