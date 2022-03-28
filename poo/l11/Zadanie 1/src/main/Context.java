package main;

import java.lang.reflect.Type;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;

public class Context {
    public Set<Type> singletonTypes;
    public HashMap<Type, Object> singletons;
    public HashMap<Class, Class> implementations;

    public Context() {
        this.singletonTypes = new HashSet<>();
        this.singletons = new HashMap<>();
        this.implementations = new HashMap<>();
    }
}
