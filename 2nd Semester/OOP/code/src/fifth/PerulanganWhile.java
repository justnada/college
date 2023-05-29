package fifth;

import java.util.Scanner;

public class PerulanganWhile {
    public static void main(String[] args) {
        boolean jalan = true;
        int hitung = 0;
        String jawab;
        Scanner sc = new Scanner(System.in);

        while (jalan) {
            System.out.println("Apakah anda ingin keluar dari perulangan?");
            System.out.println("Jawab [y/t]");

            jawab = sc.nextLine();

            if (jawab.equalsIgnoreCase("y")) {
                jalan = false;
            }

            hitung++;
        }

        System.out.println("Anda sudah melakukan perulangan sebanyak " + hitung + " kali");
    }
}
