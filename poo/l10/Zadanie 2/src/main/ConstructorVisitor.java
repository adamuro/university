package main;

import java.lang.reflect.Constructor;
import java.lang.reflect.Modifier;
import java.util.HashSet;
import java.util.Set;

public class ConstructorVisitor {
    private Context context;
    private Set<Class> visitedConstructorsClasses;

    public ConstructorVisitor(Context context) {
        this.context = context;
        this.visitedConstructorsClasses = new HashSet<>();
    }

    public Context getContext() {
        return this.context;
    }

    public <T> T visit(Class<T> tClass) throws Exception {
        Class implementationClass = tClass;
        if(tClass.isInterface() || Modifier.isAbstract(tClass.getModifiers())) {
            if(!this.context.implementations.containsKey(tClass)) {
                throw new InstantiationException("Abstract class or interface instantiation");
            }

            implementationClass = this.context.implementations.get(tClass);
        }

        if(this.context.singletonTypes.contains(tClass)) {
            if(this.context.singletons.containsKey(implementationClass)) {
                return (T) (this.context.singletons.get(implementationClass));
            }
        }

        if(this.visitedConstructorsClasses.contains(implementationClass)) {
            throw new InstantiationException("Cycle of constructor parameters detected");
        }

        this.visitedConstructorsClasses.add(implementationClass);

        Constructor<T> constructor = this.getMostParametersConstructor(implementationClass);
        if(constructor.getParameterCount() == 0) {
            T tInstance = constructor.newInstance();
            if(this.context.singletonTypes.contains(tClass)) {
                this.context.singletons.put(implementationClass, tInstance);
            }

            return tInstance;
        }

        Class[] parametersTypes = constructor.getParameterTypes();
        Object[] parametersInstances = new Object[constructor.getParameterCount()];
        for(int i = 0; i < constructor.getParameterCount(); i++) {
            parametersInstances[i] = this.visit(parametersTypes[i]);
        }

        T tInstance = constructor.newInstance(parametersInstances);
        if(this.context.singletonTypes.contains(tClass)) {
            this.context.singletons.put(implementationClass, tInstance);
        }

        return tInstance;
    }

    private <T> Constructor<T> getMostParametersConstructor(Class<T> tClass) {
        Constructor<T>[] constructors = (Constructor<T>[]) tClass.getConstructors();
        Constructor<T> mostParametersConstructor = constructors[0];
        for(Constructor<T> constructor : constructors) {
            if(constructor.getParameterCount() > mostParametersConstructor.getParameterCount()) {
                mostParametersConstructor = constructor;
            }
        }

        return mostParametersConstructor;
    }
}
