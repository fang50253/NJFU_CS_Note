import java.util.*;
import java.util.regex.*;
public class MergeIntervel
{
    public static int[][] parseIntervals(String input)
    {
        Pattern pattern = Pattern.compile("\\[\\[.*\\]\\]");
        Matcher matcher = pattern.matcher(input);
        if (!matcher.find())
        {
            System.out.println("Error!");
            return new int[0][0];
        }
        String arrayStr = matcher.group();
        arrayStr = arrayStr.substring(1, arrayStr.length() - 1);
        String[] intervalStrs = arrayStr.split("\\],\\[");
        int[][] intervals = new int[intervalStrs.length][2];
        for (int i = 0; i < intervalStrs.length; i++) 
        {
            String cleanStr = intervalStrs[i].replace("[", "").replace("]", "");
            String[] numbers = cleanStr.split(",");
            if (numbers.length != 2)
            {
                System.out.println("Error!");
                return new int[0][0];
            }
            intervals[i][0] = Integer.parseInt(numbers[0]);
            intervals[i][1] = Integer.parseInt(numbers[1]);
        }
        return intervals;
    }
    public static int max(int a,int b)
    {
        return a>b?a:b;
    }
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine().trim();
        int[][] intervals = parseIntervals(input);
        Arrays.sort(intervals,(a,b)->a[0]-b[0]);
        int st=intervals[0][0],ed=0;
        System.out.print("[");
        for(int i=0;i<intervals.length;++i)
        {
            if(intervals[i][0]<=ed||i==0)
            {
                ed=max(ed,intervals[i][1]);
            }
            else
            {
                System.out.print("["+st+","+ed+"]");
                st=intervals[i][0];
                ed=intervals[i][1];
                if(i==intervals.length-1) 
                {
                    System.out.print("["+st+","+ed+"]");
                }
                else System.out.print(",");
            }
            
        }
        System.out.println("]");
    }
}