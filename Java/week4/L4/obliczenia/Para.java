package obliczenia;

public class Para {
   public final String klucz;
   private double wartosc;

   public Para(String a, double wartosc) {
      if (a == null || a.length() == 0)
         throw new IllegalArgumentException("Niepoprawny klucz: ????? " + a);
      for (int i = 0; i < a.length(); i++) {
         if (a.charAt(i) > 'z' || a.charAt(i) < 'a') {
            throw new IllegalArgumentException("niepoprawny klucz: " + a + " " + wartosc);
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

   public boolean equals(Object obj) {
      // return a.klucz == klucz;
      if (obj == null)
         return false;
      if (obj.getClass() != this.getClass())
         return false;
      Para other = (Para) obj;
      if (!other.klucz.equals(this.klucz))
         return false;
      return true;
   }

   public String toString() {
      return klucz.toString() + "->" + wartosc;
   }
}