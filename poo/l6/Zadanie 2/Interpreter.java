import java.util.HashMap;
public class Interpreter {
    public static class Context {
        private HashMap<String, Boolean> localVariables;

        public Context() {
            this.localVariables = new HashMap<>();
        }

        public Boolean getValue(String variableName) throws Exception {
            if(this.localVariables.get((variableName)) == null) {
                throw new Exception("Variable '" + variableName + "' has no value");
            }
            return this.localVariables.get(variableName);
        }

        public void setValue(String variableName, Boolean value) {
            this.localVariables.put(variableName, value);
        }
    }

    public static abstract class AbstractExpression {
        public abstract Boolean Interpret(Context context) throws Exception;
    }

    public static class ConstExpression extends AbstractExpression {
        private String variableName;

        public ConstExpression(String variableName) {
            this.variableName = variableName;
        }

        @Override
        public Boolean Interpret(Context context) throws Exception {
            return context.getValue(this.variableName);
        }
    }

    public static abstract class UnaryExpression extends AbstractExpression {
        protected AbstractExpression expression;
    }

    public static class NegationExpression extends UnaryExpression {
        public NegationExpression(AbstractExpression expression) {
            this.expression = expression;
        }

        @Override
        public Boolean Interpret(Context context) throws Exception {
            return !this.expression.Interpret(context);
        }
    }

    public static abstract class BinaryExpression extends AbstractExpression {
        protected AbstractExpression leftExpression;
        protected AbstractExpression rightExpression;
    }

    public static class ConjunctionExpression extends BinaryExpression {
        public ConjunctionExpression(AbstractExpression leftExpression, AbstractExpression rightExpression) {
            this.leftExpression = leftExpression;
            this.rightExpression = rightExpression;
        }

        @Override
        public Boolean Interpret(Context context) throws Exception {
            return this.leftExpression.Interpret(context) && this.rightExpression.Interpret(context);
        }
    }

    public static class AlternativeExpression extends BinaryExpression {
        public AlternativeExpression(AbstractExpression leftExpression, AbstractExpression rightExpression) {
            this.leftExpression = leftExpression;
            this.rightExpression = rightExpression;
        }

        @Override
        public Boolean Interpret(Context context) throws Exception {
            return this.leftExpression.Interpret(context) || this.rightExpression.Interpret(context);
        }
    }

    public static void main(String[] args) {
        Context context = new Context();
        context.setValue("x", false);
        context.setValue("y", true);

        AbstractExpression expression =
                new ConjunctionExpression(
                        new NegationExpression(
                                new ConstExpression("x")
                        ),
                        new AlternativeExpression(
                                new ConstExpression("x"),
                                new ConstExpression("y")
                        )
                );

        AbstractExpression badExpression =
                new ConjunctionExpression(
                        new NegationExpression(
                                new ConstExpression("a")
                        ),
                        new AlternativeExpression(
                                new ConstExpression("x"),
                                new ConstExpression("y")
                        )
                );

        try {
            Boolean value = expression.Interpret(context);
            System.out.format("(!false) && (false || true) = %b\n", value);

            /* Wyrzuca wyjątek */
            badExpression.Interpret(context);
        } catch (Exception e) {
            System.out.println("Exception: " + e.getMessage());
        }
    }
}
