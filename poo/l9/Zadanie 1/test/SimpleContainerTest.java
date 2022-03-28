import main.Container.*;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;


public class SimpleContainerTest {
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
}
