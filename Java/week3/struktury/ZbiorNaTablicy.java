package struktury;

public class ZbiorNaTablicy extends Zbior {
   private Para[] tablica;

   public ZbiorNaTablicy(int rozmiar) {
      if (rozmiar < 2)
         throw new IllegalArgumentException("Niepoprawny rozmiar tablicy, minimum 2.");
      tablica = new Para[rozmiar];
   }

   @Override
   public Para szukaj(String k) throws Exception {
      for (int i = 0; i < tablica.length; i++) {
         if (tablica[i] != null && tablica[i].klucz == k)
            return tablica[i];
      }
      throw new IllegalArgumentException("Nie ma takiej pary w zbiorze.");
   }

   @Override
   public void wstaw(Para p) throws Exception {
      for (int i = 0; i < tablica.length; i++) {
         if (tablica[i] != null && tablica[i].equals(p))
            throw new IllegalArgumentException("W tablicy jest juz para o tym kluczu.");
      }
      for (int i = 0; i < tablica.length; i++)
         if (tablica[i] == null) {
            tablica[i] = p;
            return;
         }
      throw new IllegalArgumentException("W tablicy nie ma juz miejsca.");
   }

   @Override
   public void usun(String k) throws Exception {
      for (int i = 0; i < tablica.length; i++)
         if (tablica[i] != null && tablica[i].klucz == k)
            tablica[i] = null;
   }

   @Override
   public double czytaj(String k) throws Exception {
      for (int i = 0; i < tablica.length; i++)
         if (tablica[i] != null && tablica[i].klucz == k)
            return tablica[i].getValue();
      throw new IllegalArgumentException("Nie ma w tablicy pary o takim kluczu.");
   }

   @Override
   public void ustaw(Para p) throws Exception {
      try {
         this.szukaj(p.klucz);
         for (int i = 0; i < tablica.length; i++) {
            if (tablica[i] != null && tablica[i].klucz == p.klucz)
               tablica[i] = p;
         }
      } catch (Exception e) {
         this.wstaw(p);
      }
   }

   @Override
   public void czysc() {
      for (int i = 0; i < tablica.length; i++)
         tablica[i] = null;
   }

   @Override
   public int ile() {
      int res = 0;
      for (int i = 0; i < tablica.length; i++)
         if (tablica[i] != null)
            res++;
      return res;
   }

}
