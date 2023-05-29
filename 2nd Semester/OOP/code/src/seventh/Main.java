package seventh;

public class Main {
    public static void main(String[] args) {
        double volume;
        Kotak kotak = new Kotak();

        kotak.panjang = 4;
        kotak.lebar = 3;
        kotak.tinggi = 2;

        volume = kotak.panjang * kotak.tinggi * kotak.lebar;

        System.out.println("volume : " + volume);
    }
}
