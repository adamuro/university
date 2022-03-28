package main;

import java.lang.reflect.Modifier;
import java.lang.reflect.Type;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;

public class Container {
    public static class SimpleContainer {
        private Set<Type> singletonTypes;
        private HashMap<Type, Object> singletons;
        private HashMap<Class, Class> implementations;

        public SimpleContainer() {
            this.singletonTypes = new HashSet<>();
            this.singletons = new HashMap<>();
            this.implementations = new HashMap<>();
        }

        public void registerType(Type type, Boolean singleton) {
            if(singleton) {
                singletonTypes.add(type);
            } else {
                singletonTypes.remove(type);
            }
        }

        public void registerType(Class from, Class to, Boolean singleton) throws Exception {
            if(!from.isAssignableFrom(to)) {
                throw new InstantiationException();
            }
            if(to.isInterface() || Modifier.isAbstract(to.getModifiers())) {
                throw new InstantiationException();
            }

            implementations.put(from, to);
            this.registerType(from, singleton);
        }

        public <T> T resolve(Class<T> tClass) throws Exception {
            Class implementationClass = tClass;
            if(tClass.isInterface() || Modifier.isAbstract(tClass.getModifiers())) {
                if(!implementations.containsKey(tClass)) {
                    throw new InstantiationException();
                }

                implementationClass = implementations.get(tClass);
            }

            if(!singletonTypes.contains(tClass)) {
                return (T) (implementationClass.getConstructor().newInstance());
            }
            if(singletons.containsKey(implementationClass)) {
                return (T) (singletons.get(implementationClass));
            }

            singletons.put(implementationClass, implementationClass.getConstructor().newInstance());
            return (T) (singletons.get(implementationClass));
        }
    }
}
