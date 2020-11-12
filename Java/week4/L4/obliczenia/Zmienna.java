package obliczenia;

public class Zmienna extends Wyrazenie {
   private static Zbior tablicaPar;
   static {
      tablicaPar = new Zbior();
   }
   public final String klucz;

   @Override
   public int oblicz() {
      return (int) tablicaPar.czytaj(klucz);
   }

   public static void usun(String klucz) {
      tablicaPar.usun(klucz);
   }

   public static boolean istnieje(String klucz) {
      return tablicaPar.istnieje(klucz);
   }

   public static Para szukaj(String klucz) {
      return tablicaPar.szukaj(klucz);
   }

   public static void ustaw(String key, int value) {
      // System.out.println(key + " " + value);
      tablicaPar.ustaw(new Para(key, value));
   }

   public Zmienna(String klucz) {
      this.klucz = klucz;
   }

   public String toString() {
      return klucz;
   }

}
