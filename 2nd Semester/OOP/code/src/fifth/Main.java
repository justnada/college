package fifth;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws IOException {
        /*
         * Explain about counted and uncounted loop
         *
         * */

        for (int hitung = 1; hitung <= 5; hitung++) {
            System.out.println("Universitas Budi Luhur");
        }

        for (int i = 1; i <= 10; i += 2) {
            System.out.println("Bad n Boujee");
        }

        int nilai[] = {1, 14, 22, 6, 4};

        for (int n : nilai) {
            System.out.println(n);
        }

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int input = Integer.parseInt(br.readLine());
    }
}

