using System;
using System.Collections;
using System.Collections.Generic;

namespace zad2
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            Prime primes = new Prime();
            foreach (int prime in primes)
                Console.WriteLine(prime);
        }
    }

    class Prime : IEnumerable<int>, IEnumerator<int>
    {
        private int licz_elem;
        List<int> primesL;
        int dummy;
        int index;
        bool smallEnough;

        public Prime()
        {
            this.primesL = new List<int>();
            this.dummy = 2;
            this.index = 0;
            this.smallEnough = true;
        }
        public int Size()
        {
            return licz_elem;
        }
        private bool IsPrime(int test)
        {
           for( int i = 2; i < test; i++)
            {
                if (test % i == 0)
                    return false;
            }
            return true;
        }
        void FillList(int brakuje)
        {
            while(brakuje > 0)
            {
                if(IsPrime(dummy) == true)
                {
                    this.primesL.Add(this.dummy);
                    brakuje--;
                }
                if(this.dummy >= Int32.MaxValue)
                {
                    this.smallEnough = false;
                    return;
                }
                this.dummy++;
            }
        }
        public int Element(int i)
        {
            if (i > licz_elem)
            {
                int brakuje = i - licz_elem;
                this.FillList(brakuje);
                licz_elem = i;
            }
            return this.primesL[i - 1];
        }
        public IEnumerator<int> GetEnumerator()
        {
            return this;
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return this;
        }
        public void Dispose()
        {

        }
        public int Current
        {
            get
            {
                return Element(index);
            }
        }
        object IEnumerator.Current
        {
            get
            {
                return Current;
            }
        }
        public bool MoveNext()
        {
            index++;
            return smallEnough;
        }
        public void Reset()
        {
            index = 0;
        }
    }
}
