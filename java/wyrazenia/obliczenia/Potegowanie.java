package obliczenia;

public class Potegowanie extends OperatorDwuArg {
  public Potegowanie(Wyrazenie wl, Wyrazenie wp) {
    super(wl, wp);
  }

  @Override
  public int oblicz() {
    return (int)Math.pow(this.wyrazenieLewe.oblicz(), this.wyrazeniePrawe.oblicz());
  }

  @Override
  public String toString() {
    return this.wyrazenieLewe.toString() + " ^ " + this.wyrazeniePrawe.toString();
  }
}
