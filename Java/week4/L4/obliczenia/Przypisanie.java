package obliczenia;

public class Przypisanie extends Instrukcja {
   private final Wyrazenie wyr;
   private final String var;

   public Przypisanie(String var, Wyrazenie e) throws IllegalArgumentException {
      if (var == null)
         throw new IllegalArgumentException("Null name of variable");
      if (e == null)
         throw new IllegalArgumentException("Null expression");
      this.var = var;
      wyr = e;
   }

   public void wykonaj() {
      Zmienna.ustaw(var, wyr.oblicz());
   }
}
