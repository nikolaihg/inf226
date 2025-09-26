import java.util.Scanner;

public class Fruits {
    static String[] buffer = {
        "apple",
        "orange",
        "pear",
        "banana",
        "tangerine"
    };

    public static void main(String[] args) {
        System.out.println("Choose something:");

        for(int i = 0; i < buffer.length ; ++i) {
            System.out.println((i + 1) + ". " + buffer[i]);
        }

        int choice = (new Scanner(System.in)).nextInt();

        System.out.println("Here you go: One " + buffer[choice-1] + " for you!");
    }
}
