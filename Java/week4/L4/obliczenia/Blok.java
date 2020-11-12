package obliczenia;

public class Blok extends Instrukcja {
   public Instrukcja[] instrukcje;

   public Blok(Instrukcja... in) {
      instrukcje = in;
      for (int i = 0; i < instrukcje.length; i++) {
         if (instrukcje[i] == null)
            throw new IllegalArgumentException("Argument jest nullem");
      }
   }

   public void wykonaj() {
      for (int i = 0; i < instrukcje.length; i++)
         instrukcje[i].wykonaj();
      for (int i = 0; i < instrukcje.length; i++) {
         if (instrukcje[i].getClass() == (new Deklaracja(" ")).getClass()) {
            Deklaracja temp = (Deklaracja) instrukcje[i];
            temp.usun();
         }
      }
   }
}
