package Wyrazenie;

import java.util.Hashtable;

public abstract class Wyrazenie {
    Wyrazenie (Wyrazenie Left, Wyrazenie Right) {
        nodeLeft = Left;
        nodeRight = Right;
        Zmienne = new Hashtable<String, Integer>();
    }

    public abstract int Oblicz () throws DivideByZeroException, VariableWithoutValueException;
    public abstract String toString ();

    public static void UstawWartoscZmiennej (String Name, int Value) {
        Zmienne.put(Name, Value);
    }

    protected Wyrazenie nodeLeft;
    protected Wyrazenie nodeRight;
    protected static Hashtable <String, Integer> Zmienne;

    protected static class DivideByZeroException extends Exception {
        DivideByZeroException() {
            super();
        }
    }

    protected static class VariableWithoutValueException extends Exception {
        VariableWithoutValueException(String Name) {
            super(Name);
        }
    }
}

class Dodaj extends  Wyrazenie {
    Dodaj (Wyrazenie Left, Wyrazenie Right) {
        super(Left, Right);
    }

    @Override
    public int Oblicz() {
        try {
            int Result = nodeLeft.Oblicz() + nodeRight.Oblicz();
            return Result;
        }
        catch (DivideByZeroException e) {
            System.out.println("Dzielenie przez zero.");
        }
        catch (VariableWithoutValueException e) {
            System.out.println("Zmienna " + e.getMessage() + " nie ma przypisanej wartosci.");
        }
        return 0;
    }

    @Override
    public String toString() {
        return "(" + nodeLeft.toString() + " + " + nodeRight.toString() + ")";
    }
}

class Odejmij extends Wyrazenie {
    Odejmij (Wyrazenie Left, Wyrazenie Right) {
        super(Left, Right);
    }

    @Override
    public int Oblicz() {
        try {
            int Result = nodeLeft.Oblicz() - nodeRight.Oblicz();
            return Result;
        }
        catch (DivideByZeroException e) {
            System.out.println("Dzielenie przez zero.");
        }
        catch (VariableWithoutValueException e) {
            System.out.println("Zmienna " + e.getMessage() + " nie ma przypisanej wartosci.");
        }
        return 0;
    }

    @Override
    public String toString() {
        return "(" + nodeLeft.toString() + " - " + nodeRight.toString() + ")";
    }
}

class Pomnoz extends Wyrazenie {
    Pomnoz (Wyrazenie Left, Wyrazenie Right) {
        super(Left, Right);
    }

    @Override
    public int Oblicz() {
        try {
            int Result = nodeLeft.Oblicz() * nodeRight.Oblicz();
            return Result;
        }
        catch (DivideByZeroException e) {
            System.out.println("Dzielenie przez zero.");
        }
        catch (VariableWithoutValueException e) {
            System.out.println("Zmienna " + e.getMessage() + " nie ma przypisanej wartosci.");
        }
        return 0;
    }

    @Override
    public String toString() {
        return "(" + nodeLeft.toString() + " * " + nodeRight.toString() + ")";
    }
}

class Podziel extends Wyrazenie {
    Podziel (Wyrazenie Left, Wyrazenie Right) {
        super(Left, Right);
    }

    @Override
    public int Oblicz() throws DivideByZeroException {
        try {
            int RightValue = nodeRight.Oblicz();

            if (RightValue == 0) {
                throw new DivideByZeroException();
            }
            int Result = nodeLeft.Oblicz() / RightValue;
            return Result;
        }
        catch (DivideByZeroException e) {
            System.out.println("Dzielenie przez zero.");
        }
        catch (VariableWithoutValueException e) {
            System.out.println("Zmienna " + e.getMessage() + " nie ma przypisanej wartosci.");
        }
        return 0;
    }

    @Override
    public String toString() {
        return "(" + nodeLeft.toString() + " / " + nodeRight.toString() + ")";
    }
}

class Stala extends Wyrazenie {
    Stala(int Value) {
        super(null, null);
        this.Value = Value;
    }

    @Override
    public int Oblicz() {
        return Value;
    }

    @Override
    public String toString() {
        return Integer.toString(Value);
    }

    private int Value;
}

class Zmienna extends Wyrazenie {
    Zmienna (String Name) {
        super(null, null);
        this.Name = Name;
    }

    @Override
    public int Oblicz() throws VariableWithoutValueException {
        if(Zmienne.containsKey(Name)) {
            return Zmienne.get(Name);
        }
        throw new VariableWithoutValueException(Name);
    }

    @Override
    public String toString() {
        return Name;
    }

    private String Name;
}