import obliczenia.*;

public class Test2 {
      public static void main(String args[]) {

            Instrukcja program = new Blok(new Deklaracja("n"), new Czytaj("n"), new IfElse(
                        new Mniejsze(new Zmienna("n"), new Liczba(2)), new Cout(0),
                        new Blok(new Deklaracja("p"), new Przypisanie("p", new Liczba(2)), new Deklaracja("wyn"),
                                    new Przypisanie("wyn", new Liczba(0)),
                                    new Blok(new While(
                                                new MniejszeRowne(new Mnozenie(new Zmienna("p"), new Zmienna("p")),
                                                            new Zmienna("n")),
                                                new Blok(new If(
                                                            new Rowne(new Reszta(new Zmienna("n"), new Zmienna("p")),
                                                                        new Liczba(0)),
                                                            new Blok(new Przypisanie("wyn", new Zmienna("p")),
                                                                        new Przypisanie("p", new Zmienna("n")))),
                                                            new Przypisanie("p",
                                                                        new Dodawanie(new Zmienna("p"), new Liczba(1))))

                                    )), new IfElse(new Wieksze(new Zmienna("wyn"), new Liczba(0)), new Cout(0),
                                                new Cout(1)))));
            program.wykonaj();

      }
}
