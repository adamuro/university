package main;

import java.util.ArrayList;
import java.util.List;

public class zad3 {
    public static class Plane {}

    public static class Airport {
        private int capacity;

        private List<Plane> ready;
        private List<Plane> released;

        public Airport(int capacity) throws Exception {
            if(capacity <= 0) {
                throw new Exception("Invalid capacity");
            }

            this.ready    = new ArrayList<>();
            this.released = new ArrayList<>();
            this.capacity = capacity;
        }

        public Plane acquirePlane() throws Exception {
            if(released.size() == this.capacity) {
                throw new Exception("Capacity exceeded");
            }

            if(ready.size() == 0) {
                ready.add(new Plane());
            }

            Plane plane = ready.get(0);
            ready.remove(plane);
            released.add(plane);

            return plane;
        }

        public void releasePlane(Plane plane) throws Exception {
            /* Upewnienie się, że zwracany obiekt należał do danej puli */
            if(!released.contains(plane)) {
                throw new Exception("Released plane not in pool");
            }

            ready.add(plane);
            released.remove(plane);
        }
    }
}
