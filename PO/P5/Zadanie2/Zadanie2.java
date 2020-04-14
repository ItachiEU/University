import java.util.Collections;
import java.util.Scanner;
import java.util.Hashtable;

public class Zadanie2 {
   public static void main(String[] args) {
      Hashtable<String, Integer> Args = new Hashtable<String, Integer>();

      Args.put("x", 2);
      Wyrazenie zmienna = new Dodaj(new Stala(2), new Zmienna("x", Args));
      System.out.println(zmienna.toString() + " = " + zmienna.Oblicz());

      Args.put("y", 8);
      Wyrazenie nested = new Pomnoz(new Stala(4), new Stala(5));
      nested = new Dodaj(new Zmienna("y", Args), nested);
      System.out.println(nested.toString());

      Wyrazenie sub = new Odejmij(new Stala(2), new Stala(4));
      System.out.println(sub.toString() + " = " + sub.Oblicz());
   }
}