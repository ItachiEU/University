function Tree(val, left, right) {
   this.left = left;
   this.right = right;
   this.val = val;
}
Tree.prototype[Symbol.iterator] = function* () {
      const t = [this]
      while (t.length > 0) {
         const item = t.shift();
         if (item.right !== undefined)
            t.push(item.right);
         if (item.left !== undefined)
            t.push(item.left);
         yield item.val;
      }
   }

var root = new Tree( 1, new Tree(2, new Tree(3)), new Tree(4));

for ( var e of root ) {
   console.log( e );
}

//Ze stosem bylby DFS