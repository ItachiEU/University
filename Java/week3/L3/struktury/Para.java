package struktury;

public class Para {
   public final String klucz;
   private double wartosc;

   public Para(String a, double wartosc) {
      if (a == null || a.length() == 0)
         throw new IllegalArgumentException("Niepoprawny klucz");
      for (int i = 0; i < a.length(); i++) {
         if (a.charAt(i) > 'z' || a.charAt(i) < 'a') {
            throw new IllegalArgumentException("Niepoprawny klucz");
         }
      }
      klucz = a;
      this.wartosc = wartosc;
   }

   public void setValue(double a) {
      wartosc = a;
   }

   public double getValue() {
      return wartosc;
   }

   public Boolean equals(Para a) {
      return a.klucz == klucz;
   }

   public String toString() {
      return klucz.toString() + "->" + wartosc;
   }
}