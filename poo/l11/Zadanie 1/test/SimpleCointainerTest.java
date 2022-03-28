import main.DependencyMethod;
import main.SimpleContainer;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.text.SimpleDateFormat;

public class SimpleCointainerTest {
    public interface IFoo {
        Integer getNumber();
    }
    public static class Foo implements IFoo {
        @Override
        public Integer getNumber() {
            return 1;
        }
    }
    public static class Bar implements IFoo {
        @Override
        public Integer getNumber() {
            return 2;
        }
    }
    public static class ParameterizedClass {
        public Foo foo;
        public ParameterizedClass(Foo foo) { this.foo = foo; }
    }
    public static class ConstructorCycleClass {
        public ConstructorCycleClass ccc;
        public ConstructorCycleClass(ConstructorCycleClass ccc) { this.ccc = ccc; }
    }
    public static class OnlyParameterizedConstructorsClass {
        public Foo foo;
        public String str;
        public OnlyParameterizedConstructorsClass(Foo foo, String str) {
            this.foo = foo;
            this.str = str;
        }
    }
    public static class DependencyMethodClass {
        public ParameterizedClass pc;
        @DependencyMethod
        public void setPc(ParameterizedClass pc) { this.pc = pc; }
    }
    public static class InvalidDependencyMethodClass {
        public ParameterizedClass pc;
        @DependencyMethod
        public void initPc() { this.pc = new ParameterizedClass(new Foo()); }
    }

    @Test
    void resolveInstance() throws Exception {
        SimpleContainer container = new SimpleContainer();
        Foo foo = container.resolve(Foo.class);
        Assertions.assertNotNull(foo);
    }

    @Test
    void resolveMultipleInstances() throws Exception {
        SimpleContainer container = new SimpleContainer();
        Foo foo1 = container.resolve(Foo.class);
        Foo foo2 = container.resolve(Foo.class);
        Assertions.assertNotEquals(foo1, foo2);
    }

    @Test
    void registerSingleton() throws Exception {
        SimpleContainer container = new SimpleContainer();
        container.registerType(Foo.class, true);
        Foo foo1 = container.resolve(Foo.class);
        Foo foo2 = container.resolve(Foo.class);
        Assertions.assertEquals(foo1, foo2);
    }

    @Test
    void registerInterfaceImplementation() throws Exception {
        SimpleContainer container = new SimpleContainer();
        container.registerType(IFoo.class, Foo.class, false);
        IFoo ifoo = container.resolve(IFoo.class);
        Assertions.assertNotNull(ifoo);
    }

    @Test
    void resolveMultipleInterfaceImplementations() throws Exception {
        SimpleContainer container = new SimpleContainer();
        container.registerType(IFoo.class, Foo.class, false);
        IFoo ifoo1 = container.resolve(IFoo.class);
        IFoo ifoo2 = container.resolve(IFoo.class);
        Assertions.assertNotEquals(ifoo1, ifoo2);
    }

    @Test
    void registerInterfaceImplementationSingleton() throws Exception {
        SimpleContainer container = new SimpleContainer();
        container.registerType(IFoo.class, Foo.class, true);
        IFoo ifoo1 = container.resolve(IFoo.class);
        IFoo ifoo2 = container.resolve(IFoo.class);
        Assertions.assertEquals(ifoo1, ifoo2);
    }

    @Test
    void resolveInterfaceWithoutRegisteredImplementation() throws Exception {
        SimpleContainer container = new SimpleContainer();
        Assertions.assertThrows(InstantiationException.class, () -> {
            container.resolve(IFoo.class);
        });
    }

    @Test
    void changeRegisteredInterfaceImplementation() throws Exception {
        SimpleContainer container = new SimpleContainer();
        container.registerType(IFoo.class, Foo.class, false);
        IFoo ifoo1 = container.resolve(IFoo.class);
        Integer number1 = ifoo1.getNumber();
        container.registerType(IFoo.class, Bar.class, false);
        IFoo ifoo2 = container.resolve(IFoo.class);
        Integer number2 = ifoo2.getNumber();
        Assertions.assertNotEquals(number1, number2);
    }

    @Test
    void registerInstance() throws Exception {
        SimpleContainer container = new SimpleContainer();
        IFoo foo1 = new Foo();
        container.registerInstance(IFoo.class, foo1);
        IFoo foo2 = container.resolve(IFoo.class);
        Assertions.assertEquals(foo1, foo2);
    }

    @Test
    void resolveClassWithParameterizedConstructor() throws Exception {
        SimpleContainer container = new SimpleContainer();
        container.registerType(IFoo.class, Foo.class, false);
        ParameterizedClass pc = container.resolve(ParameterizedClass.class);
        Assertions.assertNotNull(pc);
        Assertions.assertNotNull(pc.foo);
    }

    @Test
    void resolveClassWithConstructorCycle() throws Exception {
        SimpleContainer container = new SimpleContainer();
        Assertions.assertThrows(InstantiationException.class, () -> {
            container.resolve(ConstructorCycleClass.class);
        });
    }

    @Test
    void registerClassWithOnlyParameterizedConstructorsInstance() throws Exception {
        SimpleContainer container = new SimpleContainer();
        container.registerInstance(String.class, "Ala ma kota");
        OnlyParameterizedConstructorsClass opcc = container.resolve(OnlyParameterizedConstructorsClass.class);
        Assertions.assertNotNull(opcc);
        Assertions.assertNotNull(opcc.foo);
        Assertions.assertNotNull(opcc.str);
        Assertions.assertEquals(opcc.str, "Ala ma kota");
    }

    @Test
    void resolveClassWithOnlyParameterizedConstructors() {
        SimpleContainer container = new SimpleContainer();
        Assertions.assertThrows(InstantiationException.class, () -> {
            OnlyParameterizedConstructorsClass opcc = container.resolve(OnlyParameterizedConstructorsClass.class);
        });
    }

    /* Testy do zadania 1 */
    @Test
    void initializeClassWithDependencyMethod() throws Exception {
        SimpleContainer container = new SimpleContainer();
        DependencyMethodClass dmc = container.resolve(DependencyMethodClass.class);
        Assertions.assertNotNull(dmc.pc);
    }

    @Test
    void invalidSignatureDependencyMethod() {
        SimpleContainer container = new SimpleContainer();
        Assertions.assertThrows(InstantiationException.class, () -> {
            InvalidDependencyMethodClass idmc = container.resolve(InvalidDependencyMethodClass.class);
        });
    }
}
