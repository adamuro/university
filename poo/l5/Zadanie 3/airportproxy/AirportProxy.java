package airportproxy;

import airportbase.AirportBase.*;

import java.rmi.AccessException;
import java.text.SimpleDateFormat;
import java.util.Calendar;

public class AirportProxy {
    public static class AirportTimeProxy implements IAirport {
        private IAirport airport;

        private void checkTime() throws AccessException {
            Calendar date = Calendar.getInstance();
            int hour = date.get(Calendar.HOUR_OF_DAY);
            if(hour < 8 || hour >= 22) {
                throw new AccessException("Access unavailable at the moment");
            }
        }

        public AirportTimeProxy(IAirport airport) {
            this.airport = airport;
        }

        @Override
        public Plane acquirePlane() throws Exception {
            checkTime();
            return airport.acquirePlane();
        }

        @Override
        public void releasePlane(Plane plane) throws Exception {
            checkTime();
            airport.releasePlane(plane);
        }
    }

    public static class AirportLogProxy implements IAirport {
        private IAirport airport;
        private final SimpleDateFormat dateFormatter;

        private String getFormattedDate() {
            Calendar date = Calendar.getInstance();
            String formattedDate = dateFormatter.format(date.getTime());
            return formattedDate;
        }

        public AirportLogProxy(IAirport airport) {
            this.airport = airport;
            this.dateFormatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        }

        @Override
        public Plane acquirePlane() throws Exception {
            System.out.format("[Wywołanie] Metoda: acquirePlane(), Data: %s\n",
                    getFormattedDate());

            Plane plane = airport.acquirePlane();

            System.out.format("[Zakończenie] Metoda: acquirePlane(), Data: %s, Zwrócona wartość: %s\n",
                    getFormattedDate(), plane.toString());
            return plane;
        }

        @Override
        public void releasePlane(Plane plane) throws Exception {
            System.out.format("[Wywołanie] Metoda: releasePlane(), Data: %s, Parametr: %s\n",
                    getFormattedDate(), plane.toString());

            airport.releasePlane(plane);

            System.out.format("[Zakończenie] Metoda: releasePlane(), Data: %s\n",
                    getFormattedDate());
        }
    }

    public static void main(String[] args) {
        try {
            IAirport airport = new Airport(3);
            IAirport timeProxy = new AirportTimeProxy(airport);
            IAirport logProxy = new AirportLogProxy(airport);

            // Po godz. 22 wyrzuca wyjątek
            Plane plane = timeProxy.acquirePlane();
            timeProxy.releasePlane(plane);

            plane = logProxy.acquirePlane();
            logProxy.releasePlane(plane);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}