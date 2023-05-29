package seventh;

class Manusia {
    String name;
    String gender;

    public void setNilai(String param1, String param2) {
        name = param1;
        gender = param2;
    }

    void cetak() {
        System.out.println(name + " is a " + gender);
    }
}

public class MethodOverloading {
    public static void main(String[] args) {
        Manusia m1, m2;

        m1 = new Manusia();
        m2 = new Manusia();

        m1.setNilai("Ziu", "Non-Binary");
        m2.setNilai("Angelo", "Male");

        m1.cetak();
        m2.cetak();
    }
}
