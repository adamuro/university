import static sun.swing.MenuItemLayoutHelper.max;

public class Visitor {
    public static abstract class Tree {}

    public static class TreeNode extends Tree {
        public Tree left;
        public Tree right;

        public TreeNode(Tree left, Tree right) {
            this.left = left;
            this.right = right;
        }
    }

    public static class TreeLeaf extends Tree {}

    public static abstract class TreeVisitor {
        public int visit(Tree tree) {
            if(tree instanceof TreeNode)
                return this.visitNode((TreeNode)tree);
            if(tree instanceof TreeLeaf)
                return this.visitLeaf((TreeLeaf)tree);
            throw new IllegalArgumentException("Tree is neither a Node nor a Leaf");
        }

        public abstract int visitNode(TreeNode node);
        public abstract int visitLeaf(TreeLeaf leaf);
    }

    public static class DepthTreeVisitor extends TreeVisitor {
        private int depth = 0;

        public int getDepth() {
            return depth;
        }

        public void reset() {
            this.depth = 0;
        }

        @Override
        public int visitNode(TreeNode node) {
            int subtreeDepth = max(this.visit(node.left), this.visit(node.right)) + 1;
            this.depth = max(this.depth, subtreeDepth);
            return subtreeDepth;
        }

        @Override
        public int visitLeaf(TreeLeaf leaf) {
            this.depth = max(this.depth, 1);
            return 1;
        }
    }

    public static void main(String[] args) {
        Tree root =                                     // Głębokość
                new TreeNode(                           // 1
                        new TreeNode(                   // 2
                                new TreeLeaf(),         // 3
                                new TreeNode(           // 3
                                        new TreeLeaf(), // 4
                                        new TreeLeaf()  // 4
                                )
                        ),
                        new TreeLeaf()
                );

        DepthTreeVisitor visitor = new DepthTreeVisitor();
        visitor.visit(root);
        System.out.format("Głębokość drzewa: %d", visitor.getDepth());
    }
}
