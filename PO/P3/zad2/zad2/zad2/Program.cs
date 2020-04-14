using System;

namespace zad2
{
    public class Pair<K, V> where K:IComparable
    {
        public K first;
        public V second;

        public Pair (K k, V v)
        {
            first = k;
            second = v;
        }
    }
    public class Node<K, V> where K : IComparable
    {
        public Node<K, V> prev;
        public Node<K, V> next;
        public Pair<K, V> curr;

        public Node(Pair<K, V> c)
        {
            prev = null;
            next = null;
            curr = c;
        }
    }
    public class Dictionary<K, V> where K:IComparable
    {
        protected Node<K, V> first;
        protected int size;
        public Dictionary()
        {
            this.first = null;
            this.size = 0;
        }
        public int Size()
        {
            return this.size;
        }
        public bool Empty()
        {
            if (size == 0)
                return true;
            return false;
        }
        public void Add(K k, V v)
        {
            Node<K, V> node = new Node<K, V>(new Pair<K, V>(k, v));
            if(this.Empty())
            {
                this.first = node;
            }
            else
            {
                this.first.prev = node;
                node.next = first;
                this.first = node;
            }
            this.size++;
        }
        public V Find(K k)
        {
            return FindNode(k).curr.second;
        }
        private Node<K, V> FindNode(K k)
        {
            Node<K, V> node = this.first;
            while (k.CompareTo(node.curr.first) != 0)
            {
                node = node.next;
            }
            return node;
        }
        public void Remove(K k)
        {
            Node<K, V> node = FindNode(k);
            Console.WriteLine(node.curr.first);
            Console.WriteLine(node.curr.second);
            if (node.next != null && node.prev != null)
            {
                node.prev.next = node.next;
            }
            if (node.prev != null && node.next != null)
            {
                node.next.prev = node.prev;
            }
            size--;
        }
    }
    class TestProgram
    {
        public static void Main(string[] args)
        {
            Dictionary<string, int> test = new Dictionary<string, int>();
            test.Add("test1", 12);
            test.Add("string", 12039);
            test.Add("costam", 7);
            Console.WriteLine("Ile elementow w slowniku: " + test.Size());
            Console.WriteLine("Szukam elementu \"string\":" + test.Find("string"));
            Console.WriteLine("Usuwam element \"costam\".");
            test.Remove("costam");
            Console.WriteLine("Rozmiar slownika po usunieciu elementu: " + test.Size());

        }
    }
}
