import java.util.Hashtable;

public class Zmienna implements Wyrazenie {
   String s;
   Hashtable<String, Integer> Args;

   public Zmienna(String s, Hashtable<String, Integer> t) {
      this.s = s;
      this.Args = t;
   }

   public int Oblicz() {
      return Args.get(s);
   }

   public String toString() {
      return " " + s + " ";
   }
}