package Wyrazenie;

public class main {
    public static void main(String[] args) {
        try {
            Wyrazenie w = new Dodaj(new Stala(5), new Stala(3)); // 5 + 3
            System.out.println(w.Oblicz());
            Wyrazenie w1 = new Pomnoz(w, new Stala((2))); // 8 * 2
            System.out.println(w1.Oblicz());
            Wyrazenie w2 = new Podziel(w1, new Stala((0))); // 16 / 4
            System.out.println(w2.Oblicz());
            Wyrazenie w3 = new Odejmij(new Zmienna("x"), w1); // x - 16
            System.out.println(w3.Oblicz());
            Wyrazenie.UstawWartoscZmiennej("x", 3); // x = 3
            System.out.println(w3.Oblicz()); // 3 - 16
            System.out.println(w3.toString());
        }
        catch(Exception e) {

        }
    }
}
