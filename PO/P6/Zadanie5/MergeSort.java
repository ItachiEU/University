public class MergeSort implements Runnable {
   int[] tab;
   int[] temp;
   int start;
   int end;

   MergeSort(int[] tab, int start, int end) {
      this.tab = tab;
      this.start = start;
      this.end = end;

      temp = new int[end + 1];
   }

   private void Merge() {
      int middle = (start + end) / 2;

      for (int i = start; i <= end; i++)
         temp[i] = tab[i];

      int i = start, j = middle + 1, k = start;

      while (i <= middle && j <= end) {
         if (temp[i] < temp[j]) {
            tab[k] = temp[i];
            k++;
            i++;
         } else {
            tab[k] = temp[j];
            k++;
            j++;
         }
      }
      while (i <= middle) {
         tab[k] = temp[i];
         k++;
         i++;
      }
      while (j <= end) {
         tab[k] = temp[j];
         k++;
         j++;
      }
   }

   public void run() {
      if (start < end) {
         int middle = (start + end) / 2;

         MergeSort left = new MergeSort(tab, start, middle);
         MergeSort right = new MergeSort(tab, middle + 1, end);
         Thread thread_left = new Thread(left);
         Thread thread_right = new Thread(right);

         thread_left.start();
         thread_right.start();

         try {
            thread_left.join();
         } catch (InterruptedException err) {
            err.printStackTrace();
         }
         try {
            thread_right.join();
         } catch (InterruptedException err) {
            err.printStackTrace();
         }
         Merge();
      }
   }

}