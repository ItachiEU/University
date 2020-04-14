using System;

namespace zad1
{
    public class Node<T>
    {
        public Node<T> prev;
        public Node<T> next;
        public T value;

        public Node(T a)
        {
            this.prev = null;
            this.next = null;
            this.value = a;
        }
    }

    public class Lista<T>
    {
        protected Node<T> first;
        protected Node<T> last;
        protected int size;

        public Lista()
        {
            this.first = null;
            this.last = null;
            this.size = 0;
        }

        public int Size()
        {
            return this.size; 
        }
        public bool Empty()
        {
            if (this.size == 0)
                return true;
            return false;
        }

        public void AddFront(T a)
        {
            Node<T> v = new Node<T>(a);
            if (this.Empty())
            {
                this.first = v;
                this.last = v;
            }
            else
            {
                this.first.prev = v;
                v.next = this.first;
                this.first = v;
            }
            this.size++;
        }
        public void AddBack(T a)
        {
            Node<T> v = new Node<T>(a);
            if (this.Empty())
            {
                this.first = v;
                this.last = v;
            }
            else
            {
                this.last.next = v;
                v.prev = this.last;
                this.last = v;
            }
            this.size++;
        }

        public T RemoveFront()
        {
            if (this.Size() == 1)
            {
                T a = first.value;
                this.first = null;
                this.last = null;
                this.size = 0;
                return a;
            }
            else
            {
                Node<T> v = this.first;
                this.first = this.first.next;
                this.first.prev = null;
                this.size--;
                return v.value;
            }
        }
        public T RemoveBack()
        {
            if (this.Size() == 1)
            {
                T a = this.last.value;
                this.first = null;
                this.last = null;
                this.size = 0;
                return a;
            }
            Node<T> v = this.last;
            this.last = this.last.prev;
            this.last.next = null;
            this.size--;
            return v.value;
        }
    }
    class program
    {
        public static void Main(string[] args)
        {
            Lista<int> list = new Lista<int>();
            for (int i = 1; i <= 10; i++)
            {
                list.AddBack(i+10);
                list.AddFront(i);
            }
            Console.WriteLine(list.RemoveFront());
            Console.WriteLine(list.RemoveBack());
            Console.WriteLine(list.RemoveFront());
            Console.WriteLine(list.RemoveBack());
            Console.WriteLine(list.RemoveFront());
            Console.WriteLine(list.RemoveBack());
            Console.WriteLine(list.RemoveFront());
            Console.WriteLine(list.RemoveBack());
            Console.WriteLine(list.Size());
        }
    }
}
