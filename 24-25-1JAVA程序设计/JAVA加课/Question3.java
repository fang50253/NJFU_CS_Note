import java.util.*;
class Question3{
    public static void main(String[] args){
        Map<String,Integer> cnt=new HashMap<>();
        Scanner scanner=new Scanner(System.in);
        String str=scanner.nextLine();
        String words[]=str.split("[\\W]");
        for(String x:words){
            if(cnt.containsKey(x)){
                cnt.put(x,cnt.get(x)+1);
            }
            else{
                cnt.put(x,1);
            }
        }
        System.out.println(cnt);
    }
}