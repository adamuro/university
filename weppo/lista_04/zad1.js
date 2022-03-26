function Tree(val, left, right) {
  this.left = left;
  this.right = right;
  this.val = val;
}

Tree.prototype[Symbol.iterator] = function*() {
  const queue = [ this ];
  
  while (queue.length > 0) {
    const node = queue.splice(0, 1)[0];
    if(node.left) queue.push(node.left);
    if(node.right) queue.push(node.right);

    yield node.val;
  }
}

var root = new Tree( 1, new Tree( 2, new Tree( 3, new Tree(4), new Tree(5)) ), new Tree( 6 ));
for ( var e of root ) {
  console.log( e );
}
