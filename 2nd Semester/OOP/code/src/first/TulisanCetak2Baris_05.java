package first;

public class TulisanCetak2Baris_05 {
public TulisanCetak2Baris_05(){}

    public void cetak(String a, String b) {
        System.out.println(a);
        System.out.println(b);
    }

    public static void main(String[] args) {
        TulisanCetak2Baris_05 obj = new TulisanCetak2Baris_05();
        obj.cetak("Selamat Datang di Perkuliahan PBO", "Di Universitas Budi Luhur");
    }
}
