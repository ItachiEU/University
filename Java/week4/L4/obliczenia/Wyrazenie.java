package obliczenia;

public abstract class Wyrazenie implements Obliczalny {
   public abstract int oblicz();

   public static double suma(Wyrazenie... wyr) {
      double sum = 0;
      for (int i = 0; i < wyr.length; i++)
         sum += wyr[i].oblicz();
      return sum;
   }

   public static double iloczyn(Wyrazenie... wyr) {
      double ilo = 0;
      for (int i = 0; i < wyr.length; i++)
         ilo *= wyr[i].oblicz();
      return ilo;
   }
}
