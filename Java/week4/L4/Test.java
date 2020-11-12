import obliczenia.*;

public class Test {
      public static void main(String args[]) {
            Wyrazenie w = new Dodawanie(new Liczba(3), new Liczba(5));
            System.out.println(w);
            System.out.println(w.oblicz());
            Zmienna.ustaw("x", 2);

            w = new Przeciwna(new Mnozenie(new Odejmowanie(new Liczba(2), new Zmienna("x")), new Liczba(7)));
            System.out.println(w);
            System.out.println(w.oblicz());

            w = new Minimum(new Mnozenie(new Dodawanie(new Zmienna("x"), new Liczba(13)), new Zmienna("x")),
                        new Reszta(new Odejmowanie(new Liczba(1), new Zmienna("x")), new Liczba(2)));
            System.out.println(w);
            System.out.println(w.oblicz());

            Zmienna.ustaw("y", 8);
            w = new Mniejsze(
                        new Dodawanie(new Potegowanie(new Liczba(2), new Liczba(5)),
                                    new Mnozenie(new Zmienna("x"), new Logarytm(new Liczba(2), new Zmienna("y")))),
                        new Liczba(20));
            System.out.println(w);
            System.out.println(w.oblicz());
      }
}
