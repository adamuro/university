package airportbase;

import java.util.ArrayList;
import java.util.List;

public class AirportBase {
    public interface IAirport {
        Plane acquirePlane() throws Exception;
        void releasePlane(Plane plane) throws Exception;
    }

    public static class Plane {}

    public static class Airport implements IAirport {
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
            if(!released.contains(plane)) {
                throw new Exception("Released plane not in pool");
            }

            ready.add(plane);
            released.remove(plane);
        }
    }
}
