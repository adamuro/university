import main.zad3.*;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

public class AirportTest {
    @Test
    void invalidCapacity() throws Exception {
        Assertions.assertThrows(Exception.class, () -> {
            Airport airport = new Airport(0);
        });
    }

    @Test
    void acquirePlane() throws Exception {
        Airport airport = new Airport(1);
        Plane plane = airport.acquirePlane();
        assert plane.getClass() == Plane.class;
    }

    @Test
    void exceedCapacity() throws Exception {
        Airport airport = new Airport(1);
        Plane plane = airport.acquirePlane();
        Assertions.assertThrows(Exception.class, () -> {
            Plane otherPlane = airport.acquirePlane();
        });
    }

    @Test
    void reusePlane() throws Exception {
        Airport airport = new Airport(1);
        Plane plane = airport.acquirePlane();
        airport.releasePlane(plane);
        Plane samePlane = airport.acquirePlane();
        assert plane == samePlane;
    }

    @Test
    void releasePlaneTwice() throws Exception {
        Airport airport = new Airport(2);
        Plane plane = airport.acquirePlane();
        airport.releasePlane(plane);
        Assertions.assertThrows(Exception.class, () -> {
            airport.releasePlane(plane);
        });
    }

    @Test
    void releaseInvalidPlane() throws Exception {
        Airport airport = new Airport(1);
        Plane plane = new Plane();
        Assertions.assertThrows(Exception.class, () -> {
            airport.releasePlane(plane);
        });
    }
}
