import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Stream;
import java.util.stream.Collectors;


public class Main {

    // password format
    // eg. 15-16 p: ppppppppppplppppp 
    // group(1) = 15
    // group(2) = 16
    // group(3) = p
    // group (4) = ppppppppppplppppp 
    private static Pattern p = Pattern.compile("(\\d+)-(\\d+) ([a-z]): ([a-z]+)");

    // main which is executed
    public static void main(String[]args) throws IOException {
        try (Stream<String> stream = Files.lines(Paths.get("passwords.txt"))) {
            List<String> lines = stream.collect(Collectors.toList());
            System.out.println(part2(lines));
            stream.close();
        }

    }

    // part 1
    // Each line gives the password policy and then the password.
    // The password policy indicates the lowest and highest number
    // of times a given letter must appear for the password to be valid.
    public static int part1(List<String> lines) {
        // whether it passes the policy or not
        int pass = 0;
        // number of occurances of the character in the password
        long count = 0;
        for (String line: lines) {
            Matcher m = p.matcher(line);

            while (m.find()) {
                // grab each group from the regex expression
                int min = Integer.parseInt(m.group(1));
                int max = Integer.parseInt(m.group(2));
                char c = m.group(3).charAt(0);
                String password = m.group(4);

                count = password.chars().filter(ch -> ch == c).count();
                if (count <= max && count >= min) {
                    // if within bounds, increment
                    pass++;
                }
            }
        }
        return pass;
    }

    // part 2
    // Each policy actually describes two positions in the password,
    // where 1 means the first character, 2 means the second character,
    // and so on. (Be careful; Toboggan Corporate Policies have no concept
    // of "index zero"!) Exactly one of these positions must contain the
    // given letter. Other occurrences of the letter are irrelevant for
    // the purposes of policy enforcement.
    public static int part2(List<String> lines) {
        int pass = 0;
        for (String line: lines) {
            Matcher m = p.matcher(line);

            while (m.find()) {
                // grab each group from the regex expression
                int idx1 = Integer.parseInt(m.group(1));
                int idx2 = Integer.parseInt(m.group(2));
                char c = m.group(3).charAt(0);
                String password = m.group(4);

                // check whether the char c is in index idx1 or idx2
               if (password.charAt(idx1-1) == c ^ password.charAt(idx2-1) == c) {
                   pass++;
               }
            }
        }
    return pass;
    }

}