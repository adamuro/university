package main;

import java.lang.reflect.Modifier;
import java.lang.reflect.Type;

public class SimpleContainer {
    private Context context;

    public SimpleContainer() {
        this.context = new Context();
    }

    public void registerType(Type type, Boolean singleton) {
        if(singleton) {
            this.context.singletonTypes.add(type);
        } else {
            this.context.singletonTypes.remove(type);
        }
    }

    public void registerType(Class from, Class to, Boolean singleton) throws Exception {
        if(!from.isAssignableFrom(to)) {
            throw new InstantiationException("Class 'to' does not extend or implement class 'from'");
        }
        if(to.isInterface() || Modifier.isAbstract(to.getModifiers())) {
            throw new InstantiationException("Class 'to' is abstract or interface");
        }

        this.context.implementations.put(from, to);
        this.registerType(from, singleton);
    }

    public <T> void registerInstance(Class<T> tClass, T tInstance) throws Exception {
        registerType(tClass, tInstance.getClass(), true);
        this.context.singletons.put(tInstance.getClass(), tInstance);
    }

    public <T> T resolve(Class<T> tClass) throws Exception {
        ConstructorVisitor constructorVisitor = new ConstructorVisitor(this.context);
        T tInstance = constructorVisitor.visit(tClass);
        this.context = constructorVisitor.getContext();

        return tInstance;
    }
}
