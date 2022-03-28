import java.util.Arrays;
import java.util.Collections;

public class Zad2 {
    public static class Item {
        public Item(double price, String name) {
            this.price = price;
            this.name = name;
        }
        public double price;
        public String name;
    }

    /* Klasy w wersjach pierwotnych */
    public class TaxCalculatorBefore {
        public double calculateTax(double price) { return price * 0.22; }
    }

    public class CashRegisterBefore {
        public TaxCalculatorBefore taxCalc = new TaxCalculatorBefore();

        public double calculatePrice(Item[] items) {
            double price = 0;
            for (Item item: items) {
                price += item.price + taxCalc.calculateTax(item.price);
            }
            return price;
        }

        public void printBill(Item[] items) {
            for (Item item: items) {
                System.out.format("Towar %s : cena %f + podatek %f\n",
                        item.name, item.price, taxCalc.calculateTax(item.price));
            }
        }
    }

    /* Poprawione klasy */

    public interface ITaxCalculator {
        double calculateTax(double price);
    }

    public static class ChangingTaxCalculator implements ITaxCalculator {
        public double tax;

        public ChangingTaxCalculator(double tax) { this.tax = tax; }

        @Override
        public double calculateTax(double price) { return price * tax; }
    }

    public interface IItemSorter {
        Item[] sortItems(Item[] items);
    }

    public static class AlphabeticalItemSorter implements IItemSorter {
        @Override
        public Item[] sortItems(Item[] items) {
            for (int i = 0; i < items.length - 1; i++) {
                int minNameIndex = i;
                for (int j = i + 1; j < items.length; j++) {
                    if (items[j].name.compareTo(items[minNameIndex].name) < 0)
                        minNameIndex = j;
                }
                Collections.swap(Arrays.asList(items), i, minNameIndex);
            }
            return items;
        }
    }

    public static class PriceItemSorter implements IItemSorter {
        @Override
        public Item[] sortItems(Item[] items) {
            for (int i = 0; i < items.length - 1; i++) {
                int minPriceIntex = i;
                for (int j = i + 1; j < items.length; j++) {
                    if (items[j].price < items[minPriceIntex].price)
                        minPriceIntex = j;
                }
                Collections.swap(Arrays.asList(items), i, minPriceIntex);
            }
            return items;
        }
    }
    public static class CashRegister {
        public double calculatePrice(Item[] items, ITaxCalculator taxCalc) {
            double price = 0;
            for (Item item: items) {
                price += item.price + taxCalc.calculateTax(item.price);
            }
            return  price;
        }

        public void printBill(Item[] items, ITaxCalculator taxCalc, IItemSorter itemSorter) {
            for (Item item: itemSorter.sortItems(items)) {
                System.out.format("Towar %s : cena %.2f + podatek %.2f\n",
                        item.name, item.price, taxCalc.calculateTax(item.price));

            }
        }
    }

    public static void main(String[] args) {
        Item[] items = new Item[] {
                new Item(1.50, "Woda"),
                new Item(3.50, "Mleko"),
                new Item(2.50, "Chleb"),
                new Item(4.00, "Czekolada")
        };
        ChangingTaxCalculator vatCalc = new ChangingTaxCalculator(0.23);
        CashRegister cashRegister = new CashRegister();

        System.out.println("Sortowanie alfabetyczne");
        cashRegister.printBill(items, vatCalc, new AlphabeticalItemSorter());
        System.out.println("Sortowanie wg ceny");
        cashRegister.printBill(items, vatCalc, new PriceItemSorter());
        System.out.println("Po podwyższeniu podatku");
        vatCalc.tax = 0.27;
        cashRegister.printBill(items, vatCalc, new AlphabeticalItemSorter());
    }
}
